#ifndef GLOOM_TRANSFORM_WIDGET_H
#define GLOOM_TRANSFORM_WIDGET_H

#include "gloom/mesh/include/transform.h"

namespace Gloom {

class TransformWidget {
public:
  void OnImGui();

  const Transform &GetTransform() const { return transform_; }

private:
  Transform transform_;
};

} // namespace Gloom

#endif // GLOOM_TRANSFORM_WIDGET_H