#include "imgui_renderer.h"
#include "tools.h"
#include <GLFW/glfw3.h>

using Gloom::Types::operator""_KiB;
using Gloom::Types::operator""_MiB;

namespace Gloom {

VertexFormat GetImGuiVertexFormat() {
  return VertexFormat{
    Types::DataType::VECTOR2, Types::DataType::VECTOR2, {Types::DataType::BVECTOR4, true}};
}

// clang-format off
Commands::BlendInformation GetBlendInformation() {
  return Commands::BlendInformation{
    Types::BlendEquation::ADD, 
    Types::BlendFunctionSeparate::SRC_ALPHA,
    Types::BlendFunctionSeparate::ONE_MINUS_SRC_ALPHA, 
    Types::BlendFunctionSeparate::ONE,
    Types::BlendFunctionSeparate::ONE_MINUS_SRC_ALPHA};
}
// clang-format on

ImGuiRenderer::ImGuiRenderer()
  : graphics_pipeline_(GetRoot() / "shaders/gui.vert", GetRoot() / "shaders/gui.frag"),
    vertex_array_(), vertex_buffer_(4_MiB, GetImGuiVertexFormat()),
    index_buffer_(Types::BufferTarget::ELEMENT_ARRAY_BUFFER, 4_MiB) {

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
    const auto *cmd_list = draw_data->CmdLists[n];

    std::span<ImDrawVert> vertices(cmd_list->VtxBuffer.Data, cmd_list->VtxBuffer.Size);
    std::span<ImDrawIdx> indices(cmd_list->IdxBuffer.Data, cmd_list->IdxBuffer.Size);
    vertex_buffer_.SetData(vertices);
    index_buffer_.SetData(indices);

    for (uint32_t cmd_i = 0; cmd_i < cmd_list->CmdBuffer.Size; cmd_i++) {
      const auto *pcmd = &cmd_list->CmdBuffer[cmd_i];
      if (pcmd->UserCallback != nullptr) {
        if (pcmd->UserCallback == ImDrawCallback_ResetRenderState) {
          SetupRenderState(draw_data, fb_width, fb_height);
        } else {
          pcmd->UserCallback(cmd_list, pcmd);
        }
      } else {
        Types::Vector2f clip_min((pcmd->ClipRect.x - clip_off.x) * clip_scale.x,
                                 (pcmd->ClipRect.y - clip_off.y) * clip_scale.y);
        Types::Vector2f clip_max((pcmd->ClipRect.z - clip_off.x) * clip_scale.x,
                                 (pcmd->ClipRect.w - clip_off.y) * clip_scale.y);

        if (clip_max.x <= clip_min.x || clip_max.y <= clip_min.y) {
          continue;
        }

        Types::Vector4i scissor{int(clip_min.x), int(float(fb_height) - clip_max.y),
                                int(clip_max.x - clip_min.x), int(clip_max.y - clip_min.y)};
        Commands::SetScissor(true, scissor);

        glBindTextureUnit(0, (GLuint)(intptr_t)pcmd->GetTexID());

        Commands::DrawElementsBaseVertex(Types::PrimitiveKind::TRIANGLES, pcmd->ElemCount,
                                         Types::CoreType::UNSIGNED_SHORT,
                                         pcmd->IdxOffset * sizeof(ImDrawIdx), pcmd->VtxOffset);
      }
    }
  }

  glDisable(GL_SCISSOR_TEST);
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

  float PM00 = 2.0f / (R - L);
  float PM11 = 2.0f / (T - B);
  float PM30 = (R + L) / (L - R);
  float PM31 = (T + B) / (B - T);

  auto projection_matrix = Types::Matrix4f{{PM00, 0.0f, +0.0f, 0.0f},
                                           {0.0f, PM11, +0.0f, 0.0f},
                                           {0.0f, 0.0f, -1.0f, 0.0f},
                                           {PM30, PM31, +0.0f, 1.0f}};

  graphics_pipeline_.SetUniform(Types::ShaderIndex::VERTEX, "u_projection_matrix",
                                projection_matrix, false);
  graphics_pipeline_.SetUniform(Types::ShaderIndex::FRAGMENT, "u_texture", 0);
}

void ImGuiRenderer::CreateFontsTexture() {
  auto &io = ImGui::GetIO();
  unsigned char *pixels{nullptr};
  int w, h;
  io.Fonts->GetTexDataAsRGBA32(&pixels, &w, &h);
  font_texture_ = std::make_unique<Texture>(Types::TextureTarget::TEXTURE_2D,
                                            Types::TextureInternalFormat::RGBA8, w, h);
  glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
  std::byte *byte_pixels = reinterpret_cast<std::byte *>(pixels);
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
