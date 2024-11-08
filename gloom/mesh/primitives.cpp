#include "mesh/include/primitives.h"

namespace Gloom {

// clang-format off
std::array<Vector3f, 8> box_vertices{
  Vector3f(-0.5f, -0.5f, +0.5f), Vector3f(+0.5f, -0.5f, +0.5f),
  Vector3f(+0.5f, +0.5f, +0.5f), Vector3f(-0.5f, +0.5f, +0.5f),
  Vector3f(-0.5f, -0.5f, -0.5f), Vector3f(+0.5f, -0.5f, -0.5f),
  Vector3f(+0.5f, +0.5f, -0.5f), Vector3f(-0.5f, +0.5f, -0.5f)};

std::array<Vector3f, 6> box_normals{
  Vector3f(+0.0, +0.0, +1.0), Vector3f(+1.0, +0.0, +0.0), 
  Vector3f(+0.0, +0.0, +1.0), Vector3f(-1.0, +0.0, +0.0),
  Vector3f(+0.0, +1.0, +0.0), Vector3f(+0.0, -1.0, +0.0)};

std::array<Vector2f, 6> box_uv{ 
  Vector2f{0.0f, 0.0f}, Vector2f{1.0f, 0.0f}, Vector2f{1.0f, 1.0f},
  Vector2f{1.0f, 1.0f}, Vector2f{0.0f, 1.0f}, Vector2f{0.0f, 0.0f}};

std::array<uint32_t, 36> box_indices{
  0, 1, 2, 2, 3, 0, 1, 5, 6, 6, 2, 1, 5, 4, 7, 7, 6, 5, 
  4, 0, 3, 3, 7, 4, 3, 2, 6, 6, 7, 3, 4, 5, 1, 1, 0, 4};
// clang-format on

std::array<Vertex, 36> MakeBox() {
  std::array<Vertex, 36> data;
  for (uint32_t i = 0; i < 36; i++) {
    data[i].position_ = box_vertices[box_indices[i]];
    data[i].normal_ = box_normals[i / 6];
    data[i].uv_ = box_uv[i % 6];
  }
  return data;
}

} // namespace Gloom