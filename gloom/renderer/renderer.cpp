#include "gloom/renderer/include/renderer.h"
#include "gloom/application/include/gloom.h"
#include "gloom/renderer/include/shader_library.h"

namespace Gloom {

Renderer::Renderer(uint32_t width, uint32_t height)
  : vertex_buffer_(500_MiB, Vertex::GetFormat()), vertex_array_(vertex_buffer_), dummy_vao_() {
  OnWindowSize(width, height);
}

void Renderer::Add(Model &model) {
  offsets_[model.path_] = vertex_buffer_.GetSize();

  vertex_buffer_.Push(model.vertices_);
}

void Renderer::SetCamera(const Camera &camera) {
  auto projection = camera.GetPerspectiveMatrix();
  auto view = camera.GetLookAtMatrix();

  auto &scene_pipeline = ShaderLibrary::Get().GetGraphicsPipeline(3);

  scene_pipeline.SetUniform(ShaderKind::VERTEX, "u_view_matrix", view);
  scene_pipeline.SetUniform(ShaderKind::VERTEX, "u_projection_matrix", projection);
  scene_pipeline.SetUniform(ShaderKind::FRAGMENT, "u_camera_position", camera.GetPosition());
}

// clang-format off
void Renderer::SetLights(const std::vector<PointLight> &point) {
  auto &scene_pipeline = ShaderLibrary::Get().GetGraphicsPipeline(3);

  for (auto i = 0; i < point.size(); i++) {
    std::string name = "u_point_lights[" + std::to_string(i) + "]";
    scene_pipeline.SetUniform(ShaderKind::FRAGMENT, (name + ".position").c_str(), point[i].position_);
    scene_pipeline.SetUniform(ShaderKind::FRAGMENT, (name + ".color").c_str(), point[i].color_);
    scene_pipeline.SetUniform(ShaderKind::FRAGMENT, (name + ".attenuation").c_str(), point[i].attenuation_);
  }
}
// clang-format on

void Renderer::OnWindowSize(uint32_t width, uint32_t height) {
  color_texture_ = std::make_unique<Texture2D>(width, height, InternalFormat::RGB8);
  depth_texture_ = std::make_unique<TextureDepth>(1024, 1024);
  renderbuffer_ = std::make_unique<Renderbuffer>(InternalFormat::DEPTH_COMPONENT32F, width, height);
  framebuffer_ = std::make_unique<Framebuffer>();
  FramebufferAttachment attachment_1(AttachmentType::COLOR_ATTACHMENT0, color_texture_.get());
  FramebufferAttachment attachment_2(AttachmentType::DEPTH_ATTACHMENT, renderbuffer_.get());
  FramebufferAttachment attachment_3(AttachmentType::DEPTH_ATTACHMENT, depth_texture_.get());
  framebuffer_->Attach(attachment_1);
  framebuffer_->Attach(attachment_3);
}

void Renderer::Begin() {

  auto &scene_pipeline = ShaderLibrary::Get().GetGraphicsPipeline(3);

  vertex_array_.Bind();
  scene_pipeline.Bind();

  scene_pipeline.SetUniform(ShaderKind::FRAGMENT, "u_ambient_map", 0);
  scene_pipeline.SetUniform(ShaderKind::FRAGMENT, "u_diffuse_map", 1);
  scene_pipeline.SetUniform(ShaderKind::FRAGMENT, "u_specular_map", 2);
  scene_pipeline.SetUniform(ShaderKind::FRAGMENT, "u_shadow_map", 3);
}

void Renderer::Draw(Model &model, const Transform &transform, const PointLight &light,
                    const Camera &camera) {
  Begin();

  auto &scene_pipeline = ShaderLibrary::Get().GetGraphicsPipeline(3);

  SetLights({light});
  SetCamera(camera);

  depth_texture_->Bind(3);

  scene_pipeline.SetUniform(ShaderKind::VERTEX, "u_model_matrix", transform.GetModelMatrix());

  float near_plane = 0.1f, far_plane = 10000.0f;
  auto light_projection = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f, near_plane, far_plane);
  auto light_view = glm::lookAt(light.position_, Vector3f(0.0f), Vector3f(0.0, 1.0, 0.0));
  auto light_space_matrix = light_projection * light_view;

  scene_pipeline.SetUniform(ShaderKind::VERTEX, "u_light_space_matrix", light_space_matrix);
  scene_pipeline.SetUniform(ShaderKind::VERTEX, "u_model_matrix", transform.GetModelMatrix());

  auto offset = offsets_[model.path_];

  for (auto &mesh : model.meshes_) {

    if (mesh.material_.names_.ambient_.empty() == false) {
      model.textures_[mesh.material_.names_.ambient_].Bind(0);
    }

    if (mesh.material_.names_.diffuse_.empty() == false) {
      model.textures_[mesh.material_.names_.diffuse_].Bind(1);
    }

    if (mesh.material_.names_.specular_.empty() == false) {
      model.textures_[mesh.material_.names_.specular_].Bind(2);
    }

    scene_pipeline.SetUniform(ShaderKind::FRAGMENT, "u_material.shininess",
                              mesh.material_.shininess);

    Command::DrawArrays(offset + mesh.vertices_offset_, mesh.vertices_size_);
  }
}

void Renderer::DrawDepth(Model &model, const Transform &transform, const PointLight &light) {
  auto &depth_pipeline = ShaderLibrary::Get().GetGraphicsPipeline(2);

  depth_pipeline.Bind();
  vertex_array_.Bind();

  float near_plane = 0.1f, far_plane = 10000.0f;
  auto light_projection = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f, near_plane, far_plane);

  auto light_view = glm::lookAt(light.position_, light.position_ - Z_, Vector3f(0.0, 1.0, 0.0));
  auto light_space_matrix = light_projection * light_view;

  depth_pipeline.SetUniform(ShaderKind::VERTEX, "u_model_matrix", transform.GetModelMatrix());
  depth_pipeline.SetUniform(ShaderKind::VERTEX, "u_light_space_matrix", light_space_matrix);

  auto offset = offsets_[model.path_];
  for (auto &mesh : model.meshes_) {
    Command::DrawArrays(offset + mesh.vertices_offset_, mesh.vertices_size_);
  }
}

void Renderer::DrawWithPasses(Model &model, const Transform &transform, const PointLight &light,
                              const Camera &camera) {

  Command::EnableDepthTest(true);
  Command::Clear(true, true);
  Command::SetViewport(0, 0, 1024, 1024);
  framebuffer_->Bind();
  depth_texture_->Bind(0);
  Command::Clear(false, true);
  DrawDepth(model, transform, light);
  framebuffer_->Unbind();

  auto &window = Application::Get().GetWindow();

  Command::SetViewport(0, 0, window.GetWidth(), window.GetHeight());

  Command::Clear(true, true);
  Draw(model, transform, light, camera);
}

} // namespace Gloom