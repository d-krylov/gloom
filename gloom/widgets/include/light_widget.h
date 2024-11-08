#ifndef GLOOM_LIGHT_WIDGET_H
#define GLOOM_LIGHT_WIDGET_H

#include "scene/include/light.h"
#include <vector>

namespace Gloom {

class LightWidget {
public:
  void OnImGui();

  void AddPointLight() { point_lights_.emplace_back(); }

  [[nodiscard]] const std::vector<PointLight> &GetPointLights() const { return point_lights_; }

private:
  DirectionalLight directional_light_;
  std::vector<PointLight> point_lights_;
};

} // namespace Gloom

#endif // GLOOM_LIGHT_WIDGET_H