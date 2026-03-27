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
#include <string>
#include <cstddef>

struct Vertex {
    float pos[3];
    float normal[3];
    float texCoord[2];
    float texCoord2[2];
};

class Mesh {
public:
    Mesh();
    ~Mesh();
    void upload(const std::vector<Vertex>& verts, const std::vector<unsigned int>& indices);
    void draw() const;
    void drawInstanced(int count) const;
    int indexCount() const { return m_indexCount; }
    bool valid() const { return m_vao != 0; }

    std::string materialName;
    std::string texturePath;
    std::string texture2Path;
    float ambient[4];
    float diffuse[4];
    float specular[4];
    float shininess;
    bool transparent;

private:
    GLuint m_vao, m_vbo, m_ebo;
    int m_indexCount;
};
