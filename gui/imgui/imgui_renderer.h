#ifndef IMGUI_RENDERER_H
#define IMGUI_RENDERER_H

#include "graphics/include/graphics.h"
#include "gui.h"
#include <memory>

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
  GraphicsPipeline graphics_pipeline_;
  VertexArray vertex_array_;
  VertexBuffer vertex_buffer_;
  Buffer index_buffer_;
  std::unique_ptr<Texture> font_texture_;
};

} // namespace Gloom

#endif // IMGUI_RENDERER_H