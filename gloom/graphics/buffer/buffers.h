#ifndef GLOOM_BUFFERS_H
#define GLOOM_BUFFERS_H

#include "buffer.ipp"
#include "graphics/vertex/vertex_format.h"

namespace Gloom {

class VertexBuffer : public Buffer {
public:
  VertexBuffer(std::size_t size, const VertexFormat &vertex_format, uint32_t binding = 0,
               BufferStorage storage = BufferStorage::DYNAMIC_STORAGE)
    : Buffer(BufferTarget::ARRAY, size, storage), vertex_format_(vertex_format), binding_(binding) {
  }

  [[nodiscard]] const VertexFormat &GetFormat() const { return vertex_format_; }
  [[nodiscard]] uint32_t GetBinding() const { return binding_; }

private:
  VertexFormat vertex_format_;
  uint32_t binding_{0};
};

class IndexBuffer : public Buffer {
public:
  IndexBuffer(std::size_t size, IndexType index_type = IndexType::UNSIGNED_INT,
              BufferStorage storage = BufferStorage::DYNAMIC_STORAGE)
    : Buffer(BufferTarget::ELEMENT_ARRAY, size, storage), index_type_(index_type) {}

  [[nodiscard]] IndexType GetIndexType() const { return index_type_; }

private:
  IndexType index_type_{0};
};

} // namespace Gloom

#endif // GLOOM_BUFFERS_H