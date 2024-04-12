#ifndef WINDOW_H
#define WINDOW_H

#include <cstdint>
#include <string_view>

namespace Gloom {

class Window {
public:
  [[nodiscard]] virtual uint32_t GetWidth() const = 0;
  [[nodiscard]] virtual uint32_t GetHeight() const = 0;
  [[nodiscard]] virtual bool ShouldClose() const = 0;
};

} // namespace Gloom

#endif // WINDOW_H