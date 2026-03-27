/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#pragma once
#include "gl3.h"

class PostProcess {
public:
    PostProcess();
    ~PostProcess();
    bool init(int width, int height);
    void bindHDRFramebuffer();
    void render(float exposure);
    void resize(int width, int height);
    void cleanup();
private:
    GLuint m_fbo;
    GLuint m_colorBufs[2];  // 0 = scene HDR, 1 = bright
    GLuint m_rbo;           // depth renderbuffer
    GLuint m_pingpongFBO[2];
    GLuint m_pingpongBufs[2];
    GLuint m_quadVAO, m_quadVBO;
    int m_width, m_height;
    bool m_initialized;
    void setupQuad();
    void renderBloom();
};
