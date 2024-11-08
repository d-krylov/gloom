#ifndef GLOOM_BUFFER_H
#define GLOOM_BUFFER_H

#include "core/include/concepts.h"
#include "graphics/include/graphics_types.h"
#include <vector>

namespace Gloom {

class Buffer {
public:
  Buffer(BufferTarget target, uint64_t capacity,
         BufferStorage storage = BufferStorage::DYNAMIC_STORAGE);

  NO_COPY_SEMANTIC(Buffer);

  Buffer(Buffer &&other) noexcept;

  ~Buffer();

  [[nodiscard]] std::span<std::byte> GetMap() const { return data_; }

  [[nodiscard]] uint64_t GetSize() const { return size_; }
  [[nodiscard]] uint64_t GetCapacity() const { return capacity_; }
  [[nodiscard]] BufferTarget GetTarget() const { return target_; }
  [[nodiscard]] BufferStorage GetStorage() const { return storage_; }

  operator uint32_t() const { return buffer_; }

  void Resize(uint64_t size);

  template <ContiguousSizedRange R> void Push(R &&source);

  void Map(uint64_t offset, uint64_t size, MapAccess access);
  void Unmap();
  void Flush(uint64_t offset, uint64_t size);

  void Bind();
  void Bind(uint32_t index);

private:
  uint32_t buffer_{0};
  uint64_t size_{0};
  uint64_t capacity_{0};
  BufferTarget target_;
  BufferStorage storage_{BufferStorage::DYNAMIC_STORAGE};
  std::span<std::byte> data_;
};

} // namespace Gloom

#endif // GLOOM_BUFFER_H