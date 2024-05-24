#include "camera.h"
#include "imgui_platform.h"
#include "imgui_renderer.h"
#include "window.h"

int main() {

  Gloom::ImGuiPlatform imgui_platform("example", 800, 600);
  Gloom::ImGuiRenderer imgui_renderer;

  Gloom::Types::Vector3f camera_position(0.0f, 0.0f, 0.0f);

  while (imgui_platform.GetWindow().ShouldClose() == false) {
    imgui_platform.GetWindow().PollEvents();

    imgui_platform.NewFrame();
    imgui_renderer.Begin();

    ImGui::Begin("window");

    ImGui::SliderFloat3("position", reinterpret_cast<float *>(&camera_position), -100.0f,
                        100.0f);

    ImGui::End();

    imgui_renderer.End();

    imgui_platform.GetWindow().Update();
  }

  return 0;
}