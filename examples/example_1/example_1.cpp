#include "graphics.h"
#include "imgui_platform.h"
#include "imgui_renderer.h"
#include "window.h"
#include <iostream>

using Gloom::Types::operator""_KiB;
using Gloom::Types::operator""_MiB;

int main() {

  Gloom::ImGuiPlatform imgui_platform("Learn OpenGL: Camera", 800, 600);
  Gloom::ImGuiRenderer imgui_renderer;

  Gloom::EnableDebug();

  auto vertices = Gloom::MakeBox();

  auto root = Gloom::GetRoot();
  Gloom::GraphicsPipeline pipeline(root / "shaders/instance_pnt.vert",
                                   root / "shaders/pbr.frag");

  pipeline.Bind();
  Gloom::VertexArray vao;

  Gloom::Image image(root / "assets/images/container.png");
  Gloom::Texture texture(Gloom::Types::TextureTarget::TEXTURE_2D, image);

  texture.SetData(image.GetData());
  texture.Bind(0);

  std::vector<Gloom::Types::Matrix4f> positions;

  for (int32_t i = -10; i <= 10; i += 2) {
    for (int32_t j = -10; j <= 10; j += 2) {
      Gloom::Types::Vector3f position(float(i), -2.0f, float(j));
      positions.emplace_back(linalg::translation_matrix(position));
    }
  }

  Gloom::Buffer ssbo(Gloom::Types::BufferTarget::SHADER_STORAGE_BUFFER, 16_KiB);

  ssbo.SetData(std::span<Gloom::Types::Matrix4f>(positions));
  ssbo.BindRange(0);

  Gloom::VertexBuffer vbo(4_KiB, Gloom::Vertex::GetFormat());

  vbo.SetData(std::span<Gloom::Vertex>(vertices));

  vao.AddVertexBuffer(vbo);
  vao.Bind();

  Gloom::Camera camera;

  Gloom::Types::Vector3f position(0.0f, 0.0f, 5.0f);
  camera.SetPosition(position);

  auto projection = camera.GetPerspectiveMatrix();
  auto look = camera.GetLookAtMatrix();

  pipeline.SetUniform(Gloom::Types::ShaderIndex::VERTEX, "u_projection_matrix", projection);
  pipeline.SetUniform(Gloom::Types::ShaderIndex::VERTEX, "u_view_matrix", look);

  Gloom::Types::Vector3f light_position(0.0f, 0.0f, 0.0f);
  Gloom::Types::Vector3f light_color(0.0f, 0.0f, 0.0f);

  while (imgui_platform.GetWindow().ShouldClose() == false) {
    imgui_platform.GetWindow().PollEvents();

    Gloom::Commands::Clear();
    pipeline.Bind();
    vao.Bind();
    texture.Bind(0);

    Gloom::Commands::SetDepthTesting(true);

    pipeline.SetUniform(Gloom::Types::ShaderIndex::FRAGMENT, "u_light_position",
                        light_position);
    pipeline.SetUniform(Gloom::Types::ShaderIndex::FRAGMENT, "u_light_color", light_color);
    pipeline.SetUniform(Gloom::Types::ShaderIndex::FRAGMENT, "u_view_position", position);

    Gloom::Commands::DrawArraysInstanced(Gloom::Types::PrimitiveKind::TRIANGLES, 0,
                                         vertices.size(), 100);

    imgui_platform.NewFrame();
    imgui_renderer.Begin();

    ImGui::Begin("window");
    ImGui::SliderFloat3("light position", Gloom::Types::Cast(light_position), 0.0f, 20.0f);
    ImGui::SliderFloat3("light color", Gloom::Types::Cast(light_color), 0.0f, 5.0f);

    ImGui::End();
    imgui_renderer.End();

    imgui_platform.GetWindow().Update();
  }

  return 0;
}