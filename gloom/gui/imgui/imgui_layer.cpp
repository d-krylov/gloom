#include "imgui_layer.h"
#include "gloom/core/include/macros.h"
#include "gloom/gui/include/event.h"
#include "gloom/gui/include/window.h"
#include "imgui.h"

namespace Gloom {

ImGuiKey ToImGuiKey(Key key) {
  switch (key) {
#define KEY(X, Y)                                                                                  \
  case Key::K_##X:                                                                                 \
    return ImGuiKey::ImGuiKey_##Y;
#include "gloom/gui/include/key.def"
  default:
    UNREACHABLE();
    break;
  }
}

// clang-format off
void UpdateKeyModifiers(GLFWwindow* window) {
  auto& io = ImGui::GetIO();
  io.AddKeyEvent(ImGuiMod_Ctrl,  (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) || (glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS));
  io.AddKeyEvent(ImGuiMod_Shift, (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)   == GLFW_PRESS) || (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT)   == GLFW_PRESS));
  io.AddKeyEvent(ImGuiMod_Alt,   (glfwGetKey(window, GLFW_KEY_LEFT_ALT)     == GLFW_PRESS) || (glfwGetKey(window, GLFW_KEY_RIGHT_ALT)     == GLFW_PRESS));
  io.AddKeyEvent(ImGuiMod_Super, (glfwGetKey(window, GLFW_KEY_LEFT_SUPER)   == GLFW_PRESS) || (glfwGetKey(window, GLFW_KEY_RIGHT_SUPER)   == GLFW_PRESS));
}
// clang-format on

bool ImGuiLayer::OnCharEvent(const CharEvent &event) {
  auto &io = ImGui::GetIO();
  io.AddInputCharacter(event.GetCharacter());
  return true;
}

bool ImGuiLayer::OnMouseMoveEvent(const MouseMoveEvent &event) {
  auto &io = ImGui::GetIO();
  io.AddMousePosEvent(event.GetX(), event.GetY());
  return true;
}

bool ImGuiLayer::OnMouseScrollEvent(const MouseScrollEvent &event) {
  auto &io = ImGui::GetIO();
  io.AddMouseWheelEvent(event.GetX(), event.GetY());
  return true;
}

bool ImGuiLayer::OnMouseButtonEvent(const MouseButtonEvent &event) {
  auto &io = ImGui::GetIO();
  UpdateKeyModifiers(window_->GetNativeWindow());
  io.AddMouseButtonEvent(int32_t(event.GetMouseButton()), event.GetAction() == Action::PRESS);
  return true;
}

bool ImGuiLayer::OnKeyEvent(const KeyEvent &event) {
  auto action = event.GetAction();
  if (action != Action::PRESS && action != Action::RELEASE) {
    return true;
  }
  auto &io = ImGui::GetIO();
  auto key = ToImGuiKey(event.GetKey());
  UpdateKeyModifiers(window_->GetNativeWindow());
  io.AddKeyEvent(key, (action == Action::PRESS));
  io.SetKeyEventNativeData(key, uint32_t(event.GetKey()), event.GetScanCode());
  return true;
}

void ImGuiLayer::OnEvent(Event &event) {
  EventDispatcher dispatcher(event);
  dispatcher.Dispatch<MouseMoveEvent>(BIND_FUNCTION(ImGuiLayer::OnMouseMoveEvent));
  dispatcher.Dispatch<MouseButtonEvent>(BIND_FUNCTION(ImGuiLayer::OnMouseButtonEvent));
  dispatcher.Dispatch<MouseScrollEvent>(BIND_FUNCTION(ImGuiLayer::OnMouseScrollEvent));
  dispatcher.Dispatch<CharEvent>(BIND_FUNCTION(ImGuiLayer::OnCharEvent));
  dispatcher.Dispatch<KeyEvent>(BIND_FUNCTION(ImGuiLayer::OnKeyEvent));
}

ImGuiLayer::ImGuiLayer(Window *window) : window_(window) { ImGui::CreateContext(); }

void ImGuiLayer::UpdateMouseData() {
  auto &io = ImGui::GetIO();
  auto &platform_io = ImGui::GetPlatformIO();
  uint32_t mouse_viewport_id = 0;
  Vector2f previous_mouse_position{io.MousePos.x, io.MousePos.y};
}

void ImGuiLayer::NewFrame() {
  auto &io = ImGui::GetIO();

  auto window_size = window_->GetSize();
  auto framebuffer_size = window_->GetFramebufferSize();

  io.DisplaySize = ImVec2((float)window_size.x, (float)window_size.y);

  if (window_size.x > 0 && window_size.y > 0) {
    io.DisplayFramebufferScale = ImVec2((float)framebuffer_size.x / (float)window_size.x,
                                        (float)framebuffer_size.y / (float)window_size.y);
  }

  UpdateMouseData();
  auto imgui_cursor = ImGui::GetMouseCursor();
  window_->SetCursor(imgui_cursor);
}

} // namespace Gloom