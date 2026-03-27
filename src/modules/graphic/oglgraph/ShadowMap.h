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

class ShadowMap {
public:
    ShadowMap();
    ~ShadowMap();
    bool init(int size);
    void bindForWriting();
    void bindForReading(int textureUnit);
    void getLightSpaceMatrix(const float lightDir[3], const float sceneBounds[6], float* mat16);
    int size() const { return m_size; }
private:
    GLuint m_fbo;
    GLuint m_depthTex;
    int m_size;
};
