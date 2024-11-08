#include "mathematics/include/triangle.h"

namespace Gloom {

Triangle::Triangle(const Vector3f &a, const Vector3f &b, const Vector3f &c) : a_(a), b_(b), c_(c) {}

bool Triangle::Intersect(const Ray &ray, float &t) const {
  Vector3f edge_1(b_ - a_);
  Vector3f edge_2(c_ - a_);

  constexpr float epsilon = 0.000001f;

  auto P = glm::cross(ray.Direction(), edge_2);
  auto D = glm::dot(edge_1, P);

  if ((D > -epsilon) && (D < epsilon)) {
    return false;
  }

  auto inverted_D = 1.0f / D;
  auto T = ray.Origin() - a_;
  auto u = glm::dot(T, P) * inverted_D;

  if ((u < 0.0f) || (u > 1.0f)) {
    return 0;
  }

  auto Q = glm::cross(T, edge_1);
  auto v = glm::dot(ray.Direction(), Q) * inverted_D;

  if (v < 0.0f || u + v > 1.0f) {
    return 0;
  }

  t = glm::dot(edge_2, Q) * inverted_D;

  return true;
}

} // namespace Gloom