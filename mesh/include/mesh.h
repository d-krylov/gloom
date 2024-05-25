#ifndef MESH_H
#define MESH_H

#include "material.h"
#include "vertex.h"

namespace Gloom {

class Mesh {
public:
  Mesh() = default;

  NO_COPY_SEMANTIC(Mesh);

  void Load(const std::filesystem::path &path);

public:
  std::vector<Types::Vector3f> positions_;
  std::vector<Types::Vector3i> indices_;
  std::vector<Types::Vector3f> normals_;
  std::vector<Types::Vector2f> uv_;
  std::vector<Vertex> vertices_;
};

} // namespace Gloom

#endif // MESH_H