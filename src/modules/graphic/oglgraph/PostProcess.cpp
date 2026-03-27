/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "PostProcess.h"
#include "Shader.h"
#include <cstring>
#include <tgfclient.h>

// Bloom shaders are owned by OGLRenderer; PostProcess keeps pointers
// We pass them as extern references set before use.
extern Shader* g_postShader;
extern Shader* g_bloomShader;

PostProcess::PostProcess()
    : m_fbo(0), m_rbo(0), m_quadVAO(0), m_quadVBO(0),
      m_width(800), m_height(600), m_initialized(false)
{
    memset(m_colorBufs, 0, sizeof(m_colorBufs));
    memset(m_pingpongFBO,  0, sizeof(m_pingpongFBO));
    memset(m_pingpongBufs, 0, sizeof(m_pingpongBufs));
}

PostProcess::~PostProcess() {
    cleanup();
}

static GLuint createHDRTexture(int w, int h) {
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, w, h, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, 0);
    return tex;
}

bool PostProcess::init(int width, int height) {
    m_width  = width;
    m_height = height;

    // Create main HDR framebuffer with 2 color attachments
    glGenFramebuffers(1, &m_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

    for (int i = 0; i < 2; i++) {
        m_colorBufs[i] = createHDRTexture(width, height);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i,
                               GL_TEXTURE_2D, m_colorBufs[i], 0);
    }

    // Depth renderbuffer
    glGenRenderbuffers(1, &m_rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_rbo);

    GLenum attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
    glDrawBuffers(2, attachments);

    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE) {
        GfOut("PostProcess::init: main HDR framebuffer incomplete (%d)\n", (int)status);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        return false;
    }

    // Create ping-pong FBOs for bloom blur
    glGenFramebuffers(2, m_pingpongFBO);
    for (int i = 0; i < 2; i++) {
        glBindFramebuffer(GL_FRAMEBUFFER, m_pingpongFBO[i]);
        m_pingpongBufs[i] = createHDRTexture(width, height);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                               GL_TEXTURE_2D, m_pingpongBufs[i], 0);
        GLenum ppStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (ppStatus != GL_FRAMEBUFFER_COMPLETE) {
            GfOut("PostProcess::init: ping-pong FBO %d incomplete (%d)\n", i, (int)ppStatus);
        }
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    setupQuad();
    m_initialized = true;
    return true;
}

void PostProcess::setupQuad() {
    // Full-screen quad: two triangles, positions in NDC, tex coords 0..1
    float verts[] = {
        // pos(2f)  texcoord(2f)
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };
    glGenVertexArrays(1, &m_quadVAO);
    glGenBuffers(1, &m_quadVBO);
    glBindVertexArray(m_quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glBindVertexArray(0);
}

void PostProcess::bindHDRFramebuffer() {
    if (!m_initialized) return;
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    glViewport(0, 0, m_width, m_height);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void PostProcess::renderBloom() {
    if (!g_bloomShader || !g_bloomShader->id()) return;

    bool horizontal = true;
    int passes = 10; // 5 passes each direction
    g_bloomShader->use();
    g_bloomShader->setInt("image", 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_colorBufs[1]); // bright-pass source

    for (int i = 0; i < passes; i++) {
        glBindFramebuffer(GL_FRAMEBUFFER, m_pingpongFBO[horizontal ? 1 : 0]);
        g_bloomShader->setInt("horizontal", horizontal ? 1 : 0);
        glBindTexture(GL_TEXTURE_2D, i == 0 ? m_colorBufs[1] : m_pingpongBufs[horizontal ? 0 : 1]);
        glBindVertexArray(m_quadVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
        horizontal = !horizontal;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void PostProcess::render(float exposure) {
    if (!m_initialized) return;

    renderBloom();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (!g_postShader || !g_postShader->id()) return;

    g_postShader->use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_colorBufs[0]);
    g_postShader->setInt("hdrBuffer", 0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_pingpongBufs[0]);
    g_postShader->setInt("bloomBlur", 1);
    g_postShader->setFloat("exposure", exposure);

    glBindVertexArray(m_quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void PostProcess::resize(int width, int height) {
    if (m_width == width && m_height == height) return;
    cleanup();
    init(width, height);
}

void PostProcess::cleanup() {
    if (m_fbo) { glDeleteFramebuffers(1, &m_fbo); m_fbo = 0; }
    if (m_colorBufs[0]) { glDeleteTextures(2, m_colorBufs); m_colorBufs[0]=m_colorBufs[1]=0; }
    if (m_rbo) { glDeleteRenderbuffers(1, &m_rbo); m_rbo = 0; }
    if (m_pingpongFBO[0]) { glDeleteFramebuffers(2, m_pingpongFBO); m_pingpongFBO[0]=m_pingpongFBO[1]=0; }
    if (m_pingpongBufs[0]) { glDeleteTextures(2, m_pingpongBufs); m_pingpongBufs[0]=m_pingpongBufs[1]=0; }
    if (m_quadVAO) { glDeleteVertexArrays(1, &m_quadVAO); m_quadVAO = 0; }
    if (m_quadVBO) { glDeleteBuffers(1, &m_quadVBO); m_quadVBO = 0; }
    m_initialized = false;
}
