#include "gloom/scene/include/perspective_camera.h"

namespace Gloom {

PerspectiveCamera::PerspectiveCamera() { UpdateVectors(); }

Matrix4f PerspectiveCamera::GetProjectionMatrix() const {
  return glm::perspective(glm::radians(fov_), aspect_, near_, far_);
}

} // namespace Gloom