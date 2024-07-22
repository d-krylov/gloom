#ifndef GLOOM_MESH_LOADER_H
#define GLOOM_MESH_LOADER_H

#include <filesystem>

namespace Gloom {

void LoadGLTF(const std::filesystem::path &path);

} // namespace Gloom

#endif // GLOOM_MESH_LOADER_H