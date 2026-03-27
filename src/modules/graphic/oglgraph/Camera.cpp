/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "Camera.h"
#include <cstring>
#include <cmath>

static inline float dot3(const float* a, const float* b) {
    return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
}

static inline void cross3(const float* a, const float* b, float* out) {
    out[0] = a[1]*b[2] - a[2]*b[1];
    out[1] = a[2]*b[0] - a[0]*b[2];
    out[2] = a[0]*b[1] - a[1]*b[0];
}

static inline void normalize3(float* v) {
    float len = sqrtf(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
    if (len > 1e-6f) { v[0] /= len; v[1] /= len; v[2] /= len; }
}

Camera::Camera()
    : m_fovY(60.0f), m_aspect(4.0f/3.0f), m_near(0.1f), m_far(3000.0f)
{
    m_pos[0] = 0.0f; m_pos[1] = -10.0f; m_pos[2] = 3.0f;
    m_target[0] = 0.0f; m_target[1] = 0.0f; m_target[2] = 0.5f;
    m_up[0] = 0.0f; m_up[1] = 0.0f; m_up[2] = 1.0f;
}

void Camera::setPosition(float x, float y, float z) { m_pos[0]=x; m_pos[1]=y; m_pos[2]=z; }
void Camera::setTarget(float x, float y, float z)   { m_target[0]=x; m_target[1]=y; m_target[2]=z; }
void Camera::setUp(float x, float y, float z)       { m_up[0]=x; m_up[1]=y; m_up[2]=z; }
void Camera::setPerspective(float fovYdeg, float aspect, float nearZ, float farZ) {
    m_fovY = fovYdeg; m_aspect = aspect; m_near = nearZ; m_far = farZ;
}

void Camera::getPosition(float* xyz) const {
    xyz[0] = m_pos[0]; xyz[1] = m_pos[1]; xyz[2] = m_pos[2];
}

void Camera::getViewMatrix(float* mat16) const { buildLookAt(mat16); }
void Camera::getProjectionMatrix(float* mat16) const { buildPerspective(mat16); }

void Camera::buildLookAt(float* m) const {
    float f[3] = { m_target[0]-m_pos[0], m_target[1]-m_pos[1], m_target[2]-m_pos[2] };
    normalize3(f);

    float r[3];
    float up[3] = { m_up[0], m_up[1], m_up[2] };
    cross3(f, up, r);
    normalize3(r);

    float u[3];
    cross3(r, f, u);

    // Column-major look-at matrix
    m[0]  =  r[0];  m[1]  =  u[0];  m[2]  = -f[0];  m[3]  = 0.0f;
    m[4]  =  r[1];  m[5]  =  u[1];  m[6]  = -f[1];  m[7]  = 0.0f;
    m[8]  =  r[2];  m[9]  =  u[2];  m[10] = -f[2];  m[11] = 0.0f;
    m[12] = -dot3(r, m_pos);
    m[13] = -dot3(u, m_pos);
    m[14] =  dot3(f, m_pos);
    m[15] = 1.0f;
}

void Camera::buildPerspective(float* m) const {
    float fovRad = m_fovY * 3.14159265358979323846f / 180.0f;
    float f = 1.0f / tanf(fovRad * 0.5f);
    float nf = m_near - m_far;

    memset(m, 0, 16 * sizeof(float));
    m[0]  = f / m_aspect;
    m[5]  = f;
    m[10] = (m_far + m_near) / nf;
    m[11] = -1.0f;
    m[14] = (2.0f * m_far * m_near) / nf;
}
