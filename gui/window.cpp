// clang-format off
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "window.h"
// clang-format on

namespace Gloom {

void GLFWInitialize() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

Window::Window(std::string_view name, uint32_t w, uint32_t h, Window *share)
  : width_(w), height_(h) {

  GLFWInitialize();

  native_window_ = glfwCreateWindow(w, h, name.data(), nullptr, share->GetNativeWindow());

  glfwMakeContextCurrent(native_window_);

  auto status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

bool Window::ShouldClose() const { return glfwWindowShouldClose(native_window_); }

void Window::PollEvents() { glfwPollEvents(); }
void Window::Update() const { glfwSwapBuffers(native_window_); }

float Window::GetAspectRatio() const {
  Types::Vector2f size(GetSize());
  return size.x / size.y;
}

void Window::Show() { glfwShowWindow(native_window_); }

void Window::SetCursor(int32_t index) {
  glfwSetCursor(native_window_, mouse_cursors_[index] != nullptr
                                  ? mouse_cursors_[index]
                                  : mouse_cursors_[MouseCursor::ARROW]);
}

void Window::SetCursorPosition(const Types::Vector2d &position) {
  glfwSetCursorPos(native_window_, position.x, position.y);
}

Types::Vector2u Window::GetFramebufferSize() const {
  Types::Vector2i size;
  glfwGetFramebufferSize(native_window_, &size.x, &size.y);
  return Types::Vector2u(size);
}

Types::Vector2u Window::GetSize() const {
  Types::Vector2i size;
  glfwGetWindowSize(native_window_, &size.x, &size.y);
  return Types::Vector2u(size);
}

uint32_t Window::GetWidth() const {
  auto size = GetSize();
  return size.x;
}

uint32_t Window::GetHeight() const {
  auto size = GetSize();
  return size.y;
}

Types::Vector2i Window::GetPosition() const {
  Types::Vector2i position;
  glfwGetWindowPos(native_window_, &position.x, &position.y);
  return position;
}

Types::Vector2f Window::GetCursorPosition() const {
  Types::Vector2d position;
  glfwGetCursorPos(native_window_, &position.x, &position.y);
  return Types::Vector2f(position);
}

// clang-format off
void Window::SetCursors() {
  mouse_cursors_[MouseCursor::ARROW] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
  mouse_cursors_[MouseCursor::TEXT_INPUT] = glfwCreateStandardCursor(GLFW_IBEAM_CURSOR);
  mouse_cursors_[MouseCursor::RESIZE_NS] = glfwCreateStandardCursor(GLFW_VRESIZE_CURSOR);
  mouse_cursors_[MouseCursor::RESIZE_EW] = glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR);
  mouse_cursors_[MouseCursor::HAND] = glfwCreateStandardCursor(GLFW_HAND_CURSOR);
  mouse_cursors_[MouseCursor::RESIZE_ALL] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
  mouse_cursors_[MouseCursor::RESIZE_NESW] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
  mouse_cursors_[MouseCursor::RESIZE_NWSE] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
  mouse_cursors_[MouseCursor::NOT_ALLOWED] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
}
// clang-format on

} // namespace Gloom