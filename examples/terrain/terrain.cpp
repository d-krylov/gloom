#include "gloom/include/application.h"
#include "gloom_widgets/include/camera_widget.h"
#include <iostream>

using Gloom::operator""_KiB;
using Gloom::operator""_MiB;

class MyApp : public Gloom::Application {
public:
  MyApp()
    : Application(), vao_(), vbo_(20_MiB, Gloom::Vertex::GetFormat()),
      ibo_(Gloom::BufferTarget::ELEMENT_ARRAY_BUFFER, 20_MiB),
      graphics_pipeline_{Gloom::GetRoot() / "shaders" / "terrain" / "terrain.vert",
                         Gloom::GetRoot() / "shaders" / "terrain" / "terrain.tesc",
                         Gloom::GetRoot() / "shaders" / "terrain" / "terrain.tese",
                         Gloom::GetRoot() / "shaders" / "terrain" / "terrain.frag"} {
    Gloom::EnableDebug();
  }

  void OnImGui() override {
    camera_.OnImGui();

    ImGui::Begin("Window");
    ImGui::InputFloat3("light direction", glm::value_ptr(light_direction_));
    ImGui::InputFloat3("zoom", glm::value_ptr(zoom_));
    ImGui::End();
  }

  void OnUpdate() override {
    Gloom::Commands::SetDepthTesting(true);
    Gloom::Commands::Clear(true);

    glPatchParameteri(GL_PATCH_VERTICES, 4);

    graphics_pipeline_.Bind();
    texture_->Bind(0);
    vao_.Bind();

    camera_.OnUpdate();
    auto &camera = camera_.GetCamera();

    auto projection = camera.GetPerspectiveMatrix();
    auto look = camera.GetLookAtMatrix();

    auto zoom = glm::scale(Gloom::Matrix4f(1.0f), zoom_);

    graphics_pipeline_.SetUniform(Gloom::ShaderIndex::TESSELATION_EVALUATION, "u_view_matrix",
                                  look);
    graphics_pipeline_.SetUniform(Gloom::ShaderIndex::TESSELATION_EVALUATION,
                                  "u_projection_matrix", projection);
    graphics_pipeline_.SetUniform(Gloom::ShaderIndex::TESSELATION_EVALUATION, "u_model_matrix",
                                  zoom);
    graphics_pipeline_.SetUniform(Gloom::ShaderIndex::TESSELATION_EVALUATION, "u_height_map",
                                  0);
    graphics_pipeline_.SetUniform(Gloom::ShaderIndex::FRAGMENT, "u_light_direction",
                                  light_direction_);
    // Gloom::Commands::SetPolygonMode(Gloom::PolygonMode::LINE);
    Gloom::Commands::DrawElements(Gloom::PrimitiveKind::PATCHES, 4 * 64 * 64);
  }

  void OnInitialize() override {
    Gloom::Image image(Gloom::GetRoot() / "assets" / "heightmap" / "heightmap.png");
    texture_ = std::make_unique<Gloom::Texture>(image);
    auto size = image.GetSize();
    auto vertices = Gloom::CreateGridVertices(64, size.x, size.y);
    auto indices = Gloom::CreateGridIndices(64);

    vbo_.SetData(vertices);
    ibo_.SetData(indices);

    vao_.AddVertexBuffer(vbo_);
    vao_.SetIndexBuffer(ibo_);
  }

private:
  Gloom::VertexArray vao_;
  Gloom::VertexBuffer vbo_;
  Gloom::Buffer ibo_;
  Gloom::GraphicsPipeline graphics_pipeline_;
  std::unique_ptr<Gloom::Texture> texture_;
  Gloom::Vector3f light_direction_;
  Gloom::Vector3f zoom_;
  Gloom::CameraWidget camera_;
};

int main() {

  MyApp app;

  app.Run();
}