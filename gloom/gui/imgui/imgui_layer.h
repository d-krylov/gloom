#ifndef GLOOM_IMGUI_LAYER_H
#define GLOOM_IMGUI_LAYER_H

#include "application/include/layer.h"

namespace Gloom {

class Window;
class Event;
class KeyEvent;
class MouseButtonEvent;
class MouseScrollEvent;
class MouseMoveEvent;
class CharEvent;

class ImGuiLayer : public Layer {
public:
  ImGuiLayer(Window *window);

  ~ImGuiLayer() = default;

  void OnEvent(Event &event) override;

  void NewFrame();

protected:
  void UpdateMouseData();

  bool OnKeyEvent(const KeyEvent &event);
  bool OnMouseButtonEvent(const MouseButtonEvent &event);
  bool OnMouseScrollEvent(const MouseScrollEvent &event);
  bool OnMouseMoveEvent(const MouseMoveEvent &event);
  bool OnCharEvent(const CharEvent &event);

private:
  Window *window_;
};

} // namespace Gloom

#endif // GLOOM_IMGUI_LAYER_H