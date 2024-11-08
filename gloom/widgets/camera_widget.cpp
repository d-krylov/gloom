#include "widgets/include/camera_widget.h"
#include "imgui.h"

namespace Gloom {

void CameraWidget::OnImGui() {
  ImGui::Begin("Camera");

  if (ImGui::RadioButton("Perspective", selected_ == 0)) {
    selected_ = 0;
  }

  if (ImGui::RadioButton("Orthographic", selected_ == 1)) {
    selected_ = 1;
  }

  auto &current_camera = const_cast<Camera &>(GetActiveCamera());
  position_ = current_camera.GetPosition();
  rotation_ = current_camera.GetRotation();

  ImGui::InputFloat3("Camera position", glm::value_ptr(position_));
  ImGui::SliderFloat3("Camera rotation", glm::value_ptr(rotation_), 0.0f, 360.0f);

  current_camera.SetPosition(position_);
  current_camera.SetRotation(rotation_);

  if (selected_ == 0) {
    DrawPerspective();
  }

  if (selected_ == 1) {
    DrawOrthographic();
  }

  ImGui::End();
}

void CameraWidget::DrawPerspective() {
  ImGui::SliderFloat("FOV", &perspective_.fov_, 0.0f, 180.0f);
}

void CameraWidget::DrawOrthographic() {
  ImGui::InputFloat("Left", &orthographic_.left_);
  ImGui::InputFloat("Right", &orthographic_.right_);
  ImGui::InputFloat("Bottom", &orthographic_.bottom_);
  ImGui::InputFloat("Top", &orthographic_.top_);
  orthographic_.SetPosition(position_);
  orthographic_.SetRotation(rotation_);
}

void CameraWidget::OnResize(uint32_t width, uint32_t height) {
  perspective_.OnResize(width, height);
  orthographic_.OnResize(width, height);
}

const Camera &CameraWidget::GetActiveCamera() const {
  if (selected_ == 0) {
    return perspective_;
  }
  return orthographic_;
}

} // namespace Gloom