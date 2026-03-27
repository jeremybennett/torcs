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
#include <vector>

struct Particle {
    float pos[3];
    float vel[3];
    float color[4];
    float size;
    float life;       // remaining life in seconds
    float maxLife;
};

class ParticleSystem {
public:
    explicit ParticleSystem(int maxParticles);
    ~ParticleSystem();
    void emit(const float pos[3], const float vel[3], const float color[4],
              float size, float life);
    void update(float dt);
    void draw(const float* viewMat, const float* camPos);
    int liveCount() const { return m_liveCount; }
private:
    std::vector<Particle> m_particles;
    int m_maxParticles;
    int m_liveCount;
    bool m_gpuDirty;
    GLuint m_vao, m_vbo;
    void uploadToGPU();
};
