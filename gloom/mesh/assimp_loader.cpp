#include "core/include/image.h"
#include "mesh/include/model.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <iostream>

namespace Gloom {

void LoadMaterial(const aiScene *scene, Model &model, aiMesh *assimp_mesh, Mesh &mesh) {
  aiMaterial *material = scene->mMaterials[assimp_mesh->mMaterialIndex];

  std::vector<aiTextureType> required{
    aiTextureType::aiTextureType_AMBIENT, aiTextureType::aiTextureType_DIFFUSE,
    aiTextureType::aiTextureType_SPECULAR, aiTextureType::aiTextureType_DISPLACEMENT};

  std::vector<std::string TextureNames::*> fields{&TextureNames::ambient_, &TextureNames::diffuse_,
                                                  &TextureNames::specular_, &TextureNames::bump_};

  for (auto i = 0; i < required.size(); i++) {
    aiString assimp_texture_name;
    mesh.material_.names_.*fields[i] = "default";
    material->GetTexture(required[i], 0, &assimp_texture_name);
    if (assimp_texture_name.length > 0) {
      std::string texture_name(assimp_texture_name.C_Str());
      if (model.textures_.find(texture_name) == model.textures_.end()) {
        auto texture_path = model.path_.parent_path() / texture_name;
        model.textures_.emplace(texture_name, Texture2D(texture_path));
      }
      mesh.material_.names_.*fields[i] = texture_name;
    }
  }
  auto ret = material->Get(AI_MATKEY_SHININESS, mesh.material_.shininess);
}

void ProcessMesh(aiMesh *assimp_mesh, const aiScene *scene, Model &model) {
  auto &mesh = model.meshes_.emplace_back();

  mesh.vertices_offset_ = model.vertices_.size();

  for (uint32_t i = 0; i < assimp_mesh->mNumFaces; i++) {
    auto face = assimp_mesh->mFaces[i];

    for (uint32_t j = 0; j < face.mNumIndices; j++) {
      auto index = face.mIndices[j];

      Vertex vertex{};

      vertex.position_.x = assimp_mesh->mVertices[index].x;
      vertex.position_.y = assimp_mesh->mVertices[index].y;
      vertex.position_.z = assimp_mesh->mVertices[index].z;

      if (assimp_mesh->HasNormals()) {
        vertex.normal_.x = assimp_mesh->mNormals[index].x;
        vertex.normal_.y = assimp_mesh->mNormals[index].y;
        vertex.normal_.z = assimp_mesh->mNormals[index].z;
      }

      if (assimp_mesh->HasTextureCoords(0)) {
        vertex.uv_.x = assimp_mesh->mTextureCoords[0][index].x;
        vertex.uv_.y = assimp_mesh->mTextureCoords[0][index].y;
      }

      model.vertices_.emplace_back(vertex);
    }
  }
  mesh.vertices_size_ = model.vertices_.size() - mesh.vertices_offset_;

  LoadMaterial(scene, model, assimp_mesh, mesh);
}

void ProcessNode(aiNode *node, const aiScene *scene, Model &model) {
  for (auto i = 0; i < node->mNumMeshes; i++) {
    auto *assimp_mesh = scene->mMeshes[node->mMeshes[i]];
    ProcessMesh(assimp_mesh, scene, model);
  }
  for (auto i = 0; i < node->mNumChildren; i++) {
    ProcessNode(node->mChildren[i], scene, model);
  }
}

void Model::LoadAssimp(const std::filesystem::path &path) {
  Assimp::Importer importer;

  path_ = path;
  auto flags = aiProcess_Triangulate;

  const auto *scene = importer.ReadFile(path, flags);

  if ((scene == nullptr) || (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) ||
      (scene->mRootNode == nullptr)) {
    return;
  }

  textures_.emplace("default", Texture2D(Image()));

  ProcessNode(scene->mRootNode, scene, *this);
}

} // namespace Gloom