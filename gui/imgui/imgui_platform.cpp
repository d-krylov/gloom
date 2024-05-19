#include "imgui_platform.h"
#include "gui.h"
#include <GLFW/glfw3.h>

namespace Gloom {

void OnWindowFocus(GLFWwindow *window, int focused) {
  ImGuiIO &io = ImGui::GetIO();
  io.AddFocusEvent(focused != 0);
}

void OnWindowSize(GLFWwindow *window, int, int) {
  auto *viewport = ImGui::FindViewportByPlatformHandle(window);
  if (viewport != nullptr) {
    viewport->PlatformRequestResize = true;
  }
}

void OnWindowPos(GLFWwindow *window, int, int) {}

// clang-format off
void UpdateKeyModifiers(GLFWwindow* window) {
  ImGuiIO& io = ImGui::GetIO();
  io.AddKeyEvent(ImGuiMod_Ctrl,  (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) || (glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS));
  io.AddKeyEvent(ImGuiMod_Shift, (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)   == GLFW_PRESS) || (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT)   == GLFW_PRESS));
  io.AddKeyEvent(ImGuiMod_Alt,   (glfwGetKey(window, GLFW_KEY_LEFT_ALT)     == GLFW_PRESS) || (glfwGetKey(window, GLFW_KEY_RIGHT_ALT)     == GLFW_PRESS));
  io.AddKeyEvent(ImGuiMod_Super, (glfwGetKey(window, GLFW_KEY_LEFT_SUPER)   == GLFW_PRESS) || (glfwGetKey(window, GLFW_KEY_RIGHT_SUPER)   == GLFW_PRESS));
}
// clang-format on

void OnMouseButton(GLFWwindow *window, int button, int action, int m) {
  UpdateKeyModifiers(window);
  auto &io = ImGui::GetIO();
  if (button >= 0 && button < ImGuiMouseButton_COUNT) {
    io.AddMouseButtonEvent(button, action == GLFW_PRESS);
  }
}

void OnScroll(GLFWwindow *window, double xoffset, double yoffset) {
  auto &io = ImGui::GetIO();
  io.AddMouseWheelEvent((float)xoffset, (float)yoffset);
}

void OnKey(GLFWwindow *window, int keycode, int scancode, int action, int m) {}

void OnCursorPos(GLFWwindow *window, double x, double y) {
  int window_x, window_y;
  auto &io = ImGui::GetIO();
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    glfwGetWindowPos(window, &window_x, &window_y);
    x += window_x;
    y += window_y;
  }
  io.AddMousePosEvent((float)x, (float)y);
}

void OnCursorEnter(GLFWwindow *window, int entered) { ImGuiIO &io = ImGui::GetIO(); }

void OnChar(GLFWwindow *window, unsigned int c) {
  auto &io = ImGui::GetIO();
  io.AddInputCharacter(c);
}

ImGuiPlatform::ImGuiPlatform() {
  ImGui::CreateContext();
  auto &io = ImGui::GetIO();
}

void ImGuiPlatform::UpdateMouseData() {
  auto &io = ImGui::GetIO();
  auto &platform_io = ImGui::GetPlatformIO();
  uint32_t mouse_viewport_id = 0;
  Types::Vector2f previous_mouse_position{io.MousePos.x, io.MousePos.y};
}

void ImGuiPlatform::NewFrame() {
  auto &io = ImGui::GetIO();

  Types::Vector2i size(window_.GetSize());
  Types::Vector2f fb_size(window_.GetFramebufferSize());

  io.DisplaySize = ImVec2(float(size.x), float(size.y));

  if (size.x > 0 && size.y > 0) {
    io.DisplayFramebufferScale = ImVec2(fb_size.x / float(size.x), fb_size.y / float(size.y));
  }

  UpdateMouseData();
  auto imgui_cursor = ImGui::GetMouseCursor();
  window_.SetCursor(imgui_cursor);
}

} // namespace Gloom