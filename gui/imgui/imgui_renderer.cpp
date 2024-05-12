#include "imgui_renderer.h"
#include "gloom_literals.h"
#include "gloom_tools.h"
#include <GLFW/glfw3.h>

Gloom::ImGuiRenderer *instance = nullptr;

void RenderWindow(ImGuiViewport *viewport, void *) {
  if (!(viewport->Flags & ImGuiViewportFlags_NoRendererClear)) {
    ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
  }
  instance->RenderDrawData(viewport->DrawData);
}

namespace Gloom {

VertexFormat GetImGuiVertexFormat() {
  return VertexFormat{Types::DataType::VECTOR2,
                      Types::DataType::VECTOR2,
                      {Types::DataType::BVECTOR4, true}};
}

ImGuiRenderer::ImGuiRenderer()
    : graphics_pipeline_(Tools::GetRoot() / "shaders/gui.vert",
                         Tools::GetRoot() / "shaders/gui.frag"),
      vertex_array_(), vertex_buffer_(Types::BufferStorage::DYNAMIC_STORAGE,
                                      4_MiB, GetImGuiVertexFormat()),
      index_buffer_(Types::BufferTarget::ELEMENT_ARRAY_BUFFER,
                    Types::BufferStorage::DYNAMIC_STORAGE, 4_MiB) {

  CreateFontsTexture();
  vertex_array_.AddVertexBuffer(vertex_buffer_);
  vertex_array_.SetIndexBuffer(index_buffer_);
  vertex_array_.Bind();
  graphics_pipeline_.Bind();

  instance = this;

  ImGuiPlatformIO &platform_io = ImGui::GetPlatformIO();
  platform_io.Renderer_RenderWindow = RenderWindow;
}

void ImGuiRenderer::RenderDrawData(ImDrawData *draw_data) {
  int fb_width =
      (int)(draw_data->DisplaySize.x * draw_data->FramebufferScale.x);
  int fb_height =
      (int)(draw_data->DisplaySize.y * draw_data->FramebufferScale.y);
  if (fb_width <= 0 || fb_height <= 0) {
    return;
  }
  GLuint last_texture;
  glGetIntegerv(GL_TEXTURE_BINDING_2D, (GLint *)&last_texture);
  GLenum last_active_texture;
  glGetIntegerv(GL_ACTIVE_TEXTURE, (GLint *)&last_active_texture);
  GLint last_scissor_box[4];
  glGetIntegerv(GL_SCISSOR_BOX, last_scissor_box);
  GLint last_viewport[4];
  glGetIntegerv(GL_VIEWPORT, last_viewport);
  glActiveTexture(GL_TEXTURE0);

  auto clip_off = draw_data->DisplayPos;
  auto clip_scale = draw_data->FramebufferScale;

  SetupRenderState(draw_data, fb_width, fb_height);

  for (uint32_t n = 0; n < draw_data->CmdListsCount; n++) {
    const auto *cmd_list = draw_data->CmdLists[n];

    std::span<ImDrawVert> vertices(cmd_list->VtxBuffer.Data,
                                   cmd_list->VtxBuffer.Size);
    std::span<ImDrawIdx> indices(cmd_list->IdxBuffer.Data,
                                 cmd_list->IdxBuffer.Size);
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
        ImVec2 clip_min((pcmd->ClipRect.x - clip_off.x) * clip_scale.x,
                        (pcmd->ClipRect.y - clip_off.y) * clip_scale.y);
        ImVec2 clip_max((pcmd->ClipRect.z - clip_off.x) * clip_scale.x,
                        (pcmd->ClipRect.w - clip_off.y) * clip_scale.y);

        if (clip_max.x <= clip_min.x || clip_max.y <= clip_min.y) {
          continue;
        }

        glScissor((int)clip_min.x, (int)((float)fb_height - clip_max.y),
                  (int)(clip_max.x - clip_min.x),
                  (int)(clip_max.y - clip_min.y));

        glBindTextureUnit(0, (GLuint)(intptr_t)pcmd->GetTexID());

        Commands::DrawElementsBaseVertex(
            Types::PrimitiveKind::TRIANGLES, pcmd->ElemCount,
            Types::CoreType::UNSIGNED_SHORT,
            pcmd->IdxOffset * sizeof(ImDrawIdx), pcmd->VtxOffset);
      }
    }
  }
  glBindTexture(GL_TEXTURE_2D, last_texture);
  glActiveTexture(last_active_texture);
  glViewport(last_viewport[0], last_viewport[1], (GLsizei)last_viewport[2],
             (GLsizei)last_viewport[3]);
  glDisable(GL_SCISSOR_TEST);
  glDisable(GL_BLEND);
}

void ImGuiRenderer::SetupRenderState(ImDrawData *draw_data, int fb_width,
                                     int fb_height) {
  Commands::SetBlending(true, Types::BlendEquation::ADD,
                        Types::BlendFunctionSeparate::SRC_ALPHA,
                        Types::BlendFunctionSeparate::ONE_MINUS_SRC_ALPHA,
                        Types::BlendFunctionSeparate::ONE,
                        Types::BlendFunctionSeparate::ONE_MINUS_SRC_ALPHA);

  Commands::SetFaceCulling(false);
  Commands::SetDepthTesting(false);
  glDisable(GL_STENCIL_TEST);
  glEnable(GL_SCISSOR_TEST);
  glDisable(GL_PRIMITIVE_RESTART);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

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

  auto projection_matrix = Types::Matrix4f{
      {PM00, 0.0f, +0.0f, 0.0f},
      {0.0f, PM11, +0.0f, 0.0f},
      {0.0f, 0.0f, -1.0f, 0.0f},
      {PM30, PM31, +0.0f, 1.0f},
  };

  graphics_pipeline_.SetUniform(Types::ShaderIndex::VERTEX,
                                "u_projection_matrix", projection_matrix,
                                false);
  graphics_pipeline_.SetUniform(Types::ShaderIndex::FRAGMENT, "u_texture", 0);
}

void ImGuiRenderer::CreateFontsTexture() {
  auto &io = ImGui::GetIO();
  unsigned char *pixels;
  int w, h;
  io.Fonts->GetTexDataAsRGBA32(&pixels, &w, &h);
  glCreateTextures(GL_TEXTURE_2D, 1, &font_texture_);
  glTextureParameteri(font_texture_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTextureParameteri(font_texture_, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
  glTextureStorage2D(font_texture_, 1, GL_RGBA8, w, h);
  glTextureSubImage2D(font_texture_, 0, 0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE,
                      pixels);
  io.Fonts->SetTexID((ImTextureID)(intptr_t)font_texture_);
}

void ImGuiRenderer::Begin() {
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}

void ImGuiRenderer::End() {
  ImGuiIO &io = ImGui::GetIO();

  ImGui::Render();

  glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
  glClear(GL_COLOR_BUFFER_BIT);

  RenderDrawData(ImGui::GetDrawData());

  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    GLFWwindow *backup_current_context = glfwGetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    glfwMakeContextCurrent(backup_current_context);
  }
}

} // namespace Gloom
