#ifndef GLOOM_MODEL_H
#define GLOOM_MODEL_H

#include "graphics/include/graphics.h"
#include "material.h"
#include "vertex.h"
#include <map>
#include <string>

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
  Model();
  Model(Model &&);
  Model &operator=(Model &&);

  NO_COPY_SEMANTIC(Model)

  Model(const std::filesystem::path &path);

protected:
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