#include "gloom_mesh/include/terrain.h"
#include "easyloggingpp/easylogging++.h"

namespace Gloom {

std::vector<uint32_t> CreateGridIndices(uint32_t size) {
  std::vector<uint32_t> indices;
  indices.reserve(size * size * 4);
  for (uint32_t i = 0; i < size - 1; i++) {
    for (uint32_t j = 0; j < size - 1; j++) {
      indices.emplace_back(j + 0 + size * (i + 0));
      indices.emplace_back(j + 0 + size * (i + 1));
      indices.emplace_back(j + 1 + size * (i + 1));
      indices.emplace_back(j + 1 + size * (i + 0));
    }
  }
  return indices;
}

std::vector<Vertex> CreateGridVertices(uint32_t size, uint32_t w, uint32_t h) {
  std::vector<Vertex> vertices;
  vertices.reserve(size * size);
  for (uint32_t z = 0; z < size; z++) {
    for (uint32_t x = 0; x < size; x++) {
      float ux = x / float(size);
      float uy = z / float(size);
      float px = -float(w) / 2.0f + w * ux;
      float pz = -float(h) / 2.0f + h * uy;
      Vertex vertex{};
      {
        vertex.position_ = {px, 0.0f, pz};
        vertex.normal_ = {0.0f, 0.0f, 0.0f};
        vertex.uv_ = {ux, uy};
      }
      vertices.emplace_back(vertex);
    }
  }
  return vertices;
}

} // namespace Gloom