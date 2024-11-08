#include "renderer/include/renderer.h"

namespace Gloom {

Renderer::Renderer() {}

void Renderer::SetCamera(const Camera &camera, GraphicsPipeline &graphics_pipeline) {
  auto position = camera.GetPosition();
  auto projection = camera.GetProjectionMatrix();
  auto view = camera.GetLookAtMatrix();

  graphics_pipeline.SetUniform(ShaderKind::VERTEX, "u_view_matrix", view);
  graphics_pipeline.SetUniform(ShaderKind::VERTEX, "u_projection_matrix", projection);
  graphics_pipeline.SetUniform(ShaderKind::FRAGMENT, "u_camera_position", position);
}

void Renderer::SetPointLights(std::span<const PointLight> points,
                              GraphicsPipeline &graphics_pipeline) {}

} // namespace Gloom