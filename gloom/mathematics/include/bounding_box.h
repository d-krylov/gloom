#ifndef GLOOM_BOUNDONG_BOX_H
#define GLOOM_BOUNDONG_BOX_H

#include "ray.h"

namespace Gloom {

class BoundingBox {
public:
  BoundingBox(const Vector3f &p1, const Vector3f &p2)
    : min_(glm::min(p1, p2)), max_(glm::max(p1, p2)) {}

  BoundingBox(const Vector3f &p) : BoundingBox(p, p) {}

  void Expand(const Vector3f &p);

  [[nodiscard]] Vector3f GetDiameter() const { return max_ - min_; }
  [[nodiscard]] Vector3f GetCenter() const { return (max_ + min_) * 0.5f; }
  [[nodiscard]] bool Intersect(const Ray &ray, float &t0, float &t1) const;

private:
  Vector3f min_;
  Vector3f max_;
};

} // namespace Gloom

#endif // GLOOM_BOUNDONG_BOX_H