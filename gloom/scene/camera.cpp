#include "gloom/scene/include/camera.h"

namespace Gloom {

Matrix4f Camera::GetLookAtMatrix() const { return glm::lookAt(position_, position_ + front_, up_); }

void Camera::OnResize(uint32_t width, uint32_t height) { aspect_ = float(width) / height; }

void Camera::UpdateVectors() {
  auto x = glm::rotate(glm::mat4(1.0f), glm::radians(rotation_.x), X_);
  auto y = glm::rotate(glm::mat4(1.0f), glm::radians(rotation_.y), Y_);
  auto z = glm::rotate(glm::mat4(1.0f), glm::radians(rotation_.z), Z_);
  auto R = x * y * z;
  front_ = Vector3f(R * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f));
  right_ = Vector3f(R * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
  up_ = Vector3f(R * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
}

void Camera::SetRotation(const Vector3f &rotation) {
  rotation_ = rotation;
  UpdateVectors();
}

} // namespace Gloom