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

class TextureManager {
public:
    static TextureManager& instance();
    GLuint load(const std::string& path);
    void unloadAll();
private:
    TextureManager() {}
    std::map<std::string, GLuint> m_cache;
    GLuint loadFromFile(const std::string& path);
    GLuint loadSGI(const std::string& path);
    GLuint createFallback();
};
