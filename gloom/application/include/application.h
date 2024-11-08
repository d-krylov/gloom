#ifndef GLOOM_APPLICATION_H
#define GLOOM_APPLICATION_H

#include "gui/imgui/imgui_layer.h"
#include "gui/imgui/imgui_renderer.h"
#include "gui/include/window.h"
#include <string>

namespace Gloom {

class Application {
public:
  Application(std::string_view name = "Application", uint32_t width = 1920, uint32_t height = 1080);

  virtual ~Application() = default;

  [[nodiscard]] static Application &Get();

  void Run();
  void AddLayer(Layer *layer);
  void OnEvent(Event &event);

  [[nodiscard]] Window &GetWindow() { return window_; }

private:
  Window window_;
  ImGuiLayer imgui_layer_;
  ImGuiRenderer imgui_renderer_;
  std::vector<Layer *> layers_;

  static Application *instance_;
};

} // namespace Gloom

#endif // GLOOM_APPLICATION_H