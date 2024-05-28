#ifndef WINDOW_EVENT_HANDLER_H
#define WINDOW_EVENT_HANDLER_H

namespace Gloom {

class WindowEventHandler {
public:
  virtual void OnWindowFocus(int focused){};
  virtual void OnWindowSize(int, int){};
  virtual void OnWindowPos(int, int){};
  virtual void OnMouseButton(int button, int action, int m){};
  virtual void OnScroll(double xoffset, double yoffset){};
  virtual void OnKey(int keycode, int scancode, int action, int m){};
  virtual void OnCursorPos(double x, double y){};
  virtual void OnCursorEnter(int entered){};
  virtual void OnChar(unsigned int c){};
};

} // namespace Gloom

#endif // WINDOW_EVENT_HANDLER_H