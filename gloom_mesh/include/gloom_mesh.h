#ifndef GLOOM_MESH_H
#define GLOOM_MESH_H

#include "gloom_macros.h"
#include "material.h"
#include <filesystem>
#include <span>
#include <vector>

namespace Gloom {

class Mesh {
public:
  Mesh() = default;

  NO_COPY_SEMANTIC(Mesh);

  std::size_t GetVerticesCount() const { return 3 * vertices_.size(); }

  std::vector<Types::Vector3f> GetAttributes() const;

  void ComputeNormals();

public:
  std::vector<Types::Vector3f> vertices_;
  std::vector<Types::Vector3i> indices_;
  std::vector<Types::Vector3f> normals_;
  std::vector<Types::Vector2f> uv_;
};

} // namespace Gloom

#endif // GLOOM_MESH_H