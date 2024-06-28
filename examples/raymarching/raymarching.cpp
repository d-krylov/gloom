#include "gloom/include/application.h"

using Gloom::operator""_KiB;
using Gloom::operator""_MiB;

constexpr uint32_t MAX_OBJECTS = 1;

struct Light {
  Gloom::Vector3f position_{0.0f, 0.0f, 0.0f};
  Gloom::Vector3f color_{0.0f, 0.0f, 0.0f};
  Gloom::Vector3f attenuation_{0.0f, 0.0f, 0.0f};
};

struct Object {
  Gloom::Vector3f position_{0.0f, 0.0f, 0.0f};
  Gloom::Vector3f size_{0.0f, 0.0f, 0.0f};
  Gloom::Vector3f rotation_{0.0f, 0.0f, 0.0f};
  float material_{0.0f};
  float visible{0.0f};
};

struct Material {
  Gloom::Vector3f albedo_{0.0f, 0.0f, 0.0f};
  float metallic_{0.0f};
  float roughness_{0.0f};
};

class RayMarching : public Gloom::Application {
public:
  RayMarching()
    : Application(), vao_(), ligth_ssbo(Gloom::BufferTarget::SHADER_STORAGE_BUFFER, 10_KiB),
      material_ssbo(Gloom::BufferTarget::SHADER_STORAGE_BUFFER, 10_KiB),
      object_ssbo(Gloom::BufferTarget::SHADER_STORAGE_BUFFER, 10_KiB),
      graphics_pipeline_{Gloom::GetRoot() / "shaders" / "canvas.vert",
                         Gloom::GetRoot() / "shaders" / "ray.frag"} {
    Gloom::EnableDebug();
  }

  void OnInitialize() {}

  void LightUI() {
    if (ImGui::CollapsingHeader("Lights")) {
      for (uint32_t i = 0; i < lights_.size(); i++) {
        ImGui::PushID(i);
        if (ImGui::CollapsingHeader("Light")) {
          ImGui::InputFloat3("Position   ", glm::value_ptr(lights_[i].position_));
          ImGui::InputFloat3("Color      ", glm::value_ptr(lights_[i].color_));
          ImGui::InputFloat3("Attenuation", glm::value_ptr(lights_[i].attenuation_));
        }
        ImGui::PopID();
      }
    }
  }

  void ObjectUI() {
    if (ImGui::CollapsingHeader("Objects")) {
      for (uint32_t i = 0; i < objects_.size(); i++) {
        ImGui::PushID(i);
        if (ImGui::CollapsingHeader("Object")) {
          ImGui::InputFloat3("Position", glm::value_ptr(objects_[i].position_));
          ImGui::InputFloat3("Size    ", glm::value_ptr(objects_[i].size_));
          ImGui::InputFloat3("Rotation", glm::value_ptr(objects_[i].rotation_));
        }
        ImGui::PopID();
      }
    }
  }

  void MaterialUI() {
    if (ImGui::CollapsingHeader("Materials")) {
      for (uint32_t i = 0; i < materials_.size(); i++) {
        ImGui::PushID(i);
        if (ImGui::CollapsingHeader("Material")) {
          ImGui::InputFloat3("Albedo", glm::value_ptr(materials_[i].albedo_));
          ImGui::InputFloat("Metallic", &materials_[i].metallic_);
          ImGui::InputFloat3("Roughness", &materials_[i].roughness_);
        }
        ImGui::PopID();
      }
    }
  }

  void OnImGui() override {
    ImGui::Begin("Settings");

    LightUI();
    ObjectUI();
    MaterialUI();

    ImGui::End();
  }

  void OnUpdate() override {
    Gloom::Commands::Clear(true);
    vao_.Bind();
    graphics_pipeline_.Bind();
    ligth_ssbo.BindRange(0);
    ligth_ssbo.SetData(std::span<Light>(lights_));
    object_ssbo.BindRange(1);
    object_ssbo.SetData(std::span<Object>(objects_));
    material_ssbo.BindRange(2);
    material_ssbo.SetData(std::span<Material>(materials_));
    Gloom::Commands::DrawArrays(0, 3);
  }

private:
  Gloom::VertexArray vao_;
  Gloom::Buffer ligth_ssbo;
  Gloom::Buffer material_ssbo;
  Gloom::Buffer object_ssbo;
  Gloom::GraphicsPipeline graphics_pipeline_;

  std::array<Light, MAX_OBJECTS> lights_;
  std::array<Object, MAX_OBJECTS> objects_;
  std::array<Material, MAX_OBJECTS> materials_;
};

int main() {
  RayMarching raymarching;

  raymarching.Run();

  return 0;
}