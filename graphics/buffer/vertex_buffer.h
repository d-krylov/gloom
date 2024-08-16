#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include "buffer.h"
#include "graphics/vertex/vertex_format.h"

namespace Gloom {

class VertexBuffer : public Buffer {
public:
  VertexBuffer(std::size_t size, const VertexFormat &vertex_format, uint32_t binding = 0,
               BufferStorage storage = BufferStorage::DYNAMIC_STORAGE)
    : Buffer(BufferTarget::ARRAY_BUFFER, size, storage), vertex_format_(vertex_format),
      binding_(binding) {}

  [[nodiscard]] const VertexFormat &GetFormat() const { return vertex_format_; }
  [[nodiscard]] uint32_t GetBinding() const { return binding_; }

private:
  VertexFormat vertex_format_;
  uint32_t binding_{0};
};

} // namespace Gloom

#endif // VERTEX_BUFFER_H