#include "gloom_mesh.h"

namespace Gloom {

void Mesh::ComputeNormals() {
  for (auto i = 0; i < vertices_.size(); i += 3) {
    auto v0 = vertices_[i + 0];
    auto v1 = vertices_[i + 1];
    auto v2 = vertices_[i + 2];

    auto n = linalg::cross(v1 - v0, v2 - v0);

    normals_.emplace_back(n);
  }
}

std::vector<Types::Vector3f> Mesh::GetAttributes() const {
  std::vector<Types::Vector3f> attributes;
  for (std::size_t i = 0; i < vertices_.size(); i++) {
    attributes.emplace_back(vertices_[i]);
    attributes.emplace_back(normals_[i / 3]);
  }
  return attributes;
}

} // namespace Gloom