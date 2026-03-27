/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "Mesh.h"
#include <cstring>

Mesh::Mesh()
    : m_vao(0), m_vbo(0), m_ebo(0), m_indexCount(0),
      shininess(32.0f), transparent(false)
{
    ambient[0]  = ambient[1]  = ambient[2]  = 0.2f; ambient[3]  = 1.0f;
    diffuse[0]  = diffuse[1]  = diffuse[2]  = 0.8f; diffuse[3]  = 1.0f;
    specular[0] = specular[1] = specular[2] = 0.0f; specular[3] = 1.0f;
}

Mesh::~Mesh() {
    if (m_vao) { glDeleteVertexArrays(1, &m_vao); m_vao = 0; }
    if (m_vbo) { glDeleteBuffers(1, &m_vbo); m_vbo = 0; }
    if (m_ebo) { glDeleteBuffers(1, &m_ebo); m_ebo = 0; }
}

void Mesh::upload(const std::vector<Vertex>& verts, const std::vector<unsigned int>& indices) {
    m_indexCount = (int)indices.size();
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);

    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(Vertex), verts.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // attrib 0: pos
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)offsetof(Vertex, pos));
    // attrib 1: normal
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)offsetof(Vertex, normal));
    // attrib 2: texCoord
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)offsetof(Vertex, texCoord));
    // attrib 3: texCoord2
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)offsetof(Vertex, texCoord2));

    glBindVertexArray(0);
}

void Mesh::draw() const {
    if (!m_vao) return;
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::drawInstanced(int count) const {
    if (!m_vao || count <= 0) return;
    glBindVertexArray(m_vao);
    glDrawElementsInstanced(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0, count);
    glBindVertexArray(0);
}
