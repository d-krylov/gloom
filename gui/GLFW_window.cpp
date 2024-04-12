// clang-format off
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "GLFW_window.h"
// clang-format on

namespace Gloom {

void GLFWInitialize() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GLFW_window::GLFW_window(std::string_view name, uint32_t width, uint32_t height)
    : width_(width), height_(height) {
  GLFWInitialize();

  native_window_ =
      glfwCreateWindow(width, height, name.data(), nullptr, nullptr);

  glfwMakeContextCurrent(native_window_);

  auto status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

bool GLFW_window::ShouldClose() const {
  return glfwWindowShouldClose(native_window_);
}
void GLFW_window::PollEvents() { glfwPollEvents(); }
void GLFW_window::Update() const { glfwSwapBuffers(native_window_); }

} // namespace Gloom