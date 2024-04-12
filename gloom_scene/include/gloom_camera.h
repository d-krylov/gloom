#ifndef GLOOM_CAMERA_H
#define GLOOM_CAMERA_H

#include "gloom_types.h"

namespace Gloom ::Scene {

class Camera {
public:
  Camera();

  Types::Vector3f GetUpDirection() const;
  Types::Vector3f GetRightDirection() const;
  Types::Vector3f GetForwardDirection() const;

  Types::Vector4f GetOrientation() const;

  Types::Matrix4f GetPerspectiveMatrix() const;

private:
  Types::Vector3f position_;
  float fov_{60.0f};
  float near_{0.1f};
  float far_{500.0f};
  float pitch_{0.0f};
  float yaw_{0.0f};
};

} // namespace Gloom::Scene

#endif // GLOOM_CAMERA_H