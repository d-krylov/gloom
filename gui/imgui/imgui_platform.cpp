#include "imgui_platform.h"
#include "gui.h"
#include <GLFW/glfw3.h>

namespace Gloom {

void ImGuiPlatform::OnWindowFocus(int focused) {
  auto &io = ImGui::GetIO();
  io.AddFocusEvent(focused != 0);
}

void ImGuiPlatform::OnWindowSize(int, int) {}

void ImGuiPlatform::OnWindowPos(int, int) {}

// clang-format off
void UpdateKeyModifiers(GLFWwindow* window) {
  auto& io = ImGui::GetIO();
  io.AddKeyEvent(ImGuiMod_Ctrl,  (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) || (glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS));
  io.AddKeyEvent(ImGuiMod_Shift, (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)   == GLFW_PRESS) || (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT)   == GLFW_PRESS));
  io.AddKeyEvent(ImGuiMod_Alt,   (glfwGetKey(window, GLFW_KEY_LEFT_ALT)     == GLFW_PRESS) || (glfwGetKey(window, GLFW_KEY_RIGHT_ALT)     == GLFW_PRESS));
  io.AddKeyEvent(ImGuiMod_Super, (glfwGetKey(window, GLFW_KEY_LEFT_SUPER)   == GLFW_PRESS) || (glfwGetKey(window, GLFW_KEY_RIGHT_SUPER)   == GLFW_PRESS));
}
// clang-format on

void ImGuiPlatform::OnMouseButton(int button, int action, int m) {
  UpdateKeyModifiers(window_.GetNativeWindow());
  auto &io = ImGui::GetIO();
  if (button >= 0 && button < ImGuiMouseButton_COUNT) {
    io.AddMouseButtonEvent(button, action == GLFW_PRESS);
  }
}

void ImGuiPlatform::OnScroll(double xoffset, double yoffset) {
  auto &io = ImGui::GetIO();
  io.AddMouseWheelEvent((float)xoffset, (float)yoffset);
}

void ImGuiPlatform::OnKey(int keycode, int scancode, int action, int m) {}

void ImGuiPlatform::OnCursorPos(double x, double y) {
  auto &io = ImGui::GetIO();
  io.AddMousePosEvent((float)x, (float)y);
}

void ImGuiPlatform::OnCursorEnter(int entered) { ImGuiIO &io = ImGui::GetIO(); }

void ImGuiPlatform::OnChar(unsigned int c) {
  auto &io = ImGui::GetIO();
  io.AddInputCharacter(c);
}

ImGuiPlatform::ImGuiPlatform(std::string_view name, uint32_t width, uint32_t height)
  : window_(name, width, height) {
  ImGui::CreateContext();
  auto &io = ImGui::GetIO();
  window_.SetWindowEventHandler(this);
}

void ImGuiPlatform::UpdateMouseData() {
  auto &io = ImGui::GetIO();
  auto &platform_io = ImGui::GetPlatformIO();
  uint32_t mouse_viewport_id = 0;
  Types::Vector2f previous_mouse_position{io.MousePos.x, io.MousePos.y};
}

void ImGuiPlatform::NewFrame() {
  auto &io = ImGui::GetIO();

  auto window_size = window_.GetSize();
  auto framebuffer_size = window_.GetFramebufferSize();

  io.DisplaySize = ImVec2((float)window_size.x, (float)window_size.y);

  if (window_size.x > 0 && window_size.y > 0) {
    io.DisplayFramebufferScale = ImVec2((float)framebuffer_size.x / (float)window_size.x,
                                        (float)framebuffer_size.y / (float)window_size.y);
  }

  UpdateMouseData();
  auto imgui_cursor = ImGui::GetMouseCursor();
  window_.SetCursor(imgui_cursor);
}

} // namespace Gloom