#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include "vertex_buffer.h"
#include "vertex_format.h"

namespace Gloom {

class VertexArray {
public:
  VertexArray();
  ~VertexArray();

  operator Types::Handle() const { return vertex_array_handle_; }

  void SetIndexBuffer(const Buffer &buffer);
  void AddVertexBuffer(const VertexBuffer &vbo);

  void AddVertexBufferAndFormat(const Buffer &buffer,
                                const VertexFormat &vertex_format);
  void Bind();

protected:
  void SetVertexFormat(const VertexFormat &vertex_format);
  void UpdateBinding() { current_binding_++; }
  std::size_t GetBinding() const { return current_binding_; }

private:
  Types::Handle vertex_array_handle_{0};
  std::size_t current_binding_{0};
};

} // namespace Gloom

#endif // VERTEX_ARRAY_H