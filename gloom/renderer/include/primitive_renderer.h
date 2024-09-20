#ifndef PRIMITIVE_RENDERER_H
#define PRIMITIVE_RENDERER_H

#include "gloom/core/include/concepts.h"
#include "gloom/graphics/include/graphics.h"

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
};

} // namespace Gloom

#endif // PRIMITIVE_RENDERER_H