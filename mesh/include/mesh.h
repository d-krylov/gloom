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

  void GetNormal();

public:
  std::vector<Types::Vector3f> positions_;
  std::vector<Types::Vector3i> indices_;
  std::vector<Types::Vector3f> normals_;
  std::vector<Types::Vector2f> uv_;
  std::vector<Vertex> vertices_;
  std::vector<std::size_t> offsets_;
  std::vector<std::shared_ptr<Texture>> materials_;
  std::vector<uint32_t> material_indices_;
};

} // namespace Gloom

#endif // MESH_H