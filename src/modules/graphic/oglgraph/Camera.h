/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#pragma once
#include <cmath>

class Camera {
public:
    Camera();
    void setPosition(float x, float y, float z);
    void setTarget(float x, float y, float z);
    void setUp(float x, float y, float z);
    void setPerspective(float fovYdeg, float aspect, float nearZ, float farZ);
    void getViewMatrix(float* mat16) const;
    void getProjectionMatrix(float* mat16) const;
    void getPosition(float* xyz) const;
private:
    float m_pos[3];
    float m_target[3];
    float m_up[3];
    float m_fovY;
    float m_aspect;
    float m_near;
    float m_far;
    void buildLookAt(float* mat16) const;
    void buildPerspective(float* mat16) const;
};
