/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "Shader.h"
#include <cstdio>
#include <cstring>
#include <tgfclient.h>

Shader::Shader() : m_program(0) {}

Shader::~Shader() {
    if (m_program) {
        glDeleteProgram(m_program);
        m_program = 0;
    }
}

std::string Shader::readFile(const std::string& path) {
    FILE* f = fopen(path.c_str(), "rb");
    if (!f) {
        GfOut("Shader::readFile: cannot open '%s'\n", path.c_str());
        return "";
    }
    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    fseek(f, 0, SEEK_SET);
    std::string buf(sz, '\0');
    fread(&buf[0], 1, sz, f);
    fclose(f);
    return buf;
}

GLuint Shader::compileShader(GLenum type, const std::string& source) {
    GLuint shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);
    GLint ok = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        char log[1024];
        glGetShaderInfoLog(shader, sizeof(log), NULL, log);
        GfOut("Shader compile error: %s\n", log);
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

bool Shader::load(const std::string& vertPath, const std::string& fragPath) {
    std::string vsrc = readFile(vertPath);
    std::string fsrc = readFile(fragPath);
    if (vsrc.empty() || fsrc.empty()) {
        GfOut("Shader::load: empty source for '%s' or '%s'\n", vertPath.c_str(), fragPath.c_str());
        return false;
    }
    GLuint vs = compileShader(GL_VERTEX_SHADER, vsrc);
    GLuint fs = compileShader(GL_FRAGMENT_SHADER, fsrc);
    if (!vs || !fs) {
        if (vs) glDeleteShader(vs);
        if (fs) glDeleteShader(fs);
        return false;
    }
    m_program = glCreateProgram();
    glAttachShader(m_program, vs);
    glAttachShader(m_program, fs);
    glLinkProgram(m_program);
    GLint ok = 0;
    glGetProgramiv(m_program, GL_LINK_STATUS, &ok);
    if (!ok) {
        char log[1024];
        glGetProgramInfoLog(m_program, sizeof(log), NULL, log);
        GfOut("Shader link error: %s\n", log);
        glDetachShader(m_program, vs);
        glDetachShader(m_program, fs);
        glDeleteShader(vs);
        glDeleteShader(fs);
        glDeleteProgram(m_program);
        m_program = 0;
        return false;
    }
    glDetachShader(m_program, vs);
    glDetachShader(m_program, fs);
    glDeleteShader(vs);
    glDeleteShader(fs);
    return true;
}

bool Shader::loadWithGeom(const std::string& vertPath, const std::string& geomPath, const std::string& fragPath) {
    std::string vsrc = readFile(vertPath);
    std::string gsrc = readFile(geomPath);
    std::string fsrc = readFile(fragPath);
    if (vsrc.empty() || gsrc.empty() || fsrc.empty()) return false;
    GLuint vs = compileShader(GL_VERTEX_SHADER, vsrc);
    GLuint gs = compileShader(GL_GEOMETRY_SHADER, gsrc);
    GLuint fs = compileShader(GL_FRAGMENT_SHADER, fsrc);
    if (!vs || !gs || !fs) {
        if (vs) glDeleteShader(vs);
        if (gs) glDeleteShader(gs);
        if (fs) glDeleteShader(fs);
        return false;
    }
    m_program = glCreateProgram();
    glAttachShader(m_program, vs);
    glAttachShader(m_program, gs);
    glAttachShader(m_program, fs);
    glLinkProgram(m_program);
    GLint ok = 0;
    glGetProgramiv(m_program, GL_LINK_STATUS, &ok);
    if (!ok) {
        char log[1024];
        glGetProgramInfoLog(m_program, sizeof(log), NULL, log);
        GfOut("Shader link error (geom): %s\n", log);
        glDeleteProgram(m_program);
        m_program = 0;
    }
    glDetachShader(m_program, vs); glDeleteShader(vs);
    glDetachShader(m_program, gs); glDeleteShader(gs);
    glDetachShader(m_program, fs); glDeleteShader(fs);
    return m_program != 0;
}

void Shader::use() const {
    glUseProgram(m_program);
}

void Shader::unuse() const {
    glUseProgram(0);
}

GLint Shader::getUniformLocation(const std::string& name) const {
    auto it = m_uniformCache.find(name);
    if (it != m_uniformCache.end()) return it->second;
    GLint loc = glGetUniformLocation(m_program, name.c_str());
    m_uniformCache[name] = loc;
    return loc;
}

void Shader::setInt(const std::string& name, int val) {
    GLint loc = getUniformLocation(name);
    if (loc >= 0) glUniform1i(loc, val);
}

void Shader::setFloat(const std::string& name, float val) {
    GLint loc = getUniformLocation(name);
    if (loc >= 0) glUniform1f(loc, val);
}

void Shader::setVec2(const std::string& name, float x, float y) {
    GLint loc = getUniformLocation(name);
    if (loc >= 0) glUniform2f(loc, x, y);
}

void Shader::setVec3(const std::string& name, float x, float y, float z) {
    GLint loc = getUniformLocation(name);
    if (loc >= 0) glUniform3f(loc, x, y, z);
}

void Shader::setVec4(const std::string& name, float x, float y, float z, float w) {
    GLint loc = getUniformLocation(name);
    if (loc >= 0) glUniform4f(loc, x, y, z, w);
}

void Shader::setMat4(const std::string& name, const float* mat) {
    GLint loc = getUniformLocation(name);
    if (loc >= 0) glUniformMatrix4fv(loc, 1, GL_FALSE, mat);
}
