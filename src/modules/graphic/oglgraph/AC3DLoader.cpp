/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "AC3DLoader.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <vector>
#include <string>
#include <array>
#include <tgfclient.h>

// ---- Internal types ----

struct Vec3 { float x, y, z; };
struct Vec2 { float u, v; };

struct AC3DMaterial {
    std::string name;
    float rgb[3];
    float amb[3];
    float emis[3];
    float spec[3];
    float shi;
    float trans;
    AC3DMaterial() : shi(0.0f), trans(0.0f) {
        rgb[0]=rgb[1]=rgb[2]=0.8f;
        amb[0]=amb[1]=amb[2]=0.2f;
        emis[0]=emis[1]=emis[2]=0.0f;
        spec[0]=spec[1]=spec[2]=0.0f;
    }
};

struct AC3DSurface {
    int flags;
    int matIdx;
    struct Ref { int vertIdx; float u, v; };
    std::vector<Ref> refs;
};

struct AC3DObject {
    std::string type;
    std::string name;
    std::string textureName;
    float loc[3];
    float rot[9]; // row-major 3x3, initialized to identity
    std::vector<Vec3> vertices;
    std::vector<AC3DSurface> surfaces;
    std::vector<AC3DObject*> children;
    int matIdx;
    AC3DObject() : matIdx(0) {
        loc[0]=loc[1]=loc[2]=0.0f;
        rot[0]=1; rot[1]=0; rot[2]=0;
        rot[3]=0; rot[4]=1; rot[5]=0;
        rot[6]=0; rot[7]=0; rot[8]=1;
    }
    ~AC3DObject() {
        for (auto c : children) delete c;
    }
};

// ---- Helper functions ----

static void skipSpaces(const char*& s) {
    while (*s == ' ' || *s == '\t') s++;
}

static std::string parseQuoted(const char* s) {
    while (*s && *s != '"') s++;
    if (!*s) return "";
    s++; // skip opening quote
    const char* start = s;
    while (*s && *s != '"') s++;
    return std::string(start, s);
}

static void transformVertex(const Vec3& v, const float rot[9], const float loc[3], Vec3& out) {
    out.x = rot[0]*v.x + rot[1]*v.y + rot[2]*v.z + loc[0];
    out.y = rot[3]*v.x + rot[4]*v.y + rot[5]*v.z + loc[1];
    out.z = rot[6]*v.x + rot[7]*v.y + rot[8]*v.z + loc[2];
}

// ---- Parser ----

static AC3DObject* parseObject(FILE* f, const std::vector<AC3DMaterial>& materials,
                                const std::string& texBase, char* line, int lineLen);

static bool parseMaterial(const char* s, AC3DMaterial& mat) {
    // Format: MATERIAL "name" rgb R G B  amb R G B  emis R G B  spec R G B  shi S  trans T
    char name[256] = "";
    mat = AC3DMaterial();
    const char* p = s;
    // name
    while (*p && *p != '"') p++;
    if (*p == '"') {
        p++;
        int i = 0;
        while (*p && *p != '"' && i < 255) name[i++] = *p++;
        name[i] = 0;
        if (*p == '"') p++;
    }
    mat.name = name;
    // parse key-value pairs
    while (*p) {
        while (*p == ' ' || *p == '\t') p++;
        if (strncmp(p, "rgb", 3) == 0) {
            p += 3;
            sscanf(p, " %f %f %f", &mat.rgb[0], &mat.rgb[1], &mat.rgb[2]);
        } else if (strncmp(p, "amb", 3) == 0) {
            p += 3;
            sscanf(p, " %f %f %f", &mat.amb[0], &mat.amb[1], &mat.amb[2]);
        } else if (strncmp(p, "emis", 4) == 0) {
            p += 4;
            sscanf(p, " %f %f %f", &mat.emis[0], &mat.emis[1], &mat.emis[2]);
        } else if (strncmp(p, "spec", 4) == 0) {
            p += 4;
            sscanf(p, " %f %f %f", &mat.spec[0], &mat.spec[1], &mat.spec[2]);
        } else if (strncmp(p, "shi", 3) == 0) {
            p += 3;
            sscanf(p, " %f", &mat.shi);
        } else if (strncmp(p, "trans", 5) == 0) {
            p += 5;
            sscanf(p, " %f", &mat.trans);
        }
        // advance past current token
        while (*p && *p != ' ' && *p != '\t') p++;
    }
    return true;
}

