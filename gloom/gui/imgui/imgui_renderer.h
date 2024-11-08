#ifndef IMGUI_RENDERER_H
#define IMGUI_RENDERER_H

#include "graphics/include/graphics.h"
#include <memory>

struct ImDrawData;
struct ImDrawList;

namespace Gloom {

class ImGuiRenderer {
public:
  ImGuiRenderer();

  void Begin();
  void End();

  void RenderDrawData(ImDrawData *draw_data);
  void SetupRenderState(ImDrawData *draw_data, int fb_width, int fb_height);
  void CreateFontsTexture();

private:
  void SetBuffers(const ImDrawList *commands);

private:
  GraphicsPipeline graphics_pipeline_;
  VertexBuffer vertex_buffer_;
  IndexBuffer index_buffer_;
  VertexArray vertex_array_;
  std::unique_ptr<Texture2D> font_texture_;
};

} // namespace Gloom

#endif // IMGUI_RENDERER_H