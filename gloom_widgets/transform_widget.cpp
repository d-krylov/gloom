#include "gloom_widgets/include/transform_widget.h"
#include "gui/include/gui.h"

namespace Gloom {

void TransformWidget::OnImGui() {
  ImGui::Begin("Transform");
  ImGui::InputFloat3("Translate", glm::value_ptr(transform_.translate_));
  ImGui::InputFloat3("Rotate   ", glm::value_ptr(transform_.rotate_));
  ImGui::InputFloat3("Scale    ", glm::value_ptr(transform_.scale_));
  ImGui::End();
}

} // namespace Gloom