#ifndef IMGUI_PLATFORM_H
#define IMGUI_PLATFORM_H

#include "window.h"

namespace Gloom {

class ImGuiPlatform {
public:
  ImGuiPlatform();
  ~ImGuiPlatform() = default;

  void NewFrame();

protected:
  void UpdateMouseData();

private:
  Window window_;
};

} // namespace Gloom

#endif // IMGUI_PLATFORM_H