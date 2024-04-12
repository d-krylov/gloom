#ifndef GLFW_WINDOW_H
#define GLFW_WINDOW_H

#include "window.h"

struct GLFWwindow;

namespace Gloom {

class GLFW_window : public Window {
public:
  GLFW_window(std::string_view name, uint32_t width, uint32_t height);

  GLFWwindow *GetNativeWindow() { return native_window_; }

  uint32_t GetWidth() const override { return width_; }
  uint32_t GetHeight() const override { return height_; }
  bool ShouldClose() const override;

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