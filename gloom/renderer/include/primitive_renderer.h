#ifndef PRIMITIVE_RENDERER_H
#define PRIMITIVE_RENDERER_H

#include "core/include/concepts.h"
#include "graphics/include/graphics.h"

namespace Gloom {

class Camera;

class PrimitiveRenderer {
public:
  PrimitiveRenderer();

  void Begin(const Camera &camera);

  void DrawBoxes(const std::vector<Matrix4f> &transforms);

private:
  VertexArray vertex_array_;
  Buffer storage_buffer_;
  GraphicsPipeline graphics_pipeline_;
};

} // namespace Gloom

#endif // PRIMITIVE_RENDERER_H