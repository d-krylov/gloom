#ifndef GLOOM_TRIANGLE_H
#define GLOOM_TRIANGLE_H

#include "ray.h"

namespace Gloom {

class Triangle {
public:
  Triangle(const Vector3f &a, const Vector3f &b, const Vector3f &c);

  [[nodiscard]] bool Intersect(const Ray &ray, float &t) const;

  [[nodiscard]] Vector3f GetCenter() const { return (a_ + b_ + c_) / 3.0f; }

private:
  Vector3f a_;
  Vector3f b_;
  Vector3f c_;
};

} // namespace Gloom

#endif // GLOOM_TRIANGLE_Hs