#ifndef GLOOM_CAMERA_H
#define GLOOM_CAMERA_H

#include "core/include/core_types.h"

namespace Gloom {

class Camera {
public:
  [[nodiscard]] Matrix4f GetLookAtMatrix() const;
  [[nodiscard]] const Vector3f &GetPosition() const { return position_; }
  [[nodiscard]] const Vector3f &GetRotation() const { return rotation_; }

  [[nodiscard]] float GetNear() const { return near_; }
  [[nodiscard]] float GetFar() const { return far_; }

  void SetNear(float near) { near_ = near; }
  void SetFar(float far) { far_ = far; }
  void SetPosition(const Vector3f &position) { position_ = position; }
  void SetRotation(const Vector3f &rotation);

  void OnResize(uint32_t width, uint32_t height);

  [[nodiscard]] virtual Matrix4f GetProjectionMatrix() const = 0;

protected:
  void UpdateVectors();

protected:
  Vector3f position_{0.0f, 0.0f, 0.0f};
  Vector3f front_{0.0f, 0.0f, -1.0f};
  Vector3f right_;
  Vector3f up_;
  Vector3f rotation_{0.0f, 0.0f, 0.0f};
  float near_{0.1f};
  float far_{10000.0f};
  float aspect_{1.0f};
};

} // namespace Gloom

#endif // GLOOM_CAMERA_H