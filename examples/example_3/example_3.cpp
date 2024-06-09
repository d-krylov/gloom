#include "graphics.h"
#include "imgui_platform.h"
#include "imgui_renderer.h"
#include "window.h"
#include <array>
#include <iostream>

using Gloom::operator""_KiB;
using Gloom::operator""_MiB;

int main() {

  Gloom::ImGuiPlatform imgui_platform("Learn OpenGL: Camera", 800, 600);
  Gloom::ImGuiRenderer imgui_renderer;

  Gloom::EnableDebug();

  Gloom::Mesh mesh;

  auto root = Gloom::GetRoot();
  mesh.Load(root / "assets/wavefront/monkey/monkey.obj");

  Gloom::GraphicsPipeline pipeline{root / "shaders/vertex_pnt.vert",
                                   root / "shaders/texture_pbr.frag"};

  pipeline.Bind();
  Gloom::VertexArray vao;

  Gloom::Image color(root / "assets/wavefront/monkey/color.png");
  Gloom::Image metallic(root / "assets/wavefront/monkey/metallic.png");
  Gloom::Image normal(root / "assets/wavefront/monkey/normal.png");
  Gloom::Image roughness(root / "assets/wavefront/monkey/roughness.png");

  Gloom::Texture tcolor(color);
  Gloom::Texture tmetallic(metallic);
  Gloom::Texture tnormal(normal);
  Gloom::Texture troughness(roughness);

  tcolor.Bind(0);
  tnormal.Bind(1);
  tmetallic.Bind(2);
  troughness.Bind(3);

  Gloom::VertexBuffer vbo(10_MiB, Gloom::Vertex::GetFormat());

  vbo.SetData(std::span<Gloom::Vertex>(mesh.vertices_));

  vao.AddVertexBuffer(vbo);
  vao.Bind();

  Gloom::Camera camera;

  camera.SetPosition(Gloom::Vector3f(0.0f, 0.0f, 5.0f));

  auto projection = camera.GetPerspectiveMatrix();
  auto look = camera.GetLookAtMatrix();

  pipeline.SetUniform(Gloom::ShaderIndex::VERTEX, "u_projection_matrix", projection);
  pipeline.SetUniform(Gloom::ShaderIndex::VERTEX, "u_view_matrix", look);

  Gloom::Vector3f light_position(0.0f, 0.0f, 0.0f);
  Gloom::Vector3f light_color(0.0f, 0.0f, 0.0f);

  while (imgui_platform.GetWindow().ShouldClose() == false) {
    imgui_platform.GetWindow().PollEvents();

    Gloom::Commands::Clear();
    pipeline.Bind();
    vao.Bind();

    Gloom::Commands::SetDepthTesting(true);
    auto rot =
      linalg::rotation_quat(Gloom::Vector3f(0.0f, 1.0f, 0.0f), float(Gloom::GetTime()));
    auto model = linalg::rotation_matrix(rot);

    pipeline.SetUniform(Gloom::ShaderIndex::VERTEX, "u_model_matrix", model);
    pipeline.SetUniform(Gloom::ShaderIndex::FRAGMENT, "u_light_position", light_position);
    pipeline.SetUniform(Gloom::ShaderIndex::FRAGMENT, "u_light_color", light_color);

    Gloom::Commands::DrawArrays(0, mesh.vertices_.size());

    imgui_platform.NewFrame();
    imgui_renderer.Begin();

    ImGui::Begin("window");
    ImGui::SliderFloat3("light position", Gloom::Cast(light_position), 0.0f, 20.0f);
    ImGui::SliderFloat3("light color", Gloom::Cast(light_color), 0.0f, 1.0f);
    ImGui::End();
    imgui_renderer.End();

    imgui_platform.GetWindow().Update();
  }

  return 0;
}