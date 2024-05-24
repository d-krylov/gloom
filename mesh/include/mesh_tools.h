#ifndef MESH_TOOLS_H
#define MESH_TOOLS_H

#include "core_types.h"
#include <vector>

namespace Gloom {

std::vector<Types::Vector3i> Triangulate(const std::vector<std::vector<int32_t>> &faces);

} // namespace Gloom

#endif // MESH_TOOLS_H