static void buildMeshFromObject(const AC3DObject* obj,
                                 const std::vector<AC3DMaterial>& materials,
                                 const std::string& texBase,
                                 std::vector<std::shared_ptr<Mesh>>& outMeshes)
{
    if (obj->surfaces.empty()) {
        for (auto c : obj->children)
            buildMeshFromObject(c, materials, texBase, outMeshes);
        return;
    }

    // Triangulate all surfaces -> vertices with normals and UVs
    std::vector<Vertex> verts;
    std::vector<unsigned int> indices;

    for (const auto& surf : obj->surfaces) {
        if (surf.refs.size() < 3) continue;
        // Fan triangulation from vertex 0
        for (size_t i = 1; i + 1 < surf.refs.size(); i++) {
            const AC3DSurface::Ref& r0 = surf.refs[0];
            const AC3DSurface::Ref& r1 = surf.refs[i];
            const AC3DSurface::Ref& r2 = surf.refs[i+1];

            if (r0.vertIdx < 0 || r0.vertIdx >= (int)obj->vertices.size()) continue;
            if (r1.vertIdx < 0 || r1.vertIdx >= (int)obj->vertices.size()) continue;
            if (r2.vertIdx < 0 || r2.vertIdx >= (int)obj->vertices.size()) continue;

            // Transform vertices by object local transform
            Vec3 p0, p1, p2;
            transformVertex(obj->vertices[r0.vertIdx], obj->rot, obj->loc, p0);
            transformVertex(obj->vertices[r1.vertIdx], obj->rot, obj->loc, p1);
            transformVertex(obj->vertices[r2.vertIdx], obj->rot, obj->loc, p2);

            // Compute face normal
            float e1[3] = { p1.x-p0.x, p1.y-p0.y, p1.z-p0.z };
            float e2[3] = { p2.x-p0.x, p2.y-p0.y, p2.z-p0.z };
            float n[3] = {
                e1[1]*e2[2] - e1[2]*e2[1],
                e1[2]*e2[0] - e1[0]*e2[2],
                e1[0]*e2[1] - e1[1]*e2[0]
            };
            float nlen = sqrtf(n[0]*n[0]+n[1]*n[1]+n[2]*n[2]);
            if (nlen > 1e-6f) { n[0]/=nlen; n[1]/=nlen; n[2]/=nlen; }

            Vertex v0, v1, v2;
            v0.pos[0]=p0.x; v0.pos[1]=p0.y; v0.pos[2]=p0.z;
            v1.pos[0]=p1.x; v1.pos[1]=p1.y; v1.pos[2]=p1.z;
            v2.pos[0]=p2.x; v2.pos[1]=p2.y; v2.pos[2]=p2.z;

            for (int j = 0; j < 3; j++) {
                v0.normal[j] = n[j];
                v1.normal[j] = n[j];
                v2.normal[j] = n[j];
            }

            v0.texCoord[0]=r0.u; v0.texCoord[1]=r0.v;
            v1.texCoord[0]=r1.u; v1.texCoord[1]=r1.v;
            v2.texCoord[0]=r2.u; v2.texCoord[1]=r2.v;

            for (int j = 0; j < 4; j++) {
                v0.texCoord2[j%2] = 0.0f;
                v1.texCoord2[j%2] = 0.0f;
                v2.texCoord2[j%2] = 0.0f;
            }
            v0.texCoord2[0]=v0.texCoord2[1]=0.0f;
            v1.texCoord2[0]=v1.texCoord2[1]=0.0f;
            v2.texCoord2[0]=v2.texCoord2[1]=0.0f;

            unsigned int base = (unsigned int)verts.size();
            verts.push_back(v0);
            verts.push_back(v1);
            verts.push_back(v2);
            indices.push_back(base);
            indices.push_back(base+1);
            indices.push_back(base+2);
        }
    }

    if (verts.empty()) {
        for (auto c : obj->children)
            buildMeshFromObject(c, materials, texBase, outMeshes);
        return;
    }

    auto mesh = std::make_shared<Mesh>();
    mesh->upload(verts, indices);

    // Set texture path
    if (!obj->textureName.empty()) {
        mesh->texturePath = texBase + obj->textureName;
    }

    // Set material from first surface's material index
    int mIdx = obj->surfaces.empty() ? 0 : obj->surfaces[0].matIdx;
    if (mIdx >= 0 && mIdx < (int)materials.size()) {
        const AC3DMaterial& mat = materials[mIdx];
        mesh->ambient[0]  = mat.amb[0];  mesh->ambient[1]  = mat.amb[1];  mesh->ambient[2]  = mat.amb[2];  mesh->ambient[3]  = 1.0f;
        mesh->diffuse[0]  = mat.rgb[0];  mesh->diffuse[1]  = mat.rgb[1];  mesh->diffuse[2]  = mat.rgb[2];  mesh->diffuse[3]  = 1.0f - mat.trans;
        mesh->specular[0] = mat.spec[0]; mesh->specular[1] = mat.spec[1]; mesh->specular[2] = mat.spec[2]; mesh->specular[3] = 1.0f;
        mesh->shininess   = mat.shi;
        mesh->transparent = mat.trans > 0.01f;
        mesh->materialName = mat.name;
    } else {
        mesh->ambient[0]=mesh->ambient[1]=mesh->ambient[2]=0.2f; mesh->ambient[3]=1.0f;
        mesh->diffuse[0]=mesh->diffuse[1]=mesh->diffuse[2]=0.8f; mesh->diffuse[3]=1.0f;
        mesh->specular[0]=mesh->specular[1]=mesh->specular[2]=0.0f; mesh->specular[3]=1.0f;
        mesh->shininess = 32.0f;
    }

    outMeshes.push_back(mesh);

    for (auto c : obj->children)
        buildMeshFromObject(c, materials, texBase, outMeshes);
}

