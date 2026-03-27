/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "Texture.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <tgfclient.h>

TextureManager& TextureManager::instance() {
    static TextureManager mgr;
    return mgr;
}

GLuint TextureManager::load(const std::string& path) {
    if (path.empty()) return createFallback();
    auto it = m_cache.find(path);
    if (it != m_cache.end()) return it->second;
    GLuint tex = loadFromFile(path);
    m_cache[path] = tex;
    return tex;
}

void TextureManager::unloadAll() {
    for (auto& kv : m_cache) {
        glDeleteTextures(1, &kv.second);
    }
    m_cache.clear();
}

// Compare file extension case-insensitively
static bool hasExtension(const std::string& path, const char* ext) {
    size_t pos = path.rfind('.');
    if (pos == std::string::npos) return false;
    std::string e = path.substr(pos + 1);
    std::string ref(ext);
    if (e.size() != ref.size()) return false;
    for (size_t i = 0; i < e.size(); i++) {
        if (tolower((unsigned char)e[i]) != tolower((unsigned char)ref[i])) return false;
    }
    return true;
}

GLuint TextureManager::loadFromFile(const std::string& path) {
    if (hasExtension(path, "rgb") || hasExtension(path, "rgba") || hasExtension(path, "sgi") ||
        hasExtension(path, "bw")) {
        GLuint tex = loadSGI(path);
        if (tex) return tex;
    }
    GfOut("TextureManager: unsupported or missing texture '%s', using fallback\n", path.c_str());
    return createFallback();
}

// SGI/RGB image loader
// Header layout (big-endian):
//   short  magic      = 0x01DA
//   char   storage    (0=verbatim, 1=RLE)
//   char   bpc        (bytes per channel, usually 1)
//   ushort dimension
//   ushort xsize, ysize, zsize
//   int    pixmin, pixmax
//   char   dummy[4]
//   char   imagename[80]
//   int    colormap
//   char   pad[404]

static unsigned short swapShort(unsigned short v) {
    return (unsigned short)((v >> 8) | (v << 8));
}

static unsigned int swapInt(unsigned int v) {
    return ((v & 0xFF000000u) >> 24) | ((v & 0x00FF0000u) >> 8) |
           ((v & 0x0000FF00u) << 8)  | ((v & 0x000000FFu) << 24);
}

