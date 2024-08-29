#ifndef GLOOM_LIGHT_H
#define GLOOM_LIGHT_H

#include "gloom/core/include/core_types.h"

namespace Gloom {

class PointLight {
public:
  Vector3f attenuation_{0.0f, 0.0f, 1.0f};
  Vector3f position_{0.0f, 0.0f, 0.0f};
  Vector3f color_{0.0f, 0.0f, 0.0f};
};

class DirectionalLight {
public:
  Vector3f direction_{0.0f, 0.0f, 0.0f};
  Vector3f color_{0.0f, 0.0f, 0.0f};
};

} // namespace Gloom

#endif // GLOOM_LIGHT_H