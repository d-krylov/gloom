#include "imgui_renderer.h"
#include "window.h"

int main() {
  Gloom::Window window("hello", 800, 600);

  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();

  // io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

  ImGui_ImplGlfw_InitForOpenGL(window.GetNativeWindow(), true);
  // ImGui_ImplOpenGL3_Init("#version 410");

  Gloom::ImGuiRenderer renderer;

  while (window.ShouldClose() == false) {
    window.PollEvents();

    renderer.Begin();

    ImGui::Begin("window");

    ImGui::End();

    renderer.End();

    window.Update();
  }

  return 0;
}