GLuint TextureManager::loadSGI(const std::string& path) {
    FILE* f = fopen(path.c_str(), "rb");
    if (!f) {
        GfOut("TextureManager::loadSGI: cannot open '%s'\n", path.c_str());
        return 0;
    }

    unsigned short magic = 0;
    if (fread(&magic, 2, 1, f) != 1) { fclose(f); return 0; }
    // Detect byte order - SGI files are big-endian, magic = 0x01DA
    bool swapped = false;
    if (magic == 0xDA01) { swapped = true; magic = 0x01DA; }
    else if (magic != 0x01DA) {
        GfOut("TextureManager::loadSGI: not an SGI file '%s' (magic=%04x)\n", path.c_str(), magic);
        fclose(f);
        return 0;
    }

    unsigned char storage, bpc;
    unsigned short dimension, xsize, ysize, zsize;
    if (fread(&storage, 1, 1, f) != 1 || fread(&bpc, 1, 1, f) != 1) { fclose(f); return 0; }
    if (fread(&dimension, 2, 1, f) != 1) { fclose(f); return 0; }
    if (fread(&xsize, 2, 1, f) != 1) { fclose(f); return 0; }
    if (fread(&ysize, 2, 1, f) != 1) { fclose(f); return 0; }
    if (fread(&zsize, 2, 1, f) != 1) { fclose(f); return 0; }
    if (swapped) { dimension = swapShort(dimension); xsize = swapShort(xsize); ysize = swapShort(ysize); zsize = swapShort(zsize); }

    // Skip remainder of header (total header = 512 bytes)
    fseek(f, 512, SEEK_SET);

    int numChannels = (int)zsize;
    if (numChannels < 1) numChannels = 1;
    if (numChannels > 4) numChannels = 4;

    int totalPixels = (int)xsize * (int)ysize;
    unsigned char* imgData = (unsigned char*)malloc(totalPixels * 4);
    if (!imgData) { fclose(f); return 0; }
    memset(imgData, 255, totalPixels * 4);

    if (storage == 0) {
        // Verbatim storage
        unsigned char* channelBuf = (unsigned char*)malloc(totalPixels * bpc);
        if (!channelBuf) { free(imgData); fclose(f); return 0; }
        for (int ch = 0; ch < numChannels; ch++) {
            fseek(f, 512 + ch * totalPixels * bpc, SEEK_SET);
            if (fread(channelBuf, bpc, totalPixels, f) != (size_t)totalPixels) break;
            for (int i = 0; i < totalPixels; i++) {
                imgData[i * 4 + ch] = channelBuf[i * bpc + (bpc - 1)];
            }
        }
        free(channelBuf);
    } else {
        // RLE storage - read offset and length tables
        int numRows = (int)ysize * numChannels;
        unsigned int* startTable = (unsigned int*)malloc(numRows * sizeof(unsigned int));
        unsigned int* lenTable   = (unsigned int*)malloc(numRows * sizeof(unsigned int));
        if (!startTable || !lenTable) {
            free(startTable); free(lenTable); free(imgData); fclose(f); return 0;
        }
        fseek(f, 512, SEEK_SET);
        fread(startTable, sizeof(unsigned int), numRows, f);
        fread(lenTable,   sizeof(unsigned int), numRows, f);
        if (swapped) {
            for (int i = 0; i < numRows; i++) {
                startTable[i] = swapInt(startTable[i]);
                lenTable[i]   = swapInt(lenTable[i]);
            }
        }

        unsigned char* rowBuf = (unsigned char*)malloc((int)xsize * 2 + 10);
        unsigned char* decoded = (unsigned char*)malloc((int)xsize + 10);
        if (!rowBuf || !decoded) {
            free(rowBuf); free(decoded); free(startTable); free(lenTable); free(imgData); fclose(f); return 0;
        }

        for (int ch = 0; ch < numChannels; ch++) {
            for (int row = 0; row < (int)ysize; row++) {
                int tableIdx = ch * (int)ysize + row;
                fseek(f, startTable[tableIdx], SEEK_SET);
                int rleLen = (int)lenTable[tableIdx];
                if (rleLen > (int)xsize * 2 + 10) rleLen = (int)xsize * 2 + 10;
                fread(rowBuf, 1, rleLen, f);

                // Decode RLE row
                int outIdx = 0;
                int inIdx  = 0;
                while (outIdx < (int)xsize && inIdx < rleLen) {
                    unsigned char code = rowBuf[inIdx++];
                    int count = code & 0x7F;
                    if (count == 0) break;
                    if (code & 0x80) {
                        // copy next 'count' bytes verbatim
                        for (int k = 0; k < count && outIdx < (int)xsize && inIdx < rleLen; k++) {
                            decoded[outIdx++] = rowBuf[inIdx++];
                        }
                    } else {
                        // repeat next byte 'count' times
                        if (inIdx < rleLen) {
                            unsigned char val = rowBuf[inIdx++];
                            for (int k = 0; k < count && outIdx < (int)xsize; k++) {
                                decoded[outIdx++] = val;
                            }
                        }
                    }
                }

                // Write decoded row into image (SGI stores bottom-up)
                int destRow = row; // keep bottom-up for now, flip on upload
                for (int x = 0; x < outIdx && x < (int)xsize; x++) {
                    imgData[(destRow * (int)xsize + x) * 4 + ch] = decoded[x];
                }
            }
        }

        free(rowBuf);
        free(decoded);
        free(startTable);
        free(lenTable);
    }

    // If grayscale (1 channel), replicate to RGB
    if (numChannels == 1) {
        for (int i = 0; i < totalPixels; i++) {
            unsigned char g = imgData[i * 4 + 0];
            imgData[i * 4 + 1] = g;
            imgData[i * 4 + 2] = g;
            imgData[i * 4 + 3] = 255;
        }
    } else if (numChannels == 2) {
        // gray + alpha
        for (int i = 0; i < totalPixels; i++) {
            unsigned char g = imgData[i * 4 + 0];
            unsigned char a = imgData[i * 4 + 1];
            imgData[i * 4 + 1] = g;
            imgData[i * 4 + 2] = g;
            imgData[i * 4 + 3] = a;
        }
    } else if (numChannels == 3) {
        // ensure alpha = 255
        for (int i = 0; i < totalPixels; i++) {
            imgData[i * 4 + 3] = 255;
        }
    }
    // numChannels == 4: already RGBA

    fclose(f);

    GLuint tex = 0;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)xsize, (GLsizei)ysize, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, imgData);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    free(imgData);
    return tex;
}

GLuint TextureManager::createFallback() {
    // 4x4 white texture
    static GLuint s_fallback = 0;
    if (s_fallback) return s_fallback;
    unsigned char data[4 * 4 * 4];
    memset(data, 255, sizeof(data));
    glGenTextures(1, &s_fallback);
    glBindTexture(GL_TEXTURE_2D, s_fallback);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 4, 4, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    return s_fallback;
}
