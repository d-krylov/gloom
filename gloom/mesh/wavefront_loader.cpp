#include "gloom/mesh/include/model.h"
#include "tinyobjloader/tiny_obj_loader.h"
#include <iostream>
#include <unordered_set>

namespace Gloom {

void SetMeshMaterial(const tinyobj::ObjReader &reader, Mesh &mesh, const tinyobj::shape_t &shape) {
  auto &materials = reader.GetMaterials();
  auto material_index = shape.mesh.material_ids[0];
  auto &material = materials[material_index];
  mesh.material_.textures_[TextureType::AMBIENT] = material.ambient_texname;
  mesh.material_.textures_[TextureType::DIFFUSE] = material.diffuse_texname;
  mesh.material_.textures_[TextureType::SPECULAR] = material.specular_texname;
  mesh.material_.textures_[TextureType::BUMP] = material.bump_texname;
  mesh.material_.shininess = material.shininess;
}

void LoadMeshes(const tinyobj::ObjReader &reader, std::vector<Vertex> &vertices,
                std::vector<Mesh> &meshes) {

  auto &shapes = reader.GetShapes();
  auto &attributes = reader.GetAttrib();

  uint64_t vertex_index{0};

  constexpr uint32_t v3_size = 3;
  constexpr uint32_t v2_size = 2;

  for (const auto &shape : shapes) {
    uint64_t index_offset = 0;

    auto &new_mesh = meshes.emplace_back();

    new_mesh.vertices_offset_ = vertices.size();

    SetMeshMaterial(reader, new_mesh, shape);

    for (uint32_t i = 0; i < shape.mesh.num_face_vertices.size(); i++) {

      auto vertices_in_face = shape.mesh.num_face_vertices[i];

      for (uint32_t v = 0; v < vertices_in_face; v++) {

        auto index = shape.mesh.indices[index_offset + v];

        Vertex vertex{};

        auto vx = attributes.vertices[v3_size * index.vertex_index + 0];
        auto vy = attributes.vertices[v3_size * index.vertex_index + 1];
        auto vz = attributes.vertices[v3_size * index.vertex_index + 2];

        vertex.position_ = Vector3f(vx, vy, vz);

        if (attributes.normals.empty() == false) {
          auto nx = attributes.normals[v3_size * index.normal_index + 0];
          auto ny = attributes.normals[v3_size * index.normal_index + 1];
          auto nz = attributes.normals[v3_size * index.normal_index + 2];

          vertex.normal_ = Vector3f(nx, ny, nz);
        }

        if (index.texcoord_index >= 0) {
          auto uvx = attributes.texcoords[v2_size * index.texcoord_index + 0];
          auto uvy = attributes.texcoords[v2_size * index.texcoord_index + 1];

          vertex.uv_ = Vector2f(uvx, uvy);
        }
        vertices.emplace_back(vertex);
      }
      index_offset += vertices_in_face;
    }
    new_mesh.vertices_size_ = vertices.size() - new_mesh.vertices_offset_;
  }
}

void LoadMaterials(const std::filesystem::path &path, const tinyobj::ObjReader &reader,
                   std::map<std::string, Texture2D> &textures) {

  auto &materials = reader.GetMaterials();

  for (uint32_t i = 0; i < materials.size(); i++) {

    auto &material = materials[i];

    if (material.ambient_texname.empty() == false) {
      auto image_path = path.parent_path() / material.ambient_texname;
      if (textures.find(material.ambient_texname) == textures.end()) {
        textures.emplace(material.ambient_texname, Texture2D(image_path));
      }
    }

    if (material.diffuse_texname.empty() == false) {
      auto image_path = path.parent_path() / material.diffuse_texname;
      if (textures.find(material.ambient_texname) == textures.end()) {
        textures.emplace(material.diffuse_texname, Texture2D(image_path));
      }
    }

    if (material.specular_texname.empty() == false) {
      auto image_path = path.parent_path() / material.specular_texname;
      if (textures.find(material.specular_texname) == textures.end()) {
        textures.emplace(material.specular_texname, Texture2D(image_path));
      }
    }

    if (material.bump_texname.empty() == false) {
      auto image_path = path.parent_path() / material.bump_texname;
      if (textures.find(material.bump_texname) == textures.end()) {
        textures.emplace(material.bump_texname, Texture2D(image_path));
      }
    }
  }
}

void Model::LoadWavefront(const std::filesystem::path &path) {
  tinyobj::ObjReader reader;
  tinyobj::ObjReaderConfig reader_config;

  path_ = path;

  auto status = reader.ParseFromFile(path.string(), reader_config);

  auto &attributes = reader.GetAttrib();
  auto &shapes = reader.GetShapes();

  uint64_t indices_size{0};

  for (auto &shape : shapes) {
    indices_size += shape.mesh.num_face_vertices.size();
  }

  auto vertices_size = attributes.vertices.size();

  std::cout << vertices_size << " " << indices_size << std::endl;

  vertices_.reserve(indices_size);

  LoadMeshes(reader, vertices_, meshes_);
  LoadMaterials(path_, reader, textures_);
}

} // namespace Gloom