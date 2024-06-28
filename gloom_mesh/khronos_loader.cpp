#include "gloom_mesh/include/mesh.h"
#include "tinygltf/tiny_gltf.h"
#include <filesystem>
#include <string>

namespace Gloom {

void GetNodeProperties(const tinygltf::Node &node, const tinygltf::Model &model,
                       std::size_t &vertex_count, std::size_t &index_count) {
  if (node.children.size() > 0) {
    for (size_t i = 0; i < node.children.size(); i++) {
      GetNodeProperties(model.nodes[node.children[i]], model, vertex_count, index_count);
    }
  }
  if (node.mesh > -1) {
    const tinygltf::Mesh mesh = model.meshes[node.mesh];
    for (size_t i = 0; i < mesh.primitives.size(); i++) {
      auto primitive = mesh.primitives[i];
      vertex_count += model.accessors[primitive.attributes.find("POSITION")->second].count;
      if (primitive.indices > -1) {
        index_count += model.accessors[primitive.indices].count;
      }
    }
  }
}

void LoadGLTF(const std::filesystem::path &path) {
  tinygltf::Model model;
  tinygltf::TinyGLTF context;

  std::string error;
  std::string warning;

  bool binary;

  bool status = binary ? context.LoadBinaryFromFile(&model, &error, &warning, path.string())
                       : context.LoadASCIIFromFile(&model, &error, &warning, path.string());

  if (status) {
  }
}

} // namespace Gloom