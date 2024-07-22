#include "gloom_mesh/include/mesh.h"

namespace Gloom {

Mesh::Mesh(const std::filesystem::path &path) : path_(path) { Load(path_); }

// clang-format off
void Mesh::GetNormal() {
  for (uint32_t i = 0; i < vertices_.size() - 2; i += 3) {
    auto normal = glm::triangleNormal(vertices_[i + 0].position_, 
                                      vertices_[i + 1].position_,
                                      vertices_[i + 2].position_);
    vertices_[i + 0].normal_ = normal;
    vertices_[i + 1].normal_ = normal;
    vertices_[i + 2].normal_ = normal;
  }
}
// clang-format on

} // namespace Gloom