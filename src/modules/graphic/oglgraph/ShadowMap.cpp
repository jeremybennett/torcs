/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "ShadowMap.h"
#include <cmath>
#include <cstring>
#include <tgfclient.h>

static inline float dot3sm(const float* a, const float* b) {
    return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
}
static inline void cross3sm(const float* a, const float* b, float* out) {
    out[0] = a[1]*b[2] - a[2]*b[1];
    out[1] = a[2]*b[0] - a[0]*b[2];
    out[2] = a[0]*b[1] - a[1]*b[0];
}
static inline void normalize3sm(float* v) {
    float len = sqrtf(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
    if (len > 1e-6f) { v[0]/=len; v[1]/=len; v[2]/=len; }
}
static void mulMat4sm(const float* a, const float* b, float* out) {
    for (int col = 0; col < 4; col++) {
        for (int row = 0; row < 4; row++) {
            float v = 0.0f;
            for (int k = 0; k < 4; k++) {
                v += a[k*4+row] * b[col*4+k];
            }
            out[col*4+row] = v;
        }
    }
}

ShadowMap::ShadowMap() : m_fbo(0), m_depthTex(0), m_size(1024) {}

ShadowMap::~ShadowMap() {
    if (m_depthTex) { glDeleteTextures(1, &m_depthTex); m_depthTex = 0; }
    if (m_fbo)      { glDeleteFramebuffers(1, &m_fbo);  m_fbo = 0; }
}

bool ShadowMap::init(int size) {
    m_size = size;
    glGenFramebuffers(1, &m_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

    glGenTextures(1, &m_depthTex);
    glBindTexture(GL_TEXTURE_2D, m_depthTex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, size, size, 0,
                 GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthTex, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    if (status != GL_FRAMEBUFFER_COMPLETE) {
        GfOut("ShadowMap::init: framebuffer incomplete (status=%d)\n", (int)status);
        return false;
    }
    return true;
}

void ShadowMap::bindForWriting() {
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    glViewport(0, 0, m_size, m_size);
    glClear(GL_DEPTH_BUFFER_BIT);
}

void ShadowMap::bindForReading(int textureUnit) {
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D, m_depthTex);
}

void ShadowMap::getLightSpaceMatrix(const float lightDir[3], const float /*sceneBounds*/[6], float* mat16) {
    // Build orthographic light-view from direction
    float ld[3] = { lightDir[0], lightDir[1], lightDir[2] };
    normalize3sm(ld);

    // Light position: pushed back along negative light direction
    float lightPos[3] = { -ld[0]*100.0f, -ld[1]*100.0f, -ld[2]*100.0f };
    float target[3]   = { 0.0f, 0.0f, 0.0f };

    // Build look-at for light
    float f[3] = { target[0]-lightPos[0], target[1]-lightPos[1], target[2]-lightPos[2] };
    normalize3sm(f);
    float worldUp[3] = { 0.0f, 0.0f, 1.0f };
    // Avoid parallel case
    if (fabsf(dot3sm(f, worldUp)) > 0.99f) worldUp[1] = 1.0f, worldUp[2] = 0.0f;
    float r[3]; cross3sm(f, worldUp, r); normalize3sm(r);
    float u[3]; cross3sm(r, f, u);

    float viewMat[16] = {
         r[0],  u[0], -f[0], 0.0f,
         r[1],  u[1], -f[1], 0.0f,
         r[2],  u[2], -f[2], 0.0f,
        -dot3sm(r, lightPos), -dot3sm(u, lightPos),  dot3sm(f, lightPos), 1.0f
    };

    // Orthographic projection
    float left=-100.0f, right=100.0f, bot=-100.0f, top=100.0f, near=1.0f, far=200.0f;
    float orthoMat[16];
    memset(orthoMat, 0, sizeof(orthoMat));
    orthoMat[0]  = 2.0f / (right - left);
    orthoMat[5]  = 2.0f / (top - bot);
    orthoMat[10] = -2.0f / (far - near);
    orthoMat[12] = -(right + left) / (right - left);
    orthoMat[13] = -(top + bot)   / (top - bot);
    orthoMat[14] = -(far + near)  / (far - near);
    orthoMat[15] = 1.0f;

    mulMat4sm(orthoMat, viewMat, mat16);
}
