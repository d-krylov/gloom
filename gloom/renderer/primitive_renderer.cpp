#include "renderer/include/primitive_renderer.h"
#include "application/include/gloom.h"
#include "scene/include/camera.h"

namespace Gloom {

PrimitiveRenderer::PrimitiveRenderer()
  : vertex_array_(), storage_buffer_(BufferTarget::SHADER_STORAGE, 50_MiB),
    graphics_pipeline_{SHADERS_DIR / "primitives" / "box.vert",
                       SHADERS_DIR / "primitives" / "primitives.frag"} {}

void PrimitiveRenderer::Begin(const Camera &camera) {
  graphics_pipeline_.Bind();
  graphics_pipeline_.SetUniform(ShaderKind::FRAGMENT, "u_camera_position", camera.GetPosition());
  graphics_pipeline_.SetUniform(ShaderKind::VERTEX, "u_view_matrix", camera.GetLookAtMatrix());
  graphics_pipeline_.SetUniform(ShaderKind::VERTEX, "u_projection_matrix",
                                camera.GetProjectionMatrix());
}

void PrimitiveRenderer::DrawBoxes(const std::vector<Matrix4f> &transforms) {
  Command::EnableDepthTest(true);
  Command::ClearColor();
  Command::ClearDepth();
  vertex_array_.Bind();
  storage_buffer_.Bind(0);
  storage_buffer_.Resize(0);
  storage_buffer_.Push(transforms);
  Command::DrawArraysInstanced(36, transforms.size());
}

} // namespace Gloom