#ifndef GLOOM_CAMERA_H
#define GLOOM_CAMERA_H

#include "graphics_types.h"

namespace Gloom ::Scene {

class Camera {
public:
  Camera();

  Types::Vector3f GetUpDirection() const { return up_; }
  Types::Vector3f GetRightDirection() const { return right_; }
  Types::Vector3f GetFrontDirection() const { return front_; }

  Types::Matrix4f GetPerspectiveMatrix() const;
  Types::Matrix4f GetLookAtMatrix() const;

  void MoveUp();

protected:
  void UpdateVectors();

private:
  Types::Vector3f position_{0.0f, 0.0f, 0.0f};
  Types::Vector3f front_{0.0f, 0.0f, -1.0f};
  Types::Vector3f right_;
  Types::Vector3f up_;
  Types::Vector3f world_up_{Types::Y};
  float fov_{Types::PI / 3.0f};
  float near_{0.1f};
  float far_{500.0f};
  float aspect_{1.0f};
  float pitch_{0.0f};
  float yaw_{0.0f};
  float speed_{0.5f};
};

} // namespace Gloom::Scene

#endif // GLOOM_CAMERA_H