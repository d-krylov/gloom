#include "imgui_platform.h"
#include "imgui_renderer.h"
#include "renderer.h"
#include "window.h"
#include <array>
#include <iostream>

using Gloom::operator""_KiB;
using Gloom::operator""_MiB;

int main() {

  Gloom::ImGuiPlatform imgui_platform("Learn OpenGL: Camera", 800, 600);
  Gloom::ImGuiRenderer imgui_renderer;

  Gloom::EnableDebug();

  Gloom::Renderer renderer;

  Gloom::TextureDescription texture_description{.size_ = Gloom::Vector3i(800, 600, 0),
                                                .target_ = Gloom::TextureTarget::TEXTURE_2D,
                                                .format_ = Gloom::TextureInternalFormat::RGB8};

  Gloom::Texture fb_texture(texture_description);

  Gloom::Renderbuffer fb_renderbuffer(Gloom::TextureInternalFormat::DEPTH24_STENCIL8, 800,
                                      600);

  fb_renderbuffer.Bind();

  Gloom::FramebufferAttachment attachment_0(Gloom::FramebufferAttachmentType::COLOR0,
                                            &fb_texture);

  Gloom::FramebufferAttachment attachment_1(Gloom::FramebufferAttachmentType::DEPTH_STENCIL,
                                            &fb_renderbuffer);

  Gloom::Framebuffer framebuffer;
  framebuffer.Attach(attachment_0);
  framebuffer.Attach(attachment_1);

  auto root = Gloom::GetRoot();

  Gloom::Mesh mesh(root / "assets/wavefront/sibenik/sibenik.obj");

  mesh.GetNormal();

  renderer.ProcessMesh(mesh);

  Gloom::GraphicsPipeline pipeline{root / "shaders/vertex_pnt.vert",
                                   root / "shaders/blinn_phong_indirect.frag"};

  Gloom::GraphicsPipeline canvas{root / "shaders" / "canvas.vert",
                                 root / "shaders" / "canvas.frag"};
  Gloom::VertexArray vao;

  pipeline.Bind();

  Gloom::Camera camera;

  Gloom::Vector3f camera_position;
  float camera_rotation{0.0f};

  auto projection = camera.GetPerspectiveMatrix();

  pipeline.SetUniform(Gloom::ShaderIndex::VERTEX, "u_projection_matrix", projection);

  Gloom::Vector3f light_position(0.0f, 0.0f, 0.0f);
  Gloom::Vector3f light_color(0.0f, 0.0f, 0.0f);

  glEnable(GL_MULTISAMPLE);

  while (imgui_platform.GetWindow().ShouldClose() == false) {
    imgui_platform.GetWindow().PollEvents();

    pipeline.Bind();

    // framebuffer.Bind();
    Gloom::Commands::SetDepthTesting(true);
    Gloom::Commands::Clear(true);
    auto rot = linalg::rotation_quat(Gloom::Vector3f(0.0f, 1.0f, 0.0f), camera_rotation);
    auto model = linalg::rotation_matrix(rot);

    camera.SetPosition(camera_position);
    auto look = camera.GetLookAtMatrix();
    pipeline.SetUniform(Gloom::ShaderIndex::VERTEX, "u_view_matrix", look);

    pipeline.SetUniform(Gloom::ShaderIndex::VERTEX, "u_model_matrix", model);
    pipeline.SetUniform(Gloom::ShaderIndex::FRAGMENT, "u_light_position", light_position);
    pipeline.SetUniform(Gloom::ShaderIndex::FRAGMENT, "u_light_color", light_color);

    //    for (uint32_t i = 0; i < mesh.materials_.size(); i++) {
    //      mesh.materials_[i]->Bind(i);
    //    }

    renderer.Draw();
    // framebuffer.Unbind();
    // Gloom::Commands::Clear();
    Gloom::Commands::SetDepthTesting(false);

#if 0 
    vao.Bind();
    canvas.Bind();
    canvas.SetUniform(Gloom::ShaderIndex::FRAGMENT, "u_texture", 0);
    fb_texture.Bind(0);
    Gloom::Commands::DrawArrays(0, 3);
#endif

    imgui_platform.NewFrame();
    imgui_renderer.Begin();

    ImGui::Begin("window");
    ImGui::InputFloat3("light position", Gloom::Cast(light_position));
    ImGui::InputFloat3("light color", Gloom::Cast(light_color));
    ImGui::InputFloat3("camera position", Gloom::Cast(camera_position));
    ImGui::SliderFloat("obj rotation", &camera_rotation, 0.0f, 6.28f);
    ImGui::End();

    imgui_renderer.End();

    imgui_platform.GetWindow().Update();
  }

  return 0;
}