#include "renderer/include/model_renderer.h"
#include "application/include/gloom.h"

namespace Gloom {

// clang-format off
ModelRenderer::ModelRenderer(uint32_t width, uint32_t height)
  : vertex_buffer_(500_MiB, Vertex::GetFormat()),
    vertex_array_1_(vertex_buffer_),
    vertex_array_2_(),
    graphics_pipeline_1_{SHADERS_DIR / "mesh" / "mesh_shadow.vert",
                         SHADERS_DIR / "mesh" / "mesh_shadow.frag"},
    graphics_pipeline_2_{SHADERS_DIR / "mesh" / "shadow_mapping.vert",
                         SHADERS_DIR / "mesh" / "shadow_mapping.frag"} {
  OnWindowSize(width, height);
}
// clang-format on

void ModelRenderer::Add(const Model &model) {
  offsets_[model.path_] = vertex_buffer_.GetSize();

  vertex_buffer_.Push(model.vertices_);
}

void ModelRenderer::SetCamera(const Camera &camera) {
  auto projection = camera.GetProjectionMatrix();
  auto view = camera.GetLookAtMatrix();

  graphics_pipeline_1_.SetUniform(ShaderKind::VERTEX, "u_view_matrix", view);
  graphics_pipeline_1_.SetUniform(ShaderKind::VERTEX, "u_projection_matrix", projection);
  graphics_pipeline_1_.SetUniform(ShaderKind::FRAGMENT, "u_camera_position", camera.GetPosition());
}

// clang-format off
void ModelRenderer::SetLights(const std::vector<PointLight> &point) {

  for (auto i = 0; i < point.size(); i++) {
    std::string name = "u_point_lights[" + std::to_string(i) + "]";
    graphics_pipeline_1_.SetUniform(ShaderKind::FRAGMENT, (name + ".position").c_str(), point[i].position_);
    graphics_pipeline_1_.SetUniform(ShaderKind::FRAGMENT, (name + ".color").c_str(), point[i].color_);
    graphics_pipeline_1_.SetUniform(ShaderKind::FRAGMENT, (name + ".attenuation").c_str(), point[i].attenuation_);
  }
}
// clang-format on

void ModelRenderer::OnWindowSize(uint32_t width, uint32_t height) {
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

void ModelRenderer::Begin() {

  vertex_array_1_.Bind();
  graphics_pipeline_1_.Bind();

  graphics_pipeline_1_.SetUniform(ShaderKind::FRAGMENT, "u_ambient_map", 0);
  graphics_pipeline_1_.SetUniform(ShaderKind::FRAGMENT, "u_diffuse_map", 1);
  graphics_pipeline_1_.SetUniform(ShaderKind::FRAGMENT, "u_specular_map", 2);
  graphics_pipeline_1_.SetUniform(ShaderKind::FRAGMENT, "u_shadow_map", 3);
}

void ModelRenderer::Draw(Model &model, const Transform &transform, const PointLight &light,
                         const Camera &camera) {
  Begin();

  SetLights({light});
  SetCamera(camera);

  depth_texture_->Bind(3);

  graphics_pipeline_1_.SetUniform(ShaderKind::VERTEX, "u_model_matrix", transform.GetModelMatrix());

  float near_plane = 0.1f, far_plane = 10000.0f;
  auto light_projection = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f, near_plane, far_plane);
  auto light_view = glm::lookAt(light.position_, Vector3f(0.0f), Vector3f(0.0, 1.0, 0.0));
  auto light_space_matrix = light_projection * light_view;

  graphics_pipeline_1_.SetUniform(ShaderKind::VERTEX, "u_light_matrix", light_space_matrix);
  graphics_pipeline_1_.SetUniform(ShaderKind::VERTEX, "u_model_matrix", transform.GetModelMatrix());

  auto offset = offsets_[model.path_];

  for (auto &mesh : model.meshes_) {
    model.textures_[mesh.material_.names_.ambient_].Bind(0);
    model.textures_[mesh.material_.names_.diffuse_].Bind(1);
    model.textures_[mesh.material_.names_.specular_].Bind(2);

    graphics_pipeline_1_.SetUniform(ShaderKind::FRAGMENT, "u_material.shininess",
                                    mesh.material_.shininess);

    Command::DrawArrays(offset + mesh.vertices_offset_, mesh.vertices_size_);
  }
}

void ModelRenderer::DrawDepth(Model &model, const Transform &transform, const PointLight &light) {
  graphics_pipeline_2_.Bind();
  vertex_array_2_.Bind();

  float near_plane = 0.1f, far_plane = 10000.0f;
  auto light_projection = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f, near_plane, far_plane);

  auto light_view = glm::lookAt(light.position_, light.position_ - Z_, Vector3f(0.0, 1.0, 0.0));
  auto light_space_matrix = light_projection * light_view;

  graphics_pipeline_2_.SetUniform(ShaderKind::VERTEX, "u_model_matrix", transform.GetModelMatrix());
  graphics_pipeline_2_.SetUniform(ShaderKind::VERTEX, "u_light_space_matrix", light_space_matrix);

  auto offset = offsets_[model.path_];
  for (auto &mesh : model.meshes_) {
    Command::DrawArrays(offset + mesh.vertices_offset_, mesh.vertices_size_);
  }
}

void ModelRenderer::DrawWithPasses(Model &model, const Transform &transform,
                                   const PointLight &light, const Camera &camera) {

  Command::EnableDepthTest(true);
  Command::ClearColor();
  Command::ClearDepth();
  Command::SetViewport(0, 0, 1024, 1024);
  framebuffer_->Bind();
  depth_texture_->Bind(0);
  Command::ClearDepth();
  DrawDepth(model, transform, light);
  framebuffer_->Unbind();

  auto &window = Application::Get().GetWindow();

  Command::SetViewport(0, 0, window.GetWidth(), window.GetHeight());

  Command::ClearColor();
  Command::ClearDepth();
  Draw(model, transform, light, camera);
}

} // namespace Gloom