#include "gloom/application/include/gloom.h"
#include <iostream>

using namespace Gloom;

class Viewer : public Layer {
public:
  void OnImGui() override {
    transform_.OnImGui();
    camera_.OnImGui();
    light_.OnImGui();
  }

  void OnUpdate() override {
    renderer_.Begin();

    camera_.OnUpdate();
    auto &camera = camera_.GetCamera();

    renderer_.SetCamera(camera);
    renderer_.SetLights(light_.GetPointLights());

    renderer_.Draw(model_, transform_.GetTransform());
  }

  void OnAttach() override {
    model_.LoadWavefront(ROOT / "assets" / "sponza1" / "sponza.obj");
    renderer_.Add(model_);
    light_.AddPointLight();
  }

private:
  Renderer renderer_;
  Model model_;
  TransformWidget transform_;
  CameraWidget camera_;
  LightWidget light_;
  Vector3f light_position_;
};

int main() {
  Application application;
  Viewer viewer;
  application.AddLayer(&viewer);
  application.Run();

  return 0;
}