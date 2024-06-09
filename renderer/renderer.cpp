#include "renderer.h"

namespace Gloom {

Renderer::Renderer()
  : vertex_array_(), vertex_buffer_(10_MiB, Vertex::GetFormat()),
    command_buffer_(BufferTarget::DRAW_INDIRECT_BUFFER, 4_MiB) {
  vertex_array_.AddVertexBuffer(vertex_buffer_);
  vertex_array_.Bind();
  command_buffer_.Bind();
}

void Renderer::ProcessMesh(const Mesh &mesh) {
  for (uint32_t i = 0; i < mesh.offsets_.size(); i++) {
    auto count = (i < mesh.offsets_.size() - 1) ? (mesh.offsets_[i + 1] - mesh.offsets_[i])
                                                : (mesh.vertices_.size() - mesh.offsets_[i]);
    DrawArraysIndirectCommand command{};
    {
      command.first_vertex_ = mesh.offsets_[i];
      command.count_ = count;
      command.base_instance_ = mesh.material_indices_[i];
      command.instance_count_ = 1;
    }
    commands_.emplace_back(command);
  }
  command_buffer_.SetData(std::span(commands_));
  vertex_buffer_.SetData(std::span(mesh.vertices_));
}

void Renderer::Draw() {
  vertex_array_.Bind();
  Commands::DrawArraysIndirect(commands_.size());
}

} // namespace Gloom