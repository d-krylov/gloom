#ifndef GLOOM_DIRECT_RENDERER_H
#define GLOOM_DIRECT_RENDERER_H

#include "graphics/include/graphics.h"

namespace Gloom {

class Renderer {
public:
  Renderer();

  void Draw(const Mesh &mesh);

private:
  VertexArray vertex_array_;
  VertexBuffer vertex_buffer_;
  Buffer index_buffer_;
};

} // namespace Gloom

#endif // GLOOM_DIRECT_RENDERER_H