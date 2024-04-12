#include "GLFW_window.h"
#include <GLFW/glfw3.h>

namespace Gloom {

void KeyCallback(GLFWwindow *wnd, int key, int scancode, int action, int mod) {
  switch (action) {
  case GLFW_PRESS:

  case GLFW_RELEASE:

  case GLFW_REPEAT:

  default:
    break;
  }
}

void WindowSizeCallback(GLFWwindow *wnd, int width, int height) {}

void WindowCloseCallback(GLFWwindow *wnd) {}

void CursorPositionCallback(GLFWwindow *wnd, double xpos, double ypos) {}

void MouseButtonCallback(GLFWwindow *wnd, int button, int action, int mods) {}

void WindowRefreshCallback(GLFWwindow *wnd) {}

void ScrollCallback(GLFWwindow *wnd, double xoffset, double yoffset) {}

void CursorEnterCallback(GLFWwindow *wnd, int entered) {}

void GLFW_window::SetUserPointer() {
  // glfwSetWindowUserPointer(native_window_, game);
}

void GLFW_window::SetCallbacks() {
  glfwSetKeyCallback(native_window_, KeyCallback);
  glfwSetWindowSizeCallback(native_window_, WindowSizeCallback);
  glfwSetWindowCloseCallback(native_window_, WindowCloseCallback);
  glfwSetWindowRefreshCallback(native_window_, WindowRefreshCallback);
  glfwSetCursorPosCallback(native_window_, CursorPositionCallback);
  glfwSetCursorEnterCallback(native_window_, CursorEnterCallback);
  glfwSetMouseButtonCallback(native_window_, MouseButtonCallback);
  glfwSetScrollCallback(native_window_, ScrollCallback);
}

} // namespace Gloom