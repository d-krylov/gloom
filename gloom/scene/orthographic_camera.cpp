#include "scene/include/orthographic_camera.h"

namespace Gloom {

OrthographicCamera::OrthographicCamera() {}

Matrix4f OrthographicCamera::GetProjectionMatrix() const {
  return glm::ortho(left_, right_, bottom_, top_, near_, far_);
}

} // namespace Gloom