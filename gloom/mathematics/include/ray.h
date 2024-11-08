#ifndef GLOOM_RAY_H
#define GLOOM_RAY_H

#include "core/include/core_types.h"

namespace Gloom {

class Ray {
public:
  Ray(const Vector3f &origin, const Vector3f &direction) : origin_(origin), direction_(direction) {}

  [[nodiscard]] Vector3f operator()(float t) const { return (origin_ + direction_ * t); }

  [[nodiscard]] const Vector3f &Origin() const { return origin_; }
  [[nodiscard]] const Vector3f &Direction() const { return direction_; }

private:
  Vector3f origin_;
  Vector3f direction_;
};

} // namespace Gloom

#endif // GLOOM_RAY_H