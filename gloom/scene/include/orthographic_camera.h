#ifndef GLOOM_ORTHOGRAPHIC_CAMERA_H
#define GLOOM_ORTHOGRAPHIC_CAMERA_H

#include "camera.h"

namespace Gloom {

class OrthographicCamera : public Camera {
public:
  OrthographicCamera();

  Matrix4f GetProjectionMatrix() const override;

public:
  float left_;
  float right_;
  float bottom_;
  float top_;
};

} // namespace Gloom

#endif // GLOOM_ORTHOGRAPHIC_CAMERA_H