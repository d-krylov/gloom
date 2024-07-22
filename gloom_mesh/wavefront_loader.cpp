#include "easyloggingpp/easylogging++.h"
#include "gloom_mesh/include/mesh.h"
#include "tinyobjloader/tiny_obj_loader.h"
#include <iostream>
#include <set>

namespace Gloom {

void Mesh::LoadVertices(const tinyobj::ObjReader &reader) {
  auto &shapes = reader.GetShapes();
  auto &attributes = reader.GetAttrib();
  for (const auto &shape : shapes) {
    std::size_t index_offset = 0;
    offsets_.emplace_back(vertices_.size());
    material_indices_.emplace_back(shape.mesh.material_ids[0]);

    for (std::size_t i = 0; i < shape.mesh.num_face_vertices.size(); i++) {
      auto vertices_in_face = shape.mesh.num_face_vertices[i];

      for (std::size_t v = 0; v < vertices_in_face; v++) {
        auto index = shape.mesh.indices[index_offset + v];
        Vertex vertex;
        auto vx = attributes.vertices[3 * index.vertex_index + 0];
        auto vy = attributes.vertices[3 * index.vertex_index + 1];
        auto vz = attributes.vertices[3 * index.vertex_index + 2];
        vertex.position_ = Vector3f(vx, vy, vz);
        positions_.emplace_back(vertex.position_);

        if (attributes.normals.empty() == false) {
          auto nx = attributes.normals[3 * index.normal_index + 0];
          auto ny = attributes.normals[3 * index.normal_index + 1];
          auto nz = attributes.normals[3 * index.normal_index + 2];
          vertex.normal_ = Vector3f(nx, ny, nz);
          normals_.emplace_back(vertex.normal_);
        }

        if (index.texcoord_index >= 0) {
          auto uvx = attributes.texcoords[2 * index.texcoord_index + 0];
          auto uvy = attributes.texcoords[2 * index.texcoord_index + 1];
          vertex.uv_ = Vector2f(uvx, uvy);
          uv_.emplace_back(vertex.uv_);
        }
        vertices_.emplace_back(vertex);
      }
      index_offset += vertices_in_face;
    }
  }
}

void Mesh::LoadMaterials(const tinyobj::ObjReader &reader) {
  auto &materials = reader.GetMaterials();
  for (auto &m : materials) {

    auto &material = materials_.emplace_back();

    MaterialProperties mp;
    mp.ambient_ = Vector3f(m.ambient[0], m.ambient[1], m.ambient[2]);
    mp.diffuse_ = Vector3f(m.diffuse[0], m.diffuse[1], m.diffuse[2]);
    mp.specular_ = Vector3f(m.specular[0], m.specular[1], m.specular[2]);
    mp.emission_ = Vector3f(m.emission[0], m.emission[1], m.emission[2]);
    mp.transmittance_ = Vector3f(m.transmittance[0], m.transmittance[1], m.transmittance[2]);
    mp.shininess_ = m.shininess;
    mp.ior_ = m.ior;
    mp.dissolve_ = m.dissolve;

    material.properties_ = std::make_shared<MaterialProperties>(mp);

    if (m.ambient_texname.size() > 0) {
      auto image_path = path_.parent_path() / m.ambient_texname;
      material.ambient_texture_ = std::make_shared<Texture>(image_path);
    }

    if (m.diffuse_texname.size() > 0) {
      auto image_path = path_.parent_path() / m.diffuse_texname;
      material.diffuse_texture_ = std::make_shared<Texture>(image_path);
    }

    if (m.specular_texname.size() > 0) {
      auto image_path = path_.parent_path() / m.specular_texname;
      material.specular_texture_ = std::make_shared<Texture>(image_path);
    }
  }
}

void Mesh::Load(const std::filesystem::path &path) {
  tinyobj::ObjReader reader;
  tinyobj::ObjReaderConfig reader_config;

  auto status = reader.ParseFromFile(path.string(), reader_config);

  LoadVertices(reader);

  LoadMaterials(reader);
}

} // namespace Gloom