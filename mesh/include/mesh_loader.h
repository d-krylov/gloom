#ifndef MESH_LOADER_H
#define MESH_LOADER_H

#include "mesh.h"
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

#endif // MESH_LOADER_H