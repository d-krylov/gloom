#include "gloom/application/include/gloom.h"

using namespace Gloom;

class Primitives : public Layer {
public:
  Primitives() { Gloom::EnableDebug(); }

  void OnImGui() override { camera_.OnImGui(); }

  void OnUpdate() override {
    renderer_.Begin(camera_.GetActiveCamera());

    std::vector<Matrix4f> boxes;

    std::transform(boxes_.begin(), boxes_.end(), std::back_inserter(boxes),
                   [](auto &x) { return x.GetModelMatrix(); });

    renderer_.DrawBoxes(boxes);
  }

  void OnAttach() override {
    for (int32_t x = -50; x < 50; x += 4) {
      for (int32_t z = -50; z < 50; z += 5) {
        for (int32_t y = -10; y < 10; y += 2) {
          Transform transform{Vector3f(x, y, z), Vector3f(0.0f, 0.0f, 0.0f),
                              Vector3f(1.0f, 1.0f, 1.0f)};
          boxes_.emplace_back(transform);
        }
      }
    }
  }

private:
  std::vector<Transform> boxes_;
  CameraWidget camera_;
  PrimitiveRenderer renderer_;
};

int main() {
  Application application;
  Primitives primitives;

  application.AddLayer(&primitives);
  application.Run();

  return 0;
}