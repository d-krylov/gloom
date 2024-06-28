#ifndef GLOOM_TRIANGLE_H
#define GLOOM_TRIANGLE_H

#include "gloom_mathematics/include/ray.h"

namespace Gloom {

class Triangle {
public:
  Triangle(const Vector3f a, const Vector3f b, const Vector3f c);

  [[nodiscard]] bool Intersect(const Ray &ray, float &t) const;

private:
  Vector3f a_;
  Vector3f b_;
  Vector3f c_;
};

} // namespace Gloom

#endif // GLOOM_TRIANGLE_Hs