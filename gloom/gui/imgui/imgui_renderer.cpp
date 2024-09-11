#include "imgui_renderer.h"
#include "gloom/core/include/tools.h"
#include "imgui.h"
#include <GLFW/glfw3.h>

namespace Gloom {

VertexFormat GetImGuiVertexFormat() {
  return VertexFormat{DataType::VECTOR2, DataType::VECTOR2, {DataType::PACKED_RGBA, true}};
}

ImGuiRenderer::ImGuiRenderer()
  : graphics_pipeline_{SHADERS_DIR / "gui" / "gui.vert", SHADERS_DIR / "gui" / "gui.frag"},
    vertex_buffer_(4_MiB, GetImGuiVertexFormat()), index_buffer_(4_MiB, IndexType::UNSIGNED_SHORT),
    vertex_array_(vertex_buffer_, index_buffer_) {
  CreateFontsTexture();
}

void ImGuiRenderer::SetBuffers(const ImDrawList *commands) {
  vertex_buffer_.Resize(0);
  vertex_buffer_.Push(std::span(commands->VtxBuffer.Data, commands->VtxBuffer.Size));
  index_buffer_.Resize(0);
  index_buffer_.Push(std::span(commands->IdxBuffer.Data, commands->IdxBuffer.Size));
}

void ImGuiRenderer::RenderDrawData(ImDrawData *draw_data) {
  int32_t fw = (int32_t)(draw_data->DisplaySize.x * draw_data->FramebufferScale.x);
  int32_t fh = (int32_t)(draw_data->DisplaySize.y * draw_data->FramebufferScale.y);

  if (fw <= 0 || fh <= 0) {
    return;
  }

  auto clip_off = draw_data->DisplayPos;
  auto clip_scale = draw_data->FramebufferScale;

  SetupRenderState(draw_data, fw, fh);

  for (uint32_t n = 0; n < draw_data->CmdListsCount; n++) {
    const auto *commands = draw_data->CmdLists[n];
    SetBuffers(commands);

    for (uint32_t i = 0; i < commands->CmdBuffer.Size; i++) {
      const auto *command = &commands->CmdBuffer[i];
      if (command->UserCallback != nullptr) {
        if (command->UserCallback == ImDrawCallback_ResetRenderState) {
        } else {
          command->UserCallback(commands, command);
        }
      } else {
        Vector2f clip_min((command->ClipRect.x - clip_off.x) * clip_scale.x,
                          (command->ClipRect.y - clip_off.y) * clip_scale.y);
        Vector2f clip_max((command->ClipRect.z - clip_off.x) * clip_scale.x,
                          (command->ClipRect.w - clip_off.y) * clip_scale.y);

        if (clip_max.x <= clip_min.x || clip_max.y <= clip_min.y) {
          continue;
        }

        Vector4f v(command->ClipRect.x, command->ClipRect.y, command->ClipRect.z,
                   command->ClipRect.w);

        // Command::SetScissor(int(clip_min.x), int(float(fh) - clip_max.y),
        //                    int(clip_max.x - clip_min.x), int(clip_max.y - clip_min.y));

        glBindTextureUnit(0, (GLuint)(intptr_t)command->GetTexID());

        auto offset = reinterpret_cast<std::byte *>(command->IdxOffset * sizeof(ImDrawIdx));
        Command::DrawElementsBaseVertex(command->ElemCount, command->VtxOffset, offset,
                                        index_buffer_.GetIndexType());
      }
    }
  }
}

void ImGuiRenderer::SetupRenderState(ImDrawData *draw_data, int32_t fw, int32_t fh) {

  Command::SetViewport(0, 0, fw, fh);

  float L = draw_data->DisplayPos.x;
  float R = draw_data->DisplayPos.x + draw_data->DisplaySize.x;
  float T = draw_data->DisplayPos.y;
  float B = draw_data->DisplayPos.y + draw_data->DisplaySize.y;

  if (Command::GetClipOrigin() == ClipOrigin::UPPER_LEFT) {
    std::swap(T, B);
  }

  auto orthographic = glm::ortho(L, R, B, T);
  graphics_pipeline_.SetUniform(ShaderKind::VERTEX, "u_projection_matrix", orthographic);
  graphics_pipeline_.SetUniform(ShaderKind::FRAGMENT, "u_texture", 0);
}

void ImGuiRenderer::CreateFontsTexture() {
  auto &io = ImGui::GetIO();
  uint8_t *pixels{nullptr};
  int32_t w, h;
  io.Fonts->GetTexDataAsRGBA32(&pixels, &w, &h);
  glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
  auto data = std::as_bytes(std::span(pixels, w * h * 4));
  font_texture_ = std::make_unique<Texture2D>(w, h, InternalFormat::RGBA8, data);
  io.Fonts->SetTexID((ImTextureID)(intptr_t)(*font_texture_));
}

void ImGuiRenderer::Begin() {
  ImGui::NewFrame();
  Command::EnableScissor(true);
  Command::EnableBlending(true);
  Command::EnableFaceCulling(false);
  Command::EnableDepthTest(false);
  Command::EnableStencilTest(false);
  Command::SetBlendOperation(BlendOperation::FUNC_ADD);
  Command::SetBlendFunction(BlendFactor::SRC_ALPHA, BlendFactor::ONE_MINUS_SRC_ALPHA,
                            BlendFactor::ONE, BlendFactor::ONE_MINUS_SRC_ALPHA);

  vertex_array_.Bind();
  graphics_pipeline_.Bind();
}

void ImGuiRenderer::End() {
  ImGuiIO &io = ImGui::GetIO();
  ImGui::Render();
  Command::SetViewport(0, 0, int32_t(io.DisplaySize.x), int32_t(io.DisplaySize.y));
  RenderDrawData(ImGui::GetDrawData());
  Command::EnableScissor(false);
  Command::EnableBlending(false);
}

} // namespace Gloom
