#ifndef RENDERER_H
#define RENDERER_H

#include "graphics.h"

namespace Gloom {

class Renderer {
public:
  Renderer();

  void ProcessMesh(const Mesh &mesh);

  void Draw();

private:
  VertexArray vertex_array_;
  VertexBuffer vertex_buffer_;
  Buffer command_buffer_;

  std::vector<DrawArraysIndirectCommand> commands_;
};

} // namespace Gloom

#endif // RENDERER_H