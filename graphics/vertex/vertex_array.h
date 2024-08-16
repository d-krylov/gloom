#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include "graphics/buffer/vertex_buffer.h"

namespace Gloom {

class VertexArray {
public:
  VertexArray();
  ~VertexArray();

  operator Handle() const { return vertex_array_; }

  void SetIndexBuffer(const Buffer &buffer);
  void AddVertexBuffer(const VertexBuffer &vbo);

  void Bind();

protected:
  void SetVertexFormat(const VertexFormat &vertex_format, uint32_t binding);

private:
  Handle vertex_array_{0};
};

} // namespace Gloom

#endif // VERTEX_ARRAY_H