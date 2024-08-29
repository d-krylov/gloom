#ifndef WINDOW_H
#define WINDOW_H

#include "gloom/core/include/core_types.h"
#include <functional>
#include <string_view>

struct GLFWwindow;
struct GLFWcursor;

namespace Gloom {

class Event;

enum MouseCursor {
  ARROW = 0,
  TEXT_INPUT = 1,
  RESIZE_ALL = 2,
  RESIZE_NS = 3,
  RESIZE_EW = 4,
  RESIZE_NESW = 5,
  RESIZE_NWSE = 6,
  HAND = 7,
  NOT_ALLOWED = 8,
  CROSSHAIR = 9
};

constexpr uint32_t GLFW_CURSOR_COUNT = MouseCursor::CROSSHAIR + 1;

class Window {
public:
  using EventCallbackFunction = std::function<void(Event &)>;

  Window(std::string_view name, uint32_t width, uint32_t height);

  [[nodiscard]] GLFWwindow *GetNativeWindow() const { return native_window_; }
  [[nodiscard]] uint32_t GetWidth() const;
  [[nodiscard]] uint32_t GetHeight() const;
  [[nodiscard]] Vector2u GetSize() const;
  [[nodiscard]] Vector2i GetPosition() const;
  [[nodiscard]] Vector2f GetCursorPosition() const;
  [[nodiscard]] Vector2u GetFramebufferSize() const;
  [[nodiscard]] bool ShouldClose() const;
  [[nodiscard]] float GetAspectRatio() const;

  [[nodiscard]] EventCallbackFunction &GetEventCallback() { return event_callback_; }

  void SetEventCallback(const EventCallbackFunction &event_callback) {
    event_callback_ = event_callback;
  }

  void SetCursorPosition(const Vector2d &position);
  void PollEvents();
  void Update() const;
  void Show();

  void SetCursor(int32_t index);

protected:
  void SetCursors();
  void SetCallbacks();

private:
  GLFWwindow *native_window_;
  GLFWcursor *mouse_cursors_[GLFW_CURSOR_COUNT];
  EventCallbackFunction event_callback_;
};

} // namespace Gloom

#endif // WINDOW_H