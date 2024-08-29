#ifndef GLOOM_INDEX_BUFFER_H
#define GLOOM_INDEX_BUFFER_H

#include "buffer.h"

namespace Gloom {

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

#endif // GLOOM_INDEX_BUFFER_H