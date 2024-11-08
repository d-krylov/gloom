#ifndef GLOOM_VERTEX_ARRAY_H
#define GLOOM_VERTEX_ARRAY_H

#include "graphics/include/graphics_types.h"

namespace Gloom {

class VertexBuffer;
class IndexBuffer;
class VertexFormat;

class VertexArray {
public:
  VertexArray();

  VertexArray(const VertexBuffer &vbo);

  VertexArray(const VertexBuffer &vbo, const IndexBuffer &ebo);

  ~VertexArray();

  operator uint32_t() const { return vertex_array_; }

  void Bind();

protected:
  void SetVertexFormat(const VertexFormat &vertex_format, uint32_t binding);

private:
  uint32_t vertex_array_{0};
};

} // namespace Gloom

#endif // GLOOM_VERTEX_ARRAY_H