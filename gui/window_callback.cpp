#include "window.h"
#include <GLFW/glfw3.h>

namespace Gloom {

WindowEventHandler *GetEventHandler(GLFWwindow *native) {
  Window *window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(native));
  auto handler = window->GetEventHandler();
  return handler;
}

void KeyCallback(GLFWwindow *wnd, int key, int scancode, int action, int mod) {
  auto handler = GetEventHandler(wnd);
  if (handler) {
    handler->OnKey(key, scancode, action, mod);
  }
}

void WindowSizeCallback(GLFWwindow *wnd, int width, int height) {}

void WindowCloseCallback(GLFWwindow *wnd) {}

void CursorPositionCallback(GLFWwindow *wnd, double xpos, double ypos) {
  auto handler = GetEventHandler(wnd);
  if (handler) {
    handler->OnCursorPos(xpos, ypos);
  }
}

void MouseButtonCallback(GLFWwindow *wnd, int button, int action, int mods) {
  auto handler = GetEventHandler(wnd);
  if (handler) {
    handler->OnMouseButton(button, action, mods);
  }
}

void WindowRefreshCallback(GLFWwindow *wnd) {}

void ScrollCallback(GLFWwindow *wnd, double xoffset, double yoffset) {
  auto handler = GetEventHandler(wnd);
  if (handler) {
    handler->OnScroll(xoffset, yoffset);
  }
}

void CursorEnterCallback(GLFWwindow *wnd, int entered) {}

void WindowFocusCallback(GLFWwindow *window, int focused) {}

void MonitorCallback(GLFWmonitor *, int) {}

void CharCallback(GLFWwindow *window, unsigned int c) {
  auto handler = GetEventHandler(window);
  if (handler) {
    handler->OnChar(c);
  }
}

void WindowPosCallback(GLFWwindow *window, int, int) {}

void Window::SetUserPointer() { glfwSetWindowUserPointer(native_window_, this); }

void Window::SetCallbacks() {
  glfwSetWindowPosCallback(native_window_, WindowPosCallback);
  glfwSetWindowFocusCallback(native_window_, WindowFocusCallback);
  glfwSetKeyCallback(native_window_, KeyCallback);
  glfwSetWindowSizeCallback(native_window_, WindowSizeCallback);
  glfwSetWindowCloseCallback(native_window_, WindowCloseCallback);
  glfwSetWindowRefreshCallback(native_window_, WindowRefreshCallback);
  glfwSetCursorPosCallback(native_window_, CursorPositionCallback);
  glfwSetCursorEnterCallback(native_window_, CursorEnterCallback);
  glfwSetMouseButtonCallback(native_window_, MouseButtonCallback);
  glfwSetScrollCallback(native_window_, ScrollCallback);
  glfwSetCharCallback(native_window_, CharCallback);
  glfwSetMonitorCallback(MonitorCallback);
}

} // namespace Gloom