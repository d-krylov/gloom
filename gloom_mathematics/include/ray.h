#ifndef GLOOM_RAY_H
#define GLOOM_RAY_H

#include "gloom_core/include/core_types.h"

namespace Gloom {

class Ray {
public:
  Ray(const Vector3f &origin, const Vector3f &direction)
    : origin_(origin), direction_(direction) {}

  [[nodiscard]] Vector3f operator()(float t) { return (origin_ + direction_ * t); }

  [[nodiscard]] const Vector3f &GetOrigin() const { return origin_; }
  [[nodiscard]] const Vector3f &GetDirection() const { return direction_; }

private:
  Vector3f origin_;
  Vector3f direction_;
};

} // namespace Gloom

#endif // GLOOM_RAY_H