#ifndef GLOOM_BUFFER_H
#define GLOOM_BUFFER_H

#include "gloom/graphics/include/graphics_types.h"
#include <span>
#include <vector>

namespace Gloom {

class Buffer {
public:
  Buffer(BufferTarget target, uint64_t capacity,
         BufferStorage storage = BufferStorage::DYNAMIC_STORAGE);

  NO_COPY_SEMANTIC(Buffer);

  Buffer(Buffer &&other) noexcept;

  ~Buffer();

  [[nodiscard]] uint64_t GetSize() const { return size_; }
  [[nodiscard]] uint64_t GetCapacity() const { return capacity_; }
  [[nodiscard]] BufferTarget GetTarget() const { return target_; }
  [[nodiscard]] BufferStorage GetStorage() const { return storage_; }

  operator uint32_t() const { return buffer_; }

  void Resize(uint64_t size);

  template <typename R>
  requires std::ranges::contiguous_range<R> &&std::ranges::sized_range<R> void Push(R &&source) {
    auto size = std::ranges::size(source) * sizeof(std::ranges::range_value_t<R>);
    glNamedBufferSubData(buffer_, size_, size, std::ranges::data(source));
    size_ += size;
  }

  void FlushRange(uint64_t offset, uint64_t size);
  void MapRange(uint64_t offset, uint64_t size);
  void Unmap();

  void Bind();
  void BindRange(uint32_t index, int64_t offset = 0, uint64_t size = 0);

protected:
  void SetRawData(uint64_t offset, std::span<const std::byte> raw);

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