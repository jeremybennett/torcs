/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "SkidMarks.h"
#include <cstring>
#include <cmath>

// 8 floats per vertex: x,y,z,nx,ny,nz,u,v
static const int FLOATS_PER_VERT = 8;

SkidMarkSystem::SkidMarkSystem(int maxStrips, int maxPointsPerStrip)
    : m_maxStrips(maxStrips), m_maxPts(maxPointsPerStrip),
      m_vao(0), m_vbo(0), m_dirty(false)
{
    m_strips.resize(maxStrips);
    for (auto& s : m_strips) {
        s.vertCount = 0;
        s.alpha     = 1.0f;
        s.active    = false;
    }

    int maxVerts = maxStrips * maxPointsPerStrip * 2;
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, maxVerts * FLOATS_PER_VERT * sizeof(float),
                 NULL, GL_DYNAMIC_DRAW);

    // attrib 0: pos(3f)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, FLOATS_PER_VERT * sizeof(float), (void*)0);
    // attrib 1: normal(3f)
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, FLOATS_PER_VERT * sizeof(float),
                          (void*)(3 * sizeof(float)));
    // attrib 2: texcoord(2f)
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, FLOATS_PER_VERT * sizeof(float),
                          (void*)(6 * sizeof(float)));
    glBindVertexArray(0);
}

SkidMarkSystem::~SkidMarkSystem() {
    if (m_vao) { glDeleteVertexArrays(1, &m_vao); m_vao = 0; }
    if (m_vbo) { glDeleteBuffers(1, &m_vbo); m_vbo = 0; }
}

void SkidMarkSystem::startStrip(int wheelIdx) {
    // Find inactive slot
    for (int i = 0; i < m_maxStrips; i++) {
        if (!m_strips[i].active) {
            m_strips[i].active   = true;
            m_strips[i].vertCount = 0;
            m_strips[i].alpha    = 1.0f;
            m_strips[i].vertices.clear();
            m_activeStrip[wheelIdx] = i;
            return;
        }
    }
    // No free slot – reuse oldest active strip (strip 0)
    m_strips[0].vertCount = 0;
    m_strips[0].vertices.clear();
    m_strips[0].active = true;
    m_activeStrip[wheelIdx] = 0;
}

void SkidMarkSystem::addPoint(int wheelIdx, float x, float y, float z,
                               float nx, float ny, float nz, float width) {
    auto it = m_activeStrip.find(wheelIdx);
    if (it == m_activeStrip.end()) return;
    int idx = it->second;
    SkidStrip& strip = m_strips[idx];
    if (strip.vertCount >= m_maxPts * 2) return;

    // Compute perpendicular direction in XY plane
    float px = -ny, py = nx; // rotate normal 90 degrees in XY
    float plen = sqrtf(px*px + py*py);
    if (plen > 1e-6f) { px /= plen; py /= plen; }

    float hw = width * 0.5f;
    float u  = strip.vertCount > 0 ? (float)(strip.vertCount / 2) * 0.1f : 0.0f;

    // Left vertex
    strip.vertices.push_back(x - px * hw);
    strip.vertices.push_back(y - py * hw);
    strip.vertices.push_back(z);
    strip.vertices.push_back(nx); strip.vertices.push_back(ny); strip.vertices.push_back(nz);
    strip.vertices.push_back(0.0f); strip.vertices.push_back(u);

    // Right vertex
    strip.vertices.push_back(x + px * hw);
    strip.vertices.push_back(y + py * hw);
    strip.vertices.push_back(z);
    strip.vertices.push_back(nx); strip.vertices.push_back(ny); strip.vertices.push_back(nz);
    strip.vertices.push_back(1.0f); strip.vertices.push_back(u);

    strip.vertCount += 2;
    m_dirty = true;
}

void SkidMarkSystem::endStrip(int wheelIdx) {
    m_activeStrip.erase(wheelIdx);
}

void SkidMarkSystem::draw() {
    if (!m_dirty) return;
    m_dirty = false;

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    GLintptr offset = 0;
    int maxVertsPerStrip = m_maxPts * 2;

    for (const auto& strip : m_strips) {
        if (strip.vertCount < 2) {
            offset += maxVertsPerStrip * FLOATS_PER_VERT * sizeof(float);
            continue;
        }
        int uploadVerts = strip.vertCount;
        glBufferSubData(GL_ARRAY_BUFFER, offset,
                        uploadVerts * FLOATS_PER_VERT * sizeof(float),
                        strip.vertices.data());
        offset += maxVertsPerStrip * FLOATS_PER_VERT * sizeof(float);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(m_vao);
    GLint drawOffset = 0;
    for (const auto& strip : m_strips) {
        if (strip.vertCount >= 2) {
            glDrawArrays(GL_TRIANGLE_STRIP, drawOffset, strip.vertCount);
        }
        drawOffset += maxVertsPerStrip;
    }
    glBindVertexArray(0);
}

void SkidMarkSystem::clear() {
    for (auto& s : m_strips) {
        s.active    = false;
        s.vertCount = 0;
        s.vertices.clear();
    }
    m_activeStrip.clear();
    m_dirty = false;
}
