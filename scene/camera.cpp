#include "camera.h"

namespace Gloom {

Camera::Camera() { UpdateVectors(); }

Types::Matrix4f Camera::GetPerspectiveMatrix() const {
  return linalg::perspective_matrix(fov_, aspect_, near_, far_);
}

Types::Matrix4f Camera::GetLookAtMatrix() const {
  return linalg::lookat_matrix(position_, position_ + front_, up_);
}

void Camera::UpdateVectors() {
  Types::Vector3f front;
  front.x = linalg::cos(yaw_) * linalg::cos(pitch_);
  front.y = linalg::sin(pitch_);
  front.z = linalg::sin(yaw_) * linalg::cos(pitch_);
  front_ = linalg::normalize(front);
  right_ = linalg::normalize(linalg::cross(front_, world_up_));
  up_ = linalg::normalize(linalg::cross(right_, front_));
}

void Camera::SetPosition(Types::Vector3f position) { position_ = position; }

void Camera::MoveRight(float v) {}

} // namespace Gloom