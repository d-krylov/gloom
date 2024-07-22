#include "gloom/include/application.h"
#include "window.h"
#include <iostream>

using Gloom::operator""_KiB;
using Gloom::operator""_MiB;

class MyApp : public Gloom::Application {
public:
  MyApp()
    : Application(), vao_(), vbo_(4_KiB, Gloom::Vertex::GetFormat()),
      graphics_pipeline_{Gloom::GetRoot() / "shaders" / "skybox" / "skybox.vert",
                         Gloom::GetRoot() / "shaders" / "skybox" / "skybox.frag"} {
    Gloom::EnableDebug();
  }

  void OnImGui() override {

    auto position = camera_.GetPosition();

    auto yaw = camera_.GetYaw();
    auto pitch = camera_.GetPitch();

    ImGui::Begin("Window");
    ImGui::InputFloat3("camera position", glm::value_ptr(position));
    ImGui::SliderFloat("camera yaw", &yaw, 0.0f, 2.0f * Gloom::PI);
    ImGui::SliderFloat("camera pitch", &pitch, 0.0f, 2.0f * Gloom::PI);
    ImGui::End();

    camera_.SetPosition(position);
    camera_.SetYaw(yaw);
    camera_.SetPitch(pitch);
  }

  void OnUpdate() override {
    Gloom::Commands::SetDepthTesting(true);
    Gloom::Commands::Clear(true);
    glDepthFunc(GL_LEQUAL);
    auto projection = camera_.GetPerspectiveMatrix();
    auto look = camera_.GetLookAtMatrix();
    graphics_pipeline_.Bind();
    vao_.Bind();
    texture_->Bind(0);
    graphics_pipeline_.SetUniform(Gloom::ShaderIndex::VERTEX, "u_view_matrix",
                                  Gloom::Matrix4f(Gloom::Matrix3f(look)));
    graphics_pipeline_.SetUniform(Gloom::ShaderIndex::VERTEX, "u_projection_matrix",
                                  projection);
    graphics_pipeline_.SetUniform(Gloom::ShaderIndex::FRAGMENT, "skybox", 0);
    Gloom::Commands::DrawArrays(0, 36);
    glDepthFunc(GL_LESS);
  }

  void OnInitialize() override {
    auto data = Gloom::MakeBox();
    vbo_.SetData(std::span<Gloom::Vertex>(data));
    vao_.AddVertexBuffer(vbo_);

    Gloom::CubeMap cubemap(
      {Gloom::GetRoot() / "assets" / "cubemap" / "cubemap_2" / "miramar_ft.tga",
       Gloom::GetRoot() / "assets" / "cubemap" / "cubemap_2" / "miramar_bk.tga",
       Gloom::GetRoot() / "assets" / "cubemap" / "cubemap_2" / "miramar_up.tga",
       Gloom::GetRoot() / "assets" / "cubemap" / "cubemap_2" / "miramar_dn.tga",
       Gloom::GetRoot() / "assets" / "cubemap" / "cubemap_2" / "miramar_rt.tga",
       Gloom::GetRoot() / "assets" / "cubemap" / "cubemap_2" / "miramar_lf.tga"});

    texture_ = std::make_unique<Gloom::Texture>(cubemap);
  }

private:
  Gloom::Camera camera_;
  Gloom::VertexArray vao_;
  Gloom::VertexBuffer vbo_;
  Gloom::GraphicsPipeline graphics_pipeline_;
  std::unique_ptr<Gloom::Texture> texture_;
};

int main() {
  MyApp app;

  app.Run();

  return 0;
}