#ifndef APPLICATION_H
#define APPLICATION_H

#include "imgui_platform.h"
#include "imgui_renderer.h"
#include <string>

namespace Gloom {

class Application {
public:
  Application(std::string_view name, uint32_t width, uint32_t height);

  ~Application();

  void OnInitialize();
  void Run();

  virtual void OnUpdate() {}
  virtual void OnImGui() {}

private:
  ImGuiPlatform imgui_platform_;
  ImGuiRenderer imgui_renderer_;
};

} // namespace Gloom

#endif // APPLICATION_H