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
#include <string>
#include <map>

class Shader {
public:
    Shader();
    ~Shader();
    bool load(const std::string& vertPath, const std::string& fragPath);
    bool loadWithGeom(const std::string& vertPath, const std::string& geomPath, const std::string& fragPath);
    void use() const;
    void unuse() const;
    GLuint id() const { return m_program; }
    void setInt(const std::string& name, int val);
    void setFloat(const std::string& name, float val);
    void setVec2(const std::string& name, float x, float y);
    void setVec3(const std::string& name, float x, float y, float z);
    void setVec4(const std::string& name, float x, float y, float z, float w);
    void setMat4(const std::string& name, const float* mat);
private:
    GLuint m_program;
    mutable std::map<std::string, GLint> m_uniformCache;
    GLint getUniformLocation(const std::string& name) const;
    static GLuint compileShader(GLenum type, const std::string& source);
    static std::string readFile(const std::string& path);
};
