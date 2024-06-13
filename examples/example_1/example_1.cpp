#include "gloom/include/application.h"
#include "graphics.h"
#include "window.h"
#include <iostream>

using Gloom::operator""_KiB;
using Gloom::operator""_MiB;

class MyApp : public Gloom::Application {
public:
  MyApp()
    : Application(), vao_(), vbo_(4_MiB, Gloom::Vertex::GetFormat()),
      graphics_pipeline_{Gloom::GetRoot() / "shaders" / "vertex_pnt.vert",
                         Gloom::GetRoot() / "shaders" / "pbr.frag"} {
    Gloom::EnableDebug();
  }

  void OnImGui() override {
    auto position = camera_.GetPosition();

    ImGui::Begin("Window");
    ImGui::InputFloat3("light position", Gloom::Cast(light_position_));
    ImGui::InputFloat3("light color", Gloom::Cast(light_color_));
    ImGui::InputFloat3("camera position", Gloom::Cast(position));
    ImGui::SliderFloat3("Rotation", Gloom::Cast(rotation_), 0.0f, 2.0f * Gloom::PI);
    ImGui::SliderFloat("Metallic", &metallic_, 0.0f, 1.0f);
    ImGui::SliderFloat("Roughness", &roughness_, 0.0f, 1.0f);
    ImGui::End();

    camera_.SetPosition(position);
  }

  void OnUpdate() override {
    Gloom::Commands::SetDepthTesting(true);
    Gloom::Commands::Clear(true);

    vao_.Bind();
    graphics_pipeline_.Bind();

    auto projection = camera_.GetPerspectiveMatrix();
    auto look = camera_.GetLookAtMatrix();

    graphics_pipeline_.SetUniform(Gloom::ShaderIndex::VERTEX, "u_view_matrix", look);
    graphics_pipeline_.SetUniform(Gloom::ShaderIndex::VERTEX, "u_projection_matrix",
                                  projection);
    graphics_pipeline_.SetUniform(Gloom::ShaderIndex::FRAGMENT, "u_light_position",
                                  light_position_);
    graphics_pipeline_.SetUniform(Gloom::ShaderIndex::FRAGMENT, "u_light_color", light_color_);
    graphics_pipeline_.SetUniform(Gloom::ShaderIndex::FRAGMENT, "u_view_position",
                                  camera_.GetPosition());
    graphics_pipeline_.SetUniform(Gloom::ShaderIndex::FRAGMENT, "u_metallic", metallic_);
    graphics_pipeline_.SetUniform(Gloom::ShaderIndex::FRAGMENT, "u_roughness", roughness_);

    auto rotate = Gloom::RotateX(Gloom::Degrees(rotation_.x));
    rotate = linalg::mul(rotate, Gloom::RotateY(Gloom::Degrees(rotation_.y)));
    rotate = linalg::mul(rotate, Gloom::RotateZ(Gloom::Degrees(rotation_.z)));

    graphics_pipeline_.SetUniform(Gloom::ShaderIndex::VERTEX, "u_model_matrix", rotate);

    Gloom::Commands::DrawArrays(0, 24);
  }

  void OnInitialize() override {
    camera_.SetPosition(Gloom::Vector3f(0.0f, 0.0f, 5.0f));
    auto cube = Gloom::MakeOctahedron();
    vbo_.SetData(std::span<Gloom::Vertex>(cube));
    vao_.AddVertexBuffer(vbo_);
  }

private:
  float metallic_{0.0f};
  float roughness_{0.0f};
  Gloom::Vector3f light_color_;
  Gloom::Vector3f light_position_;
  Gloom::Vector3f rotation_;
  Gloom::Camera camera_;
  Gloom::VertexBuffer vbo_;
  Gloom::VertexArray vao_;
  Gloom::GraphicsPipeline graphics_pipeline_;
};

int main() {
  MyApp app;

  app.Run();

  return 0;
}