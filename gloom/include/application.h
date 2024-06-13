#ifndef GLOOM_APPLICATION_H
#define GLOOM_APPLICATION_H

#include "imgui_platform.h"
#include "imgui_renderer.h"
#include <string>

namespace Gloom {

class Application {
public:
  Application(std::string_view name = "Application", uint32_t width = 1920,
              uint32_t height = 1080);

  virtual ~Application() = default;

  void Run();

  virtual void OnInitialize() {}
  virtual void OnUpdate() {}
  virtual void OnImGui() {}

private:
  ImGuiPlatform imgui_platform_;
  ImGuiRenderer imgui_renderer_;
};

} // namespace Gloom

#endif // GLOOM_APPLICATION_H