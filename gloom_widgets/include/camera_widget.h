#ifndef GLOOM_CAMERA_WIDGET_H
#define GLOOM_CAMERA_WIDGET_H

#include "camera.h"

namespace Gloom {

class CameraWidget {
public:
  CameraWidget();

  void OnImGui();

  [[nodiscard]] const Camera &GetCamera() const { return camera_; }
  [[nodiscard]] Camera &GetCamera() { return camera_; }

private:
  Camera camera_;
};

} // namespace Gloom

#endif // GLOOM_CAMERA_WIDGET_H