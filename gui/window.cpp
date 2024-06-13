// clang-format off
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "window.h"
// clang-format on

namespace Gloom {

void GLFWInitialize() {
  glfwInit();
  // glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

Window::Window(std::string_view name, uint32_t w, uint32_t h) {

  GLFWInitialize();

  native_window_ = glfwCreateWindow(w, h, name.data(), nullptr, nullptr);

  glfwMakeContextCurrent(native_window_);

  auto status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

  SetCursors();
  SetUserPointer();
  SetCallbacks();
}

bool Window::ShouldClose() const { return glfwWindowShouldClose(native_window_); }

void Window::PollEvents() { glfwPollEvents(); }
void Window::Update() const { glfwSwapBuffers(native_window_); }

float Window::GetAspectRatio() const {
  Vector2f size(GetSize());
  return size.x / size.y;
}

void Window::Show() { glfwShowWindow(native_window_); }

void Window::SetCursor(int32_t index) {
  glfwSetCursor(native_window_, mouse_cursors_[index] != nullptr
                                  ? mouse_cursors_[index]
                                  : mouse_cursors_[MouseCursor::ARROW]);
}

void Window::SetCursorPosition(const Vector2d &position) {
  glfwSetCursorPos(native_window_, position.x, position.y);
}

void Window::SetWindowEventHandler(WindowEventHandler *handler) {
  window_event_handler_ = handler;
}

Vector2u Window::GetFramebufferSize() const {
  Vector2i size;
  glfwGetFramebufferSize(native_window_, &size.x, &size.y);
  return Vector2u(size);
}

Vector2u Window::GetSize() const {
  Vector2i size;
  glfwGetWindowSize(native_window_, &size.x, &size.y);
  return Vector2u(size);
}

uint32_t Window::GetWidth() const {
  auto size = GetSize();
  return size.x;
}

uint32_t Window::GetHeight() const {
  auto size = GetSize();
  return size.y;
}

Vector2i Window::GetPosition() const {
  Vector2i position;
  glfwGetWindowPos(native_window_, &position.x, &position.y);
  return position;
}

Vector2f Window::GetCursorPosition() const {
  Vector2d position;
  glfwGetCursorPos(native_window_, &position.x, &position.y);
  return Vector2f(position);
}

// clang-format off
void Window::SetCursors() {
  mouse_cursors_[MouseCursor::ARROW] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
  mouse_cursors_[MouseCursor::TEXT_INPUT] = glfwCreateStandardCursor(GLFW_IBEAM_CURSOR);
  mouse_cursors_[MouseCursor::RESIZE_NS] = glfwCreateStandardCursor(GLFW_VRESIZE_CURSOR);
  mouse_cursors_[MouseCursor::RESIZE_EW] = glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR);
  mouse_cursors_[MouseCursor::HAND] = glfwCreateStandardCursor(GLFW_HAND_CURSOR);
#if GLFW_HAS_NEW_CURSORS
  mouse_cursors_[MouseCursor::RESIZE_ALL] = glfwCreateStandardCursor(GLFW_RESIZE_ALL_CURSOR);
  mouse_cursors_[MouseCursor::RESIZE_NESW] = glfwCreateStandardCursor(GLFW_RESIZE_NESW_CURSOR);
  mouse_cursors_[MouseCursor::RESIZE_NWSE] = glfwCreateStandardCursor(GLFW_RESIZE_NWSE_CURSOR);
  mouse_cursors_[MouseCursor::NOT_ALLOWED] = glfwCreateStandardCursor(GLFW_NOT_ALLOWED_CURSOR);
#else
  mouse_cursors_[MouseCursor::RESIZE_ALL] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
  mouse_cursors_[MouseCursor::RESIZE_NESW] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
  mouse_cursors_[MouseCursor::RESIZE_NWSE] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
  mouse_cursors_[MouseCursor::NOT_ALLOWED] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
#endif
}
// clang-format on

} // namespace Gloom