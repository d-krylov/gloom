#include "application.h"

namespace Gloom {

Application::Application(std::string_view name, uint32_t width, uint32_t height)
  : imgui_platform_(name, width, height), imgui_renderer_() {}

Application::~Application() {}

void Application::Run() {}

} // namespace Gloom