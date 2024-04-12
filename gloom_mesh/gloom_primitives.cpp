#include "gloom_primitives.h"
#include "gloom_mesh_tools.h"

namespace Gloom {

void MakeBox(Mesh &mesh) {
  std::vector<Types::Vector3f> vertices = {
      {-0.5f, -0.5f, +0.5f}, // 0
      {+0.5f, -0.5f, +0.5f}, // 1
      {+0.5f, +0.5f, +0.5f}, // 2
      {-0.5f, +0.5f, +0.5f}, // 3
      {-0.5f, -0.5f, -0.5f}, // 4
      {+0.5f, -0.5f, -0.5f}, // 5
      {+0.5f, +0.5f, -0.5f}, // 6
      {-0.5f, +0.5f, -0.5f}, // 7
  };

  std::vector<std::vector<int32_t>> faces = {{0, 1, 2, 3}, {1, 5, 6, 2},
                                             {4, 0, 3, 7}, {3, 2, 6, 7},
                                             {4, 5, 1, 0}, {5, 4, 7, 6}};

  mesh.indices_ = Triangulate(faces);

  for (const auto &v : mesh.indices_) {
    mesh.vertices_.emplace_back(vertices[v.x]);
    mesh.vertices_.emplace_back(vertices[v.y]);
    mesh.vertices_.emplace_back(vertices[v.z]);
  }
}

} // namespace Gloom