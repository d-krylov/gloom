#ifndef RENDERER_H
#define RENDERER_H

#include "graphics.h"

namespace Gloom {

class Renderer {
public:
  Renderer();

private:
  VertexArray vertex_array_;
};

} // namespace Gloom

#endif // RENDERER_H