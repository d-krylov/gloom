#include "imgui_renderer.h"
#include <GLFW/glfw3.h>

using Gloom::operator""_KiB;
using Gloom::operator""_MiB;

namespace Gloom {

VertexFormat GetImGuiVertexFormat() {
  return VertexFormat{DataType::VECTOR2, DataType::VECTOR2, {DataType::BVECTOR4, true}};
}

// clang-format off
Commands::BlendInformation GetBlendInformation() {
  return Commands::BlendInformation{
    BlendEquation::ADD, 
    BlendFunctionSeparate::SRC_ALPHA,
    BlendFunctionSeparate::ONE_MINUS_SRC_ALPHA, 
    BlendFunctionSeparate::ONE,
    BlendFunctionSeparate::ONE_MINUS_SRC_ALPHA};
}
// clang-format on

ImGuiRenderer::ImGuiRenderer()
  : graphics_pipeline_{GetRoot() / "shaders/gui.vert", GetRoot() / "shaders/gui.frag"},
    vertex_array_(), vertex_buffer_(4_MiB, GetImGuiVertexFormat()),
    index_buffer_(BufferTarget::ELEMENT_ARRAY_BUFFER, 4_MiB) {

  CreateFontsTexture();
  vertex_array_.AddVertexBuffer(vertex_buffer_);
  vertex_array_.SetIndexBuffer(index_buffer_);
}

void ImGuiRenderer::RenderDrawData(ImDrawData *draw_data) {
  int fb_width = (int)(draw_data->DisplaySize.x * draw_data->FramebufferScale.x);
  int fb_height = (int)(draw_data->DisplaySize.y * draw_data->FramebufferScale.y);
  if (fb_width <= 0 || fb_height <= 0) {
    return;
  }

  auto clip_off = draw_data->DisplayPos;
  auto clip_scale = draw_data->FramebufferScale;

  SetupRenderState(draw_data, fb_width, fb_height);

  for (uint32_t n = 0; n < draw_data->CmdListsCount; n++) {
    const auto *commands = draw_data->CmdLists[n];
    vertex_buffer_.SetData(std::span(commands->VtxBuffer.Data, commands->VtxBuffer.Size));
    index_buffer_.SetData(std::span(commands->IdxBuffer.Data, commands->IdxBuffer.Size));

    for (uint32_t i = 0; i < commands->CmdBuffer.Size; i++) {
      const auto *command = &commands->CmdBuffer[i];
      if (command->UserCallback != nullptr) {
        if (command->UserCallback == ImDrawCallback_ResetRenderState) {
          SetupRenderState(draw_data, fb_width, fb_height);
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

        Vector4i scissor{int(clip_min.x), int(float(fb_height) - clip_max.y),
                         int(clip_max.x - clip_min.x), int(clip_max.y - clip_min.y)};
        Commands::SetScissor(true, scissor);

        glBindTextureUnit(0, (GLuint)(intptr_t)command->GetTexID());

        Commands::DrawElementsBaseVertex(
          PrimitiveKind::TRIANGLES, command->ElemCount, CoreType::UNSIGNED_SHORT,
          command->IdxOffset * sizeof(ImDrawIdx), command->VtxOffset);
      }
    }
  }

  Commands::SetScissor(false);
  Commands::SetBlending(false);
}

void ImGuiRenderer::SetupRenderState(ImDrawData *draw_data, int fb_width, int fb_height) {
  Commands::SetBlending(true, GetBlendInformation());
  Commands::SetFaceCulling(false);
  Commands::SetDepthTesting(false);
  Commands::SetStencilTesting(false);
  Commands::SetPrimitiveRestart(false);
  Commands::SetPolygonMode();

  bool clip_origin_lower_left = true;

  GLenum current_clip_origin = 0;
  glGetIntegerv(GL_CLIP_ORIGIN, (GLint *)&current_clip_origin);
  if (current_clip_origin == GL_UPPER_LEFT) {
    clip_origin_lower_left = false;
  }

  Commands::SetViewport(0, 0, fb_width, fb_height);
  float L = draw_data->DisplayPos.x;
  float R = draw_data->DisplayPos.x + draw_data->DisplaySize.x;
  float T = draw_data->DisplayPos.y;
  float B = draw_data->DisplayPos.y + draw_data->DisplaySize.y;

  if (!clip_origin_lower_left) {
    std::swap(T, B);
  }

  auto orthographic = glm::ortho(L, R, B, T);
  graphics_pipeline_.SetUniform(ShaderIndex::VERTEX, "u_projection_matrix", orthographic);
  graphics_pipeline_.SetUniform(ShaderIndex::FRAGMENT, "u_texture", 0);
}

void ImGuiRenderer::CreateFontsTexture() {
  auto &io = ImGui::GetIO();
  uint8_t *pixels{nullptr};
  int32_t w, h;
  io.Fonts->GetTexDataAsRGBA32(&pixels, &w, &h);
  font_texture_ =
    std::make_unique<Texture>(TextureTarget::TEXTURE_2D, TextureInternalFormat::RGBA8, w, h);
  glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
  auto *byte_pixels = ToBytePointer(pixels);
  std::span<const std::byte> span_pixels(byte_pixels, w * h * 4);
  font_texture_->SetData(span_pixels);
  io.Fonts->SetTexID((ImTextureID)(intptr_t)(*font_texture_));
}

void ImGuiRenderer::Begin() {
  ImGui::NewFrame();
  vertex_array_.Bind();
  graphics_pipeline_.Bind();
}

void ImGuiRenderer::End() {
  ImGuiIO &io = ImGui::GetIO();
  ImGui::Render();
  Commands::SetViewport(0, 0, int(io.DisplaySize.x), int(io.DisplaySize.y));
  RenderDrawData(ImGui::GetDrawData());
}

} // namespace Gloom
