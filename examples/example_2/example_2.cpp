#include "graphics.h"
#include "imgui_platform.h"
#include "imgui_renderer.h"
#include "window.h"
#include <array>

using Gloom::Types::operator""_KiB;
using Gloom::Types::operator""_MiB;

int main() {

  Gloom::ImGuiPlatform imgui_platform("Learn OpenGL: Camera", 800, 600);
  Gloom::ImGuiRenderer imgui_renderer;

  Gloom::EnableDebug();

  auto vertices = Gloom::MakeBox();

  auto root = Gloom::GetRoot();
  Gloom::GraphicsPipeline pipeline(root / "shaders/vertex_pnt.vert",
                                   root / "shaders/blinn_phong.frag");

  pipeline.Bind();
  Gloom::VertexArray vao;

  Gloom::Image image(root / "assets/images/container.png");
  Gloom::Texture texture(image);

  texture.Bind(0);

  Gloom::VertexBuffer vbo(4_KiB, Gloom::Vertex::GetFormat());

  vbo.SetData(std::span<Gloom::Vertex>(vertices));

  vao.AddVertexBuffer(vbo);
  vao.Bind();

  Gloom::Camera camera;

  camera.SetPosition(Gloom::Types::Vector3f(0.0f, 0.0f, 5.0f));

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
    auto rot =
      linalg::rotation_quat(Gloom::Types::Vector3f(0.0f, 1.0f, 0.0f), float(Gloom::GetTime()));
    auto model = linalg::rotation_matrix(rot);

    pipeline.SetUniform(Gloom::Types::ShaderIndex::VERTEX, "u_model_matrix", model);
    pipeline.SetUniform(Gloom::Types::ShaderIndex::FRAGMENT, "u_light_position",
                        light_position);
    pipeline.SetUniform(Gloom::Types::ShaderIndex::FRAGMENT, "u_light_color", light_color);

    Gloom::Commands::DrawArrays(Gloom::Types::PrimitiveKind::TRIANGLES, 0, vertices.size());

    imgui_platform.NewFrame();
    imgui_renderer.Begin();

    ImGui::Begin("window");
    ImGui::SliderFloat3("light position", Gloom::Types::Cast(light_position), 0.0f, 20.0f);
    ImGui::SliderFloat3("light color", Gloom::Types::Cast(light_color), 0.0f, 1.0f);
    // auto size = ImGui::GetContentRegionAvail();
    // ImGui::Image((void *)(intptr_t)texture, size);
    ImGui::End();
    imgui_renderer.End();

    imgui_platform.GetWindow().Update();
  }

  return 0;
}