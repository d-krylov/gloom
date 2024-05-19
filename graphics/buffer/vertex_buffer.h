#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include "buffer.h"
#include "vertex_format.h"

namespace Gloom {

class VertexBuffer : public Buffer {
public:
  VertexBuffer(Types::BufferStorage storage, std::size_t size,
               const VertexFormat &vertex_format)
    : Buffer(Types::BufferTarget::ARRAY_BUFFER, storage, size), vertex_format_(vertex_format) {
  }

  const VertexFormat &GetFormat() const { return vertex_format_; }

private:
  VertexFormat vertex_format_;
};

} // namespace Gloom

#endif // VERTEX_BUFFER_H