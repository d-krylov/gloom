#ifndef GLOOM_CAMERA_H
#define GLOOM_CAMERA_H

#include "gloom_core/include/core_types.h"

namespace Gloom {

class Camera {
public:
  Camera();

  [[nodiscard]] const Vector3f &GetUpDirection() const { return up_; }
  [[nodiscard]] const Vector3f &GetRightDirection() const { return right_; }
  [[nodiscard]] const Vector3f &GetFrontDirection() const { return front_; }
  [[nodiscard]] const Vector3f &GetPosition() { return position_; }

  [[nodiscard]] Matrix4f GetPerspectiveMatrix() const;
  [[nodiscard]] Matrix4f GetLookAtMatrix() const;

  void MoveUp(float v);
  void MoveRight(float v);

  void SetPosition(const Vector3f &position);
  void SetAspect(float aspect);

protected:
  void UpdateVectors();

private:
  Vector3f position_{0.0f, 0.0f, 0.0f};
  Vector3f front_{0.0f, 0.0f, -1.0f};
  Vector3f right_;
  Vector3f up_;
  Vector3f world_up_{Y};
  float fov_{PI / 3.0f};
  float near_{0.1f};
  float far_{1000.0f};
  float aspect_{1.7f};
  float pitch_{0.0f};
  float yaw_{-PI / 2.0f};
  float speed_{0.5f};
};

} // namespace Gloom

#endif // GLOOM_CAMERA_H