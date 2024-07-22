#include "gloom/include/application.h"
#include "graphics.h"
#include "window.h"
#include <iostream>

using namespace Gloom;

constexpr uint32_t TEXTURE_WIDTH = 1000;
constexpr uint32_t TEXTURE_HEIGHT = 1000;

class ComputeRaytracing : public Gloom::Application {
public:
  ComputeRaytracing()
    : Application(), vao_(),
      compute_pipeline_(GetRoot() / "shaders" / "compute" / "raytracing.comp"),
      graphics_pipeline_{GetRoot() / "shaders" / "raytracing" / "canvas.vert",
                         GetRoot() / "shaders" / "raytracing" / "canvas.frag"} {
    Gloom::EnableDebug();
  }

  void OnImGui() override {}

  void OnUpdate() override {
    texture_->Bind(0);
    texture_->BindImage(0, 0, false, 0, Access::READ_WRITE);
    vao_.Bind();
    compute_pipeline_.Bind();
    compute_pipeline_.SetUniform("t", float(GetTime()));

    Commands::DispatchCompute(TEXTURE_WIDTH / 10, TEXTURE_HEIGHT / 10, 1);
    Commands::MemoryBarrier(BarrierBit::SHADER_IMAGE_ACCESS);

    graphics_pipeline_.Bind();
    texture_->Bind(0);
    Commands::DrawArrays(0, 3);
  }

  void OnInitialize() override {
    texture_ =
      std::make_unique<Texture>(TextureTarget::TEXTURE_2D, TextureInternalFormat::RGBA32F,
                                TEXTURE_WIDTH, TEXTURE_HEIGHT);
  }

private:
  VertexArray vao_;
  ComputePipeline compute_pipeline_;
  GraphicsPipeline graphics_pipeline_;
  std::unique_ptr<Texture> texture_;
};

int main() {
  ComputeRaytracing application;

  application.Run();

  return 0;
}