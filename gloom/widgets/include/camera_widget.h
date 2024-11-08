#ifndef GLOOM_CAMERA_WIDGET_H
#define GLOOM_CAMERA_WIDGET_H

#include "scene/include/orthographic_camera.h"
#include "scene/include/perspective_camera.h"

namespace Gloom {

class CameraWidget {
public:
  void OnImGui();

  [[nodiscard]] const PerspectiveCamera &GetPerspectiveCamera() const { return perspective_; }
  [[nodiscard]] const OrthographicCamera &GetOrthographicCamera() const { return orthographic_; }
  [[nodiscard]] const Camera &GetActiveCamera() const;

  void OnResize(uint32_t width, uint32_t height);

private:
  void DrawPerspective();
  void DrawOrthographic();

private:
  Vector3f position_;
  Vector3f rotation_;
  PerspectiveCamera perspective_;
  OrthographicCamera orthographic_;
  uint32_t selected_{0};
};

} // namespace Gloom

#endif // GLOOM_CAMERA_WIDGET_H