#ifndef IMGUI_PLATFORM_H
#define IMGUI_PLATFORM_H

#include "window.h"

namespace Gloom {

class ImGuiPlatform : public WindowEventHandler {
public:
  ImGuiPlatform(std::string_view name, uint32_t width, uint32_t height);
  ~ImGuiPlatform() = default;

  void NewFrame();

  [[nodiscard]] Window &GetWindow() { return window_; }
  [[nodiscard]] const Window &GetWindow() const { return window_; }

  void OnWindowFocus(int focused) override;
  void OnWindowSize(int, int) override;
  void OnWindowPos(int, int) override;
  void OnMouseButton(int button, int action, int m) override;
  void OnScroll(double xoffset, double yoffset) override;
  void OnKey(int keycode, int scancode, int action, int m) override;
  void OnCursorPos(double x, double y) override;
  void OnCursorEnter(int entered) override;
  void OnChar(unsigned int c) override;

protected:
  void UpdateMouseData();

private:
  Window window_;
};

} // namespace Gloom

#endif // IMGUI_PLATFORM_H