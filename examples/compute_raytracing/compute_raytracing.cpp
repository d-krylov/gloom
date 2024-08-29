#include "gloom/application/include/gloom.h"
#include <iostream>

using namespace Gloom;

constexpr uint32_t TEXTURE_WIDTH = 1000;
constexpr uint32_t TEXTURE_HEIGHT = 1000;

class ComputeRaytracing : public Layer {
public:
  ComputeRaytracing()
    : vao_(), compute_pipeline_(SHADERS_DIR / "compute" / "raytracing.comp"),
      graphics_pipeline_{SHADERS_DIR / "raytracing" / "canvas.vert",
                         SHADERS_DIR / "raytracing" / "canvas.frag"} {
    Gloom::EnableDebug();
  }

  void OnImGui() override {
    ImGui::Begin("Hello");
    ImGui::End();
  }

  void OnUpdate() override {
    texture_->Bind(0);
    texture_->BindImage(0, 0, false, 0, Access::READ_WRITE);
    vao_.Bind();
    compute_pipeline_.Bind();
    compute_pipeline_.SetUniform("t", float(GetTime()));

    Command::DispatchCompute(TEXTURE_WIDTH / 10, TEXTURE_HEIGHT / 10, 1);
    Command::MemoryBarrier(BarrierBit::SHADER_IMAGE_ACCESS);

    graphics_pipeline_.Bind();
    texture_->Bind(0);
    Command::DrawArrays(0, 3);
  }

  void OnAttach() override {
    texture_ = std::make_unique<Texture2D>(TEXTURE_WIDTH, TEXTURE_HEIGHT, InternalFormat::RGBA32F);
  }

private:
  VertexArray vao_;
  ComputePipeline compute_pipeline_;
  GraphicsPipeline graphics_pipeline_;
  std::unique_ptr<Texture> texture_;
};

int main() {
  Application application;
  ComputeRaytracing compute_raytracing;
  application.AddLayer(&compute_raytracing);
  application.Run();
  return 0;
}