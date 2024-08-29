#ifndef GLOOM_BVH_H
#define GLOOM_BVH_H

#include "bounding_box.h"

namespace Gloom {

class BVHNode {
public:
  [[nodiscard]] bool IsLeaf() const { return primitive_count_ > 0; }

private:
  uint32_t right_offset_;
  uint32_t primitive_start_;
  uint32_t primitive_count_;
  BoundingBox bounding_box_;
};

class BVH {
public:
private:
};

} // namespace Gloom

#endif // GLOOM_BVH_H