#ifndef GLOOM_CAMERA_H
#define GLOOM_CAMERA_H

#include "core_types.h"

namespace Gloom {

class Camera {
public:
  Camera();

  [[nodiscard]] const Types::Vector3f &GetUpDirection() const { return up_; }
  [[nodiscard]] const Types::Vector3f &GetRightDirection() const { return right_; }
  [[nodiscard]] const Types::Vector3f &GetFrontDirection() const { return front_; }

  [[nodiscard]] Types::Matrix4f GetPerspectiveMatrix() const;
  [[nodiscard]] Types::Matrix4f GetLookAtMatrix() const;

  void MoveUp(float v);
  void MoveRight(float v);

  void SetPosition(Types::Vector3f position);

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
  float yaw_{-Types::PI / 2.0f};
  float speed_{0.5f};
};

} // namespace Gloom

#endif // GLOOM_CAMERA_H