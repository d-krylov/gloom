#ifndef GLOOM_TERRAIN_H
#define GLOOM_TERRAIN_H

#include "gloom_mesh/include/vertex.h"

namespace Gloom {

std::vector<Vertex> CreateGridVertices(uint32_t size, uint32_t w, uint32_t h);
std::vector<uint32_t> CreateGridIndices(uint32_t size);

} // namespace Gloom

#endif // GLOOM_TERRAIN_H