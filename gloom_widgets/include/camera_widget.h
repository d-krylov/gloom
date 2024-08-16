#ifndef GLOOM_CAMERA_WIDGET_H
#define GLOOM_CAMERA_WIDGET_H

#include "camera.h"

namespace Gloom {

class CameraWidget {
public:
  void OnImGui();
  void OnUpdate();

  [[nodiscard]] const Camera &GetCamera() const { return camera_; }
  [[nodiscard]] Camera &GetCamera() { return camera_; }

private:
  Vector3f position_;
  Vector3f rotation_;
  Camera camera_;
};

} // namespace Gloom

#endif // GLOOM_CAMERA_WIDGET_H