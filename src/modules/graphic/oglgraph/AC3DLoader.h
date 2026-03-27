/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#pragma once
#include "Mesh.h"
#include <vector>
#include <string>
#include <memory>

struct AC3DModel {
    std::vector<std::shared_ptr<Mesh>> meshes;
};

class AC3DLoader {
public:
    static AC3DModel* load(const std::string& filepath, const std::string& textureBasePath);
};
