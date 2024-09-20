#ifndef GLOOM_MODEL_H
#define GLOOM_MODEL_H

#include "gloom/core/include/image.h"
#include "gloom/graphics/texture/texture_2d.h"
#include "material.h"
#include "vertex.h"
#include <filesystem>
#include <map>
#include <memory>
#include <string>

struct aiNode;
struct aiScene;
struct aiMesh;

namespace Gloom {

struct Mesh {
  uint64_t vertices_offset_;
  uint64_t vertices_size_;
  uint64_t indices_offset_;
  uint64_t indices_size_;
  Material material_;
};

class Model {
public:
  void LoadAssimp(const std::filesystem::path &path);
  void LoadWavefront(const std::filesystem::path &path);

public:
  std::vector<Mesh> meshes_;
  std::vector<Vertex> vertices_;
  std::map<std::string, Texture2D> textures_;
  std::filesystem::path path_;
};

} // namespace Gloom

#endif // GLOOM_MODEL_H