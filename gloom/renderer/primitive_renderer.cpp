#include "gloom/renderer/include/primitive_renderer.h"
#include "gloom/renderer/include/shader_library.h"
#include "gloom/scene/include/camera.h"

namespace Gloom {

PrimitiveRenderer::PrimitiveRenderer()
  : vertex_array_(), storage_buffer_(BufferTarget::SHADER_STORAGE, 50_MiB) {}

void PrimitiveRenderer::Begin(const Camera &camera) {
  auto &graphics_pipeline = ShaderLibrary::Get().GetGraphicsPipeline(4);
  graphics_pipeline.Bind();
  graphics_pipeline.SetUniform(ShaderKind::FRAGMENT, "u_camera_position", camera.GetPosition());
  graphics_pipeline.SetUniform(ShaderKind::VERTEX, "u_view_matrix", camera.GetLookAtMatrix());
  graphics_pipeline.SetUniform(ShaderKind::VERTEX, "u_projection_matrix",
                               camera.GetProjectionMatrix());
}

void PrimitiveRenderer::DrawBoxes(const std::vector<Matrix4f> &transforms) {
  Command::EnableDepthTest(true);
  Command::Clear(true, true);
  auto &graphics_pipeline = ShaderLibrary::Get().GetGraphicsPipeline(4);
  vertex_array_.Bind();
  storage_buffer_.BindRange(0);
  storage_buffer_.Resize(0);
  storage_buffer_.Push(transforms);
  Command::DrawArraysInstanced(36, transforms.size());
}

} // namespace Gloom