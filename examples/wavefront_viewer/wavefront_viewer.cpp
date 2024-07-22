#include "gloom/include/application.h"
#include "graphics.h"
#include "window.h"
#include <iostream>

using Gloom::operator""_KiB;
using Gloom::operator""_MiB;

class MyApp : public Gloom::Application {
public:
  MyApp()
    : Application(), vao_(), vbo_(512_MiB, Gloom::Vertex::GetFormat()),
      graphics_pipeline_{Gloom::GetRoot() / "shaders" / "vertex_pnt.vert",
                         Gloom::GetRoot() / "shaders" / "blinn_phong.frag"} {
    Gloom::EnableDebug();
  }

  void OnImGui() override {
    auto position = camera_.GetPosition();

    ImGui::Begin("Window");
    ImGui::InputFloat3("light position", glm::value_ptr(light_.position_));
    ImGui::InputFloat3("light ambient", glm::value_ptr(light_.ambient_));
    ImGui::InputFloat3("light diffuse", glm::value_ptr(light_.diffuse_));
    ImGui::InputFloat3("light specular", glm::value_ptr(light_.specular_));
    ImGui::InputFloat3("camera position", glm::value_ptr(position));
    ImGui::SliderFloat3("Rotation", glm::value_ptr(rotation_), 0.0f, 2.0f * Gloom::PI);
    ImGui::End();

    camera_.SetPosition(position);
  }

  void SetUniform() {
    auto projection = camera_.GetPerspectiveMatrix();
    auto look = camera_.GetLookAtMatrix();

    graphics_pipeline_.SetUniform(Gloom::ShaderIndex::VERTEX, "u_view_matrix", look);
    graphics_pipeline_.SetUniform(Gloom::ShaderIndex::VERTEX, "u_projection_matrix",
                                  projection);
    graphics_pipeline_.SetUniform(Gloom::ShaderIndex::FRAGMENT, "u_light.position",
                                  light_.position_);
    graphics_pipeline_.SetUniform(Gloom::ShaderIndex::FRAGMENT, "u_light.ambient",
                                  light_.ambient_);
    graphics_pipeline_.SetUniform(Gloom::ShaderIndex::FRAGMENT, "u_light.diffuse",
                                  light_.diffuse_);
    graphics_pipeline_.SetUniform(Gloom::ShaderIndex::FRAGMENT, "u_light.specular",
                                  light_.specular_);
    graphics_pipeline_.SetUniform(Gloom::ShaderIndex::FRAGMENT, "u_view_position",
                                  camera_.GetPosition());

    graphics_pipeline_.SetUniform(Gloom::ShaderIndex::FRAGMENT, "u_material.ambient_map", 0);
    graphics_pipeline_.SetUniform(Gloom::ShaderIndex::FRAGMENT, "u_material.diffuse_map", 1);
    graphics_pipeline_.SetUniform(Gloom::ShaderIndex::FRAGMENT, "u_material.specular_map", 2);

    auto rotate = glm::rotate(Gloom::Matrix4f(1.0f), rotation_.x, Gloom::X);
    rotate = glm::rotate(rotate, rotation_.y, Gloom::Y);
    rotate = glm::rotate(rotate, rotation_.z, Gloom::Z);

    graphics_pipeline_.SetUniform(Gloom::ShaderIndex::VERTEX, "u_model_matrix", rotate);
  }

  void OnUpdate() {
    Gloom::Commands::SetDepthTesting(true);
    Gloom::Commands::Clear(true);

    vao_.Bind();
    graphics_pipeline_.Bind();

    auto sub_count = mesh_->offsets_.size();

    SetUniform();

    for (uint32_t i = 0; i < sub_count; i++) {

      auto material_index = mesh_->material_indices_[i];

      auto ambient = mesh_->materials_[material_index].properties_->ambient_;
      auto diffuse = mesh_->materials_[material_index].properties_->diffuse_;
      auto specular = mesh_->materials_[material_index].properties_->specular_;
      auto shininess = mesh_->materials_[material_index].properties_->shininess_;

      graphics_pipeline_.SetUniform(Gloom::ShaderIndex::FRAGMENT, "u_material.ambient",
                                    ambient);
      graphics_pipeline_.SetUniform(Gloom::ShaderIndex::FRAGMENT, "u_material.diffuse",
                                    diffuse);
      graphics_pipeline_.SetUniform(Gloom::ShaderIndex::FRAGMENT, "u_material.specular",
                                    specular);
      graphics_pipeline_.SetUniform(Gloom::ShaderIndex::FRAGMENT, "u_material.shininess",
                                    shininess);

      if (mesh_->materials_[material_index].ambient_texture_) {
        mesh_->materials_[material_index].ambient_texture_->Bind(0);
      }

      if (mesh_->materials_[material_index].diffuse_texture_) {
        mesh_->materials_[material_index].diffuse_texture_->Bind(1);
      }

      if (mesh_->materials_[material_index].specular_texture_) {
        mesh_->materials_[material_index].specular_texture_->Bind(2);
      }

      uint32_t count{0};

      if (i < sub_count - 1) {
        count = mesh_->offsets_[i + 1] - mesh_->offsets_[i];
      } else {
        count = mesh_->vertices_.size() - mesh_->offsets_[i];
      }

      Gloom::Commands::DrawArrays(mesh_->offsets_[i], count);
    }
  }

  void OnInitialize() {
    auto root = Gloom::GetRoot();
    mesh_ = std::make_shared<Gloom::Mesh>(root / "assets" / "wavefront" / "Sponza-master" /
                                          "sponza.obj");

    mesh_->GetNormal();
    vbo_.SetData(mesh_->GetVertices());
    vao_.AddVertexBuffer(vbo_);
  }

private:
  std::shared_ptr<Gloom::Mesh> mesh_;
  Gloom::Light light_;
  Gloom::Camera camera_;
  Gloom::Vector3f rotation_;
  Gloom::VertexBuffer vbo_;
  Gloom::VertexArray vao_;
  Gloom::GraphicsPipeline graphics_pipeline_;
};

int main() {

  MyApp app;

  app.Run();

  return 0;
}