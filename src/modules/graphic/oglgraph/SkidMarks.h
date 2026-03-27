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
#include <map>
#include <string>

struct SkidStrip {
    std::vector<float> vertices; // x,y,z,nx,ny,nz,u,v per vertex
    int vertCount;
    float alpha;
    bool active;
};

class SkidMarkSystem {
public:
    SkidMarkSystem(int maxStrips, int maxPointsPerStrip);
    ~SkidMarkSystem();
    void startStrip(int wheelIdx);
    void addPoint(int wheelIdx, float x, float y, float z,
                  float nx, float ny, float nz, float width);
    void endStrip(int wheelIdx);
    void draw();
    void clear();
private:
    int m_maxStrips, m_maxPts;
    std::vector<SkidStrip> m_strips;
    std::map<int, int> m_activeStrip; // wheelIdx -> strip index
    GLuint m_vao, m_vbo;
    bool m_dirty;
};
