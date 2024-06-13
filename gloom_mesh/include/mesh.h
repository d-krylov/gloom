#ifndef GLOOM_MESH_H
#define GLOOM_MESH_H

#include "material.h"
#include "vertex.h"

namespace tinyobj {
class ObjReader;
}

namespace Gloom {

class Mesh {
public:
  Mesh(const std::filesystem::path &path);

  NO_COPY_SEMANTIC(Mesh);

  void GetNormal();

  const std::vector<Vertex> &GetVertices() const { return vertices_; }

protected:
  void Load(const std::filesystem::path &path);
  void LoadVertices(const tinyobj::ObjReader &reader);
  void LoadMaterials(const tinyobj::ObjReader &reader);

public:
  std::filesystem::path path_;
  std::vector<Vector3f> positions_;
  std::vector<Vector3i> indices_;
  std::vector<Vector3f> normals_;
  std::vector<Vector2f> uv_;
  std::vector<Vertex> vertices_;
  std::vector<std::size_t> offsets_;
  std::vector<Material> materials_;
  std::vector<uint32_t> material_indices_;
};

} // namespace Gloom

#endif // GLOOM_MESH_H