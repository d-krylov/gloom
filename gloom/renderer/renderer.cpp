#include "gloom/renderer/include/renderer.h"
#include "gloom/application/include/gloom.h"

namespace Gloom {

Renderer::Renderer()
  : vertex_buffer_(500_MiB, Vertex::GetFormat()),
    vertex_array_(vertex_buffer_), graphics_pipeline_{SHADERS_DIR / "mesh" / "mesh.vert",
                                                      SHADERS_DIR / "mesh" / "mesh.frag"} {}

void Renderer::Add(Model &model) {
  offsets_[model.path_] = vertex_buffer_.GetSize();

  vertex_buffer_.Push(model.vertices_);
}

void Renderer::SetCamera(const Camera &camera) {
  auto projection = camera.GetPerspectiveMatrix();
  auto view = camera.GetLookAtMatrix();

  graphics_pipeline_.SetUniform(ShaderKind::VERTEX, "u_view_matrix", view);
  graphics_pipeline_.SetUniform(ShaderKind::VERTEX, "u_projection_matrix", projection);
  graphics_pipeline_.SetUniform(ShaderKind::FRAGMENT, "u_camera_position", camera.GetPosition());
}

// clang-format off
void Renderer::SetLights(const std::vector<PointLight> &point) {
  for (auto i = 0; i < point.size(); i++) {
    std::string name = "u_point_lights[" + std::to_string(i) + "]";
    graphics_pipeline_.SetUniform(ShaderKind::FRAGMENT, (name + ".position").c_str(), point[i].position_);
    graphics_pipeline_.SetUniform(ShaderKind::FRAGMENT, (name + ".color").c_str(), point[i].color_);
    graphics_pipeline_.SetUniform(ShaderKind::FRAGMENT, (name + ".attenuation").c_str(), point[i].attenuation_);
  }
}
// clang-format on

void Renderer::Begin() {

  Command::EnableDepthTest(true);
  Command::Clear(true, true);

  vertex_array_.Bind();
  graphics_pipeline_.Bind();

  graphics_pipeline_.SetUniform(ShaderKind::FRAGMENT, "u_material.ambient_map", 0);
  graphics_pipeline_.SetUniform(ShaderKind::FRAGMENT, "u_material.diffuse_map", 1);
  graphics_pipeline_.SetUniform(ShaderKind::FRAGMENT, "u_material.specular_map", 2);
}

void Renderer::Draw(Model &model, const Transform &transform) {

  graphics_pipeline_.SetUniform(ShaderKind::VERTEX, "u_model_matrix", transform.GetModelMatrix());

  auto offset = offsets_[model.path_];

  for (auto &mesh : model.meshes_) {

    if (mesh.material_.HasTexture(TextureType::AMBIENT)) {
      model.textures_[mesh.material_.GetName(TextureType::AMBIENT)].Bind(0);
    }

    if (mesh.material_.HasTexture(TextureType::DIFFUSE)) {
      model.textures_[mesh.material_.GetName(TextureType::DIFFUSE)].Bind(1);
    }

    if (mesh.material_.HasTexture(TextureType::SPECULAR)) {
      model.textures_[mesh.material_.GetName(TextureType::SPECULAR)].Bind(2);
    }

    graphics_pipeline_.SetUniform(ShaderKind::FRAGMENT, "u_material.shininess",
                                  mesh.material_.shininess);

    Command::DrawArrays(offset + mesh.vertices_offset_, mesh.vertices_size_);
  }
}

} // namespace Gloom