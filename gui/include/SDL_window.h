#ifndef SDL_WINDOW_H
#define SDL_WINDOW_H

#include <string_view>

struct SDL_Window;

namespace Gloom {

class SDL_window {
public:
  SDL_window(std::string_view name, uint32_t width, uint32_t height);

  const SDL_Window *GetNativeWindow() const { return native_window_; }

  uint32_t GetWidth() const { return width_; }
  uint32_t GetHeight() const { return height_; }

private:
  uint32_t width_;
  uint32_t height_;
  SDL_Window *native_window_;
};

} // namespace Gloom

#endif // SDL_WINDOW_H