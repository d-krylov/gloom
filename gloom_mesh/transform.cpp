#include "gloom_mesh/include/transform.h"

namespace Gloom {

Matrix4f Transform::GetModelMatrix() const {
  Matrix4f transform = Matrix4f(1.0f);
  transform = glm::translate(transform, translate_);
  transform = glm::rotate(transform, rotate_.x, X);
  transform = glm::rotate(transform, rotate_.y, Y);
  transform = glm::rotate(transform, rotate_.z, Z);
  transform = glm::scale(transform, scale_);
  return transform;
}

} // namespace Gloom
