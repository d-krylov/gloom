#include "gloom_mathematics/include/bounding_box.h"

namespace Gloom {

void BoundingBox::Expand(const Vector3f &p) {
  min_ = glm::min(min_, p);
  max_ = glm::max(max_, p);
}

bool BoundingBox::Intersect(const Ray &ray, float &t0, float &t1) const {
  auto t_min = (min_ - ray.GetOrigin()) / ray.GetDirection();
  auto t_max = (max_ - ray.GetOrigin()) / ray.GetDirection();

  auto temp = glm::min(t_min, t_max);

  t_max = glm::max(t_min, t_max);
  t_min = temp;

  return true;
}

} // namespace Gloom