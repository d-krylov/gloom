#include "gloom/include/application.h"
#include "easyloggingpp/easylogging++.h"

INITIALIZE_EASYLOGGINGPP

namespace Gloom {

Application::Application(std::string_view name, uint32_t width, uint32_t height)
  : imgui_platform_(name, width, height), imgui_renderer_() {}

void Application::Run() {
  OnInitialize();

  while (imgui_platform_.GetWindow().ShouldClose() == false) {
    imgui_platform_.GetWindow().PollEvents();

    OnUpdate();

    imgui_platform_.NewFrame();
    imgui_renderer_.Begin();

    OnImGui();

    imgui_renderer_.End();
    imgui_platform_.GetWindow().Update();
  }
}

} // namespace Gloom