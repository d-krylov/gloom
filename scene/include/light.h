#ifndef GLOOM_LIGHT_H
#define GLOOM_LIGHT_H

#include "gloom_core/include/core_types.h"

namespace Gloom {

class Light {
public:
  Vector3f position_;
  Vector3f ambient_;
  Vector3f diffuse_;
  Vector3f specular_;
};

} // namespace Gloom

#endif // GLOOM_LIGHT_H