static AC3DObject* parseObject(FILE* f, const std::vector<AC3DMaterial>& materials,
                                const std::string& texBase, char* line, int lineLen)
{
    AC3DObject* obj = new AC3DObject();

    // type is in the same line as OBJECT
    const char* p = line + strlen("OBJECT");
    while (*p == ' ' || *p == '\t') p++;
    obj->type = std::string(p);
    // trim trailing whitespace/newline
    while (!obj->type.empty() && (obj->type.back() == '\n' || obj->type.back() == '\r' || obj->type.back() == ' '))
        obj->type.pop_back();

    while (fgets(line, lineLen, f)) {
        // Strip trailing newline
        char* nl = strchr(line, '\n');
        if (nl) *nl = '\0';
        char* cr = strchr(line, '\r');
        if (cr) *cr = '\0';

        if (strncmp(line, "name", 4) == 0) {
            obj->name = parseQuoted(line + 4);
        } else if (strncmp(line, "texture ", 8) == 0) {
            obj->textureName = parseQuoted(line + 8);
        } else if (strncmp(line, "loc", 3) == 0) {
            sscanf(line + 3, " %f %f %f", &obj->loc[0], &obj->loc[1], &obj->loc[2]);
        } else if (strncmp(line, "rot", 3) == 0) {
            sscanf(line + 3, " %f %f %f %f %f %f %f %f %f",
                   &obj->rot[0], &obj->rot[1], &obj->rot[2],
                   &obj->rot[3], &obj->rot[4], &obj->rot[5],
                   &obj->rot[6], &obj->rot[7], &obj->rot[8]);
        } else if (strncmp(line, "numvert", 7) == 0) {
            int n = 0;
            sscanf(line + 7, " %d", &n);
            obj->vertices.resize(n);
            for (int i = 0; i < n; i++) {
                if (!fgets(line, lineLen, f)) break;
                sscanf(line, "%f %f %f", &obj->vertices[i].x, &obj->vertices[i].y, &obj->vertices[i].z);
            }
        } else if (strncmp(line, "numsurf", 7) == 0) {
            int ns = 0;
            sscanf(line + 7, " %d", &ns);
            obj->surfaces.resize(ns);
            for (int si = 0; si < ns; si++) {
                AC3DSurface& surf = obj->surfaces[si];
                surf.flags  = 0;
                surf.matIdx = 0;
                // Read SURF line
                while (fgets(line, lineLen, f)) {
                    if (line[0] == '\n' || line[0] == '\r') continue;
                    nl = strchr(line, '\n'); if (nl) *nl='\0';
                    cr = strchr(line, '\r'); if (cr) *cr='\0';
                    if (strncmp(line, "SURF", 4) == 0) {
                        unsigned int flags = 0;
                        sscanf(line + 4, " %x", &flags);
                        surf.flags = (int)flags;
                    } else if (strncmp(line, "mat", 3) == 0) {
                        sscanf(line + 3, " %d", &surf.matIdx);
                    } else if (strncmp(line, "refs", 4) == 0) {
                        int nr = 0;
                        sscanf(line + 4, " %d", &nr);
                        surf.refs.resize(nr);
                        for (int ri = 0; ri < nr; ri++) {
                            if (!fgets(line, lineLen, f)) break;
                            sscanf(line, "%d %f %f",
                                   &surf.refs[ri].vertIdx,
                                   &surf.refs[ri].u,
                                   &surf.refs[ri].v);
                        }
                        break; // done with this surface
                    }
                }
            }
        } else if (strncmp(line, "kids", 4) == 0) {
            int nkids = 0;
            sscanf(line + 4, " %d", &nkids);
            for (int ki = 0; ki < nkids; ki++) {
                // Find next OBJECT line
                while (fgets(line, lineLen, f)) {
                    nl = strchr(line, '\n'); if (nl) *nl='\0';
                    cr = strchr(line, '\r'); if (cr) *cr='\0';
                    if (strncmp(line, "OBJECT", 6) == 0) {
                        AC3DObject* child = parseObject(f, materials, texBase, line, lineLen);
                        obj->children.push_back(child);
                        break;
                    }
                }
            }
            break; // kids is last token in an object
        }
    }
    return obj;
}

