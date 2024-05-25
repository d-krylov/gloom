#include "mesh.h"
#define TINYOBJLOADER_IMPLEMENTATION
#define TINYOBJLOADER_USE_MAPBOX_EARCUT
#include "tinyobjloader/tiny_obj_loader.h"

namespace Gloom {

void Mesh::Load(const std::filesystem::path &path) {
  tinyobj::ObjReader reader;
  tinyobj::ObjReaderConfig reader_config;

  auto status = reader.ParseFromFile(path.string(), reader_config);

  auto &attributes = reader.GetAttrib();
  auto &shapes = reader.GetShapes();
  auto &materials = reader.GetMaterials();

  for (const auto &shape : shapes) {
    std::size_t index_offset = 0;
    for (auto i = 0; i < shape.mesh.num_face_vertices.size(); i++) {
      auto vertices_in_face = shape.mesh.num_face_vertices[i];
      for (auto v = 0; v < vertices_in_face; v++) {
        auto index = shape.mesh.indices[index_offset + v];
        Vertex vertex;
        auto vx = attributes.vertices[3 * index.vertex_index + 0];
        auto vy = attributes.vertices[3 * index.vertex_index + 1];
        auto vz = attributes.vertices[3 * index.vertex_index + 2];
        vertex.position_ = Types::Vector3f(vx, vy, vz);
        positions_.emplace_back(vertex.position_);

        if (attributes.normals.empty() == false) {
          auto nx = attributes.normals[3 * index.normal_index + 0];
          auto ny = attributes.normals[3 * index.normal_index + 1];
          auto nz = attributes.normals[3 * index.normal_index + 2];
          vertex.normal_ = Types::Vector3f(nx, ny, nz);
          normals_.emplace_back(vertex.normal_);
        }

        if (index.texcoord_index >= 0) {
          auto uvx = attributes.texcoords[2 * index.texcoord_index + 0];
          auto uvy = attributes.texcoords[2 * index.texcoord_index + 1];
          vertex.uv_ = Types::Vector2f(uvx, uvy);
          uv_.emplace_back(vertex.uv_);
        }
        vertices_.emplace_back(vertex);
      }
      index_offset += vertices_in_face;
    }
  }
}

} // namespace Gloom