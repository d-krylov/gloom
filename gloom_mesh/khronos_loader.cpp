#include "easyloggingpp/easylogging++.h"
#include "gloom_core/include/core_types.h"
#include "gloom_mesh/include/mesh_loader.h"
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

void GetVertices(const tinygltf::Model &model, const tinygltf::Node &node) {
  LOG(INFO) << "Node name: " << node.name;
}

void LoadGLTF(const std::filesystem::path &path) {
  tinygltf::Model model;
  tinygltf::TinyGLTF context;

  std::string error;
  std::string warning;

  bool binary = false;

  bool status = binary ? context.LoadBinaryFromFile(&model, &error, &warning, path.string())
                       : context.LoadASCIIFromFile(&model, &error, &warning, path.string());

  if (status) {

    LOG(INFO) << "Scenes: " << model.scenes.size();

    const auto &default_scene = model.scenes[model.defaultScene > -1 ? model.defaultScene : 0];

    LOG(INFO) << "Nodes: " << default_scene.nodes.size();

    const auto mesh = model.meshes[0];

    for (const auto &primitive : mesh.primitives) {
      const auto &position_accessor = model.accessors[primitive.attributes.at("POSITION")];
      const auto &position_buffer_view = model.bufferViews[position_accessor.bufferView];
      const auto &position_buffer = model.buffers[position_buffer_view.buffer];

      auto positions = reinterpret_cast<const Vector3f *>(position_buffer.data.data() +
                                                          position_buffer_view.byteOffset +
                                                          position_accessor.byteOffset);

      size_t count = position_accessor.count;

      for (int i = 0; i < count; i++) {
        LOG(INFO) << (positions + i)->r << " " << (positions + i)->g << " "
                  << (positions + i)->b;
      }
    }

  } else {
    LOG(FATAL) << error;
  }
}

} // namespace Gloom