#ifndef GLOOM_PERSPECTIVE_CAMERA_H
#define GLOOM_PERSPECTIVE_CAMERA_H

#include "camera.h"

namespace Gloom {

class PerspectiveCamera : public Camera {
public:
  PerspectiveCamera();

  Matrix4f GetProjectionMatrix() const override;

public:
  float fov_{60.0f};
};

} // namespace Gloom

#endif // GLOOM_PERSPECTIVE_CAMERA_H