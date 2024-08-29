#ifndef GLOOM_LAYER_H
#define GLOOM_LAYER_H

#include "gloom/gui/include/event.h"

namespace Gloom {

class Layer {
public:
  virtual ~Layer() = default;

  virtual void OnImGui() {}
  virtual void OnUpdate() {}
  virtual void OnAttach() {}
  virtual void OnEvent(Event &event) {}
};

} // namespace Gloom

#endif // GLOOM_LAYER_H