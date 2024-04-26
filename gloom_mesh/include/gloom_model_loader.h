#ifndef GLOOM_MODEL_LOADER_H
#define GLOOM_MODEL_LOADER_H

#include "gloom_mesh.h"
#include <filesystem>
#include <memory>
#include <vector>

namespace Gloom {

class ModelLoader {
public:
  void Load(std::filesystem::path path, Mesh &mesh);

private:
};

} // namespace Gloom

#endif // GLOOM_MODEL_LOADER_H