#include "gloom_camera.h"

namespace Gloom ::Scene {

Camera::Camera() {}

Types::Vector3f Camera::GetUpDirection() const {}

Types::Vector3f Camera::GetRightDirection() const {}

Types::Vector3f Camera::GetForwardDirection() const {}

Types::Vector4f Camera::GetOrientation() const {}

Types::Matrix4f Camera::GetPerspectiveMatrix() const {
  return linalg::perspective_matrix(3.1415926f * fov_ / 180.0f, 4.0f / 3.0f,
                                    near_, far_, linalg::neg_z,
                                    linalg::zero_to_one);
}

} // namespace Gloom::Scene