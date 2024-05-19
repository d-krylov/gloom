#include "window.h"
#include <GLFW/glfw3.h>

namespace Gloom {

void KeyCallback(GLFWwindow *wnd, int key, int scancode, int action, int mod) {}

void WindowSizeCallback(GLFWwindow *wnd, int width, int height) {}

void WindowCloseCallback(GLFWwindow *wnd) {}

void CursorPositionCallback(GLFWwindow *wnd, double xpos, double ypos) {}

void MouseButtonCallback(GLFWwindow *wnd, int button, int action, int mods) {}

void WindowRefreshCallback(GLFWwindow *wnd) {}

void ScrollCallback(GLFWwindow *wnd, double xoffset, double yoffset) {}

void CursorEnterCallback(GLFWwindow *wnd, int entered) {}

void WindowFocusCallback(GLFWwindow *window, int focused) {}

void MonitorCallback(GLFWmonitor *, int) {}

void CharCallback(GLFWwindow *window, unsigned int c) {}

void WindowPosCallback(GLFWwindow *window, int, int) {}

void Window::SetUserPointer() {
  // glfwSetWindowUserPointer(native_window_, game);
}

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