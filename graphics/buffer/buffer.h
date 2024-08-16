#ifndef GLOOM_BUFFER_H
#define GLOOM_BUFFER_H

#include "graphics/include/graphics_types.h"
#include <span>
#include <vector>

namespace Gloom {

class Buffer {
public:
  Buffer(BufferTarget target, std::size_t size,
         BufferStorage storage = BufferStorage::DYNAMIC_STORAGE);

  ~Buffer();

  NO_COPY_SEMANTIC(Buffer);

  Buffer(Buffer &&other) noexcept;

  template <typename T> void SetData(const std::vector<T> &data) {
    std::span<const T> span_data(data.data(), data.size());
    SetData(std::as_bytes(span_data));
  }

  template <typename T> void SetData(std::span<T> data) { SetData(std::as_bytes(data)); }

  void SetData(std::span<const std::byte> data, std::size_t offset = 0);

  void FlushRange(std::size_t offset, std::size_t size);
  void MapRange(std::size_t offset, std::size_t size);
  void Unmap();

  void Bind();
  void BindRange(uint32_t index, int64_t offset = 0, uint64_t size = WHOLE_SIZE);

  operator Handle() const { return buffer_; }

  [[nodiscard]] std::size_t GetSize() const { return buffer_size_; }
  [[nodiscard]] std::size_t GetCapacity() const { return buffer_capacity_; }
  [[nodiscard]] BufferTarget GetTarget() const { return target_; }
  [[nodiscard]] BufferStorage GetStorage() const { return storage_; }

protected:
  void Destroy();

private:
  Handle buffer_{0};
  BufferTarget target_;
  BufferStorage storage_{BufferStorage::DYNAMIC_STORAGE};
  std::size_t buffer_size_{0};
  std::size_t buffer_capacity_{0};
  std::span<std::byte> data_;
};

} // namespace Gloom

#endif // GLOOM_BUFFER_H