#ifndef GLOOM_RENDERER_H
#define GLOOM_RENDERER_H

#include "gloom.h"

namespace Gloom {

class Renderer {
public:
  Renderer();

private:
  VertexArray vertex_array_;
};

} // namespace Gloom

#endif // GLOOM_RENDERER_H