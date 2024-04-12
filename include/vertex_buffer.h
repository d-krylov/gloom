#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include "buffer.h"
#include "vertex_format.h"

namespace Gloom {

class VertexBuffer {
public:
  VertexBuffer(Types::BufferStorage storage, std::size_t size,
               const VertexFormat &vertex_format)
      : vertex_buffer_(Types::BufferTarget::ARRAY_BUFFER, storage, size),
        vertex_format_(vertex_format) {}

  const Buffer &operator()() const { return vertex_buffer_; }
  Buffer &operator()() { return vertex_buffer_; }

  const VertexFormat &GetFormat() const { return vertex_format_; }

private:
  Buffer vertex_buffer_;
  VertexFormat vertex_format_;
};

} // namespace Gloom

#endif // VERTEX_BUFFER_H