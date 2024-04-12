#ifndef GLOOM_MESH_LOADER_H
#define GLOOM_MESH_LOADER_H

#include "gloom_mesh.h"
#include <filesystem>
#include <memory>
#include <vector>

namespace Gloom {

class MeshLoader {
public:
  void Load(std::filesystem::path path, Mesh &mesh);

private:
};

} // namespace Gloom

#endif // GLOOM_MESH_LOADER_H