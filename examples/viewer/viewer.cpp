#include "application/include/gloom.h"
#include <iostream>

using namespace Gloom;

class Viewer : public Layer {
public:
  Viewer()
    : renderer_(Application::Get().GetWindow().GetWidth(),
                Application::Get().GetWindow().GetHeight()) {}

  void OnImGui() override {
    transform_.OnImGui();
    camera_.OnImGui();
    light_.OnImGui();
  }

  void OnEvent(Event &event) {
    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<WindowResizeEvent>(BIND_FUNCTION(Viewer::OnWindowResizeEvent));
  }

  bool OnWindowResizeEvent(const WindowResizeEvent &event) {
    renderer_.OnWindowSize(event.GetWidth(), event.GetHeight());
    camera_.OnResize(event.GetWidth(), event.GetHeight());
    return true;
  }

  void OnUpdate() override {
    renderer_.Begin();

    auto &camera = camera_.GetActiveCamera();

    renderer_.DrawWithPasses(model_, transform_.GetTransform(), light_.GetPointLights().front(),
                             camera);
  }

  void OnAttach() override {
    model_ = Model(ROOT / "assets" / "sponza1" / "sponza.obj");
    renderer_.Add(model_);
    light_.AddPointLight();
  }

private:
  ModelRenderer renderer_;
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