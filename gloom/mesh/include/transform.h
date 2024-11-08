#ifndef GLOOM_TRANSFORM_H
#define GLOOM_TRANSFORM_H

#include "core/include/core_types.h"

namespace Gloom {

class Transform {
public:
  [[nodiscard]] Matrix4f GetModelMatrix() const;

public:
  Vector3f translate_{0.0f};
  Vector3f rotate_{0.0f};
  Vector3f scale_{1.0f};
};

} // namespace Gloom

#endif // GLOOM_TRANSFORM_H