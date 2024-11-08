#include "widgets/include/transform_widget.h"
#include "imgui.h"

namespace Gloom {

void TransformWidget::OnImGui() {
  ImGui::Begin("Transform");
  ImGui::InputFloat3("Translate", glm::value_ptr(transform_.translate_));
  ImGui::SliderFloat3("Rotate   ", glm::value_ptr(transform_.rotate_), 0.0f, PI_);
  ImGui::InputFloat3("Scale    ", glm::value_ptr(transform_.scale_));
  ImGui::End();
}

} // namespace Gloom