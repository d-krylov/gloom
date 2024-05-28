#include "imgui_platform.h"
#include "imgui_renderer.h"
#include "renderer.h"
#include "window.h"
#include <array>
#include <iostream>

using Gloom::Types::operator""_KiB;
using Gloom::Types::operator""_MiB;

int main() {

  Gloom::ImGuiPlatform imgui_platform("Learn OpenGL: Camera", 800, 600);
  Gloom::ImGuiRenderer imgui_renderer;

  Gloom::EnableDebug();

  Gloom::Renderer renderer;

  Gloom::Mesh mesh;

  auto root = Gloom::GetRoot();
  mesh.Load(root / "assets/wavefront/sibenik/sibenik.obj");
  mesh.GetNormal();

  renderer.ProcessMesh(mesh);

  Gloom::GraphicsPipeline pipeline(root / "shaders/vertex_pnt.vert",
                                   root / "shaders/blinn_phong_indirect.frag");

  pipeline.Bind();

  Gloom::Camera camera;

  Gloom::Types::Vector3f camera_position;
  float camera_rotation{0.0f};

  auto projection = camera.GetPerspectiveMatrix();

  pipeline.SetUniform(Gloom::Types::ShaderIndex::VERTEX, "u_projection_matrix", projection);

  Gloom::Types::Vector3f light_position(0.0f, 0.0f, 0.0f);
  Gloom::Types::Vector3f light_color(0.0f, 0.0f, 0.0f);

  while (imgui_platform.GetWindow().ShouldClose() == false) {
    imgui_platform.GetWindow().PollEvents();

    Gloom::Commands::Clear();
    pipeline.Bind();

    Gloom::Commands::SetDepthTesting(true);
    auto rot =
      linalg::rotation_quat(Gloom::Types::Vector3f(0.0f, 1.0f, 0.0f), camera_rotation);
    auto model = linalg::rotation_matrix(rot);

    camera.SetPosition(camera_position);
    auto look = camera.GetLookAtMatrix();
    pipeline.SetUniform(Gloom::Types::ShaderIndex::VERTEX, "u_view_matrix", look);

    pipeline.SetUniform(Gloom::Types::ShaderIndex::VERTEX, "u_model_matrix", model);
    pipeline.SetUniform(Gloom::Types::ShaderIndex::FRAGMENT, "u_light_position",
                        light_position);
    pipeline.SetUniform(Gloom::Types::ShaderIndex::FRAGMENT, "u_light_color", light_color);

    for (uint32_t i = 0; i < mesh.materials_.size(); i++) {
      mesh.materials_[i]->Bind(i);
    }

    renderer.Draw();

    imgui_platform.NewFrame();
    imgui_renderer.Begin();

    ImGui::Begin("window");
    ImGui::SliderFloat3("light position", Gloom::Types::Cast(light_position), 0.0f, 40.0f);
    ImGui::SliderFloat3("light color", Gloom::Types::Cast(light_color), 0.0f, 10.0f);
    ImGui::SliderFloat3("camera position", Gloom::Types::Cast(camera_position), -30.0f, 40.0f);
    ImGui::SliderFloat("obj rotation", &camera_rotation, 0.0f, 6.28f);
    ImGui::End();
    imgui_renderer.End();

    imgui_platform.GetWindow().Update();
  }

  return 0;
}