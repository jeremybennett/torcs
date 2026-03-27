/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "Particles.h"
#include <cstring>

// Layout per particle in VBO: pos(3f) + color(4f) + size(1f) = 8 floats
static const int FLOATS_PER_PARTICLE = 8;

ParticleSystem::ParticleSystem(int maxParticles)
    : m_maxParticles(maxParticles), m_liveCount(0), m_gpuDirty(false),
      m_vao(0), m_vbo(0)
{
    m_particles.resize(maxParticles);
    for (auto& p : m_particles) {
        memset(&p, 0, sizeof(p));
        p.life = -1.0f; // mark dead
    }

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);

    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, maxParticles * FLOATS_PER_PARTICLE * sizeof(float),
                 NULL, GL_DYNAMIC_DRAW);

    // attrib 0: pos (3f)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, FLOATS_PER_PARTICLE * sizeof(float), (void*)0);
    // attrib 1: color (4f)
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, FLOATS_PER_PARTICLE * sizeof(float),
                          (void*)(3 * sizeof(float)));
    // attrib 2: size (1f)
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, FLOATS_PER_PARTICLE * sizeof(float),
                          (void*)(7 * sizeof(float)));

    glBindVertexArray(0);
}

ParticleSystem::~ParticleSystem() {
    if (m_vao) { glDeleteVertexArrays(1, &m_vao); m_vao = 0; }
    if (m_vbo) { glDeleteBuffers(1, &m_vbo); m_vbo = 0; }
}

void ParticleSystem::emit(const float pos[3], const float vel[3], const float color[4],
                           float size, float life) {
    // Find a dead particle slot
    for (auto& p : m_particles) {
        if (p.life <= 0.0f) {
            p.pos[0] = pos[0]; p.pos[1] = pos[1]; p.pos[2] = pos[2];
            p.vel[0] = vel[0]; p.vel[1] = vel[1]; p.vel[2] = vel[2];
            p.color[0] = color[0]; p.color[1] = color[1];
            p.color[2] = color[2]; p.color[3] = color[3];
            p.size    = size;
            p.life    = life;
            p.maxLife = life;
            m_gpuDirty = true;
            return;
        }
    }
}

void ParticleSystem::update(float dt) {
    m_liveCount = 0;
    for (auto& p : m_particles) {
        if (p.life <= 0.0f) continue;
        p.pos[0] += p.vel[0] * dt;
        p.pos[1] += p.vel[1] * dt;
        p.pos[2] += p.vel[2] * dt;
        p.life   -= dt;
        // Fade alpha as life decreases
        if (p.maxLife > 0.0f)
            p.color[3] = p.life / p.maxLife;
        if (p.life > 0.0f) m_liveCount++;
    }
    if (m_liveCount > 0) m_gpuDirty = true;
}

void ParticleSystem::uploadToGPU() {
    if (!m_gpuDirty) return;
    m_gpuDirty = false;

    // Build compact live-particle array
    std::vector<float> buf;
    buf.reserve(m_liveCount * FLOATS_PER_PARTICLE);
    for (const auto& p : m_particles) {
        if (p.life <= 0.0f) continue;
        buf.push_back(p.pos[0]); buf.push_back(p.pos[1]); buf.push_back(p.pos[2]);
        buf.push_back(p.color[0]); buf.push_back(p.color[1]);
        buf.push_back(p.color[2]); buf.push_back(p.color[3]);
        buf.push_back(p.size);
    }
    int count = (int)(buf.size() / FLOATS_PER_PARTICLE);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, count * FLOATS_PER_PARTICLE * sizeof(float), buf.data());
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ParticleSystem::draw(const float* /*viewMat*/, const float* /*camPos*/) {
    if (m_liveCount <= 0) return;
    uploadToGPU();

    glEnable(GL_PROGRAM_POINT_SIZE);
    glDepthMask(GL_FALSE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    glBindVertexArray(m_vao);
    glDrawArrays(GL_POINTS, 0, m_liveCount);
    glBindVertexArray(0);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_BLEND);
    glDepthMask(GL_TRUE);
    glDisable(GL_PROGRAM_POINT_SIZE);
}