AC3DModel* AC3DLoader::load(const std::string& filepath, const std::string& textureBasePath) {
    FILE* f = fopen(filepath.c_str(), "r");
    if (!f) {
        GfOut("AC3DLoader::load: cannot open '%s'\n", filepath.c_str());
        return nullptr;
    }

    const int LINE_LEN = 4096;
    char line[LINE_LEN];

    // Check magic
    if (!fgets(line, LINE_LEN, f)) { fclose(f); return nullptr; }
    if (strncmp(line, "AC3Db", 5) != 0) {
        GfOut("AC3DLoader::load: not an AC3D file '%s'\n", filepath.c_str());
        fclose(f);
        return nullptr;
    }

    std::vector<AC3DMaterial> materials;
    std::vector<AC3DObject*>  objects;

    while (fgets(line, LINE_LEN, f)) {
        // Strip trailing newlines
        char* nl = strchr(line, '\n'); if (nl) *nl='\0';
        char* cr = strchr(line, '\r'); if (cr) *cr='\0';
        if (line[0] == '\0') continue;

        if (strncmp(line, "MATERIAL", 8) == 0) {
            AC3DMaterial mat;
            parseMaterial(line + 8, mat);
            materials.push_back(mat);
        } else if (strncmp(line, "OBJECT", 6) == 0) {
            AC3DObject* obj = parseObject(f, materials, textureBasePath, line, LINE_LEN);
            objects.push_back(obj);
        }
    }
    fclose(f);

    AC3DModel* model = new AC3DModel();
    for (auto obj : objects) {
        buildMeshFromObject(obj, materials, textureBasePath, model->meshes);
        delete obj;
    }

    GfOut("AC3DLoader::load: loaded '%s' -> %d meshes\n",
          filepath.c_str(), (int)model->meshes.size());
    return model;
}
