#ifndef GLFW_WINDOW_H
#define GLFW_WINDOW_H

#include <string_view>

struct GLFWwindow;

namespace Gloom {

class GLFW_window {
public:
  GLFW_window(std::string_view name, uint32_t width, uint32_t height);

  const GLFWwindow *GetNativeWindow() const { return native_window_; }

  uint32_t GetWidth() const { return width_; }
  uint32_t GetHeight() const { return height_; }
  bool ShouldClose() const;
  float GetAspectRatio() const;

  void SetCallbacks();
  void SetUserPointer();

  void PollEvents();
  void Update() const;

private:
  uint32_t width_;
  uint32_t height_;
  GLFWwindow *native_window_;
};

} // namespace Gloom

#endif // GLFW_WINDOW_H