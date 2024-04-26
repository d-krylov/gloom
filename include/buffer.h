#ifndef BUFFER_H
#define BUFFER_H

#include "gloom_types.h"
#include <span>

namespace Gloom {

class Buffer {
public:
  Buffer(Types::BufferTarget target, Types::BufferStorage storage,
         std::size_t size);

  ~Buffer();

  NO_COPY_SEMANTIC(Buffer);

  template <typename T> void SetData(std::span<T> data) {
    SetData(std::as_bytes(data));
  }

  void SetData(std::span<const std::byte> data);
  void FlushRange(std::size_t offset, std::size_t size);
  void MapRange(std::size_t offset, std::size_t size);
  void Unmap();

  void Reset() { buffer_offset_ = 0; }

  operator Types::Handle() const { return buffer_handle_; }

  [[nodiscard]] std::size_t GetSize() const { return buffer_size_; }
  [[nodiscard]] std::size_t GetOffset() const { return buffer_offset_; }
  [[nodiscard]] Types::BufferTarget GetTarget() const { return target_; }
  [[nodiscard]] Types::BufferStorage GetStorage() const { return storage_; }

protected:
  void Destroy();

private:
  Types::Handle buffer_handle_{0};
  Types::BufferTarget target_;
  Types::BufferStorage storage_{Types::BufferStorage::DYNAMIC_STORAGE};
  std::size_t buffer_size_{0};
  std::size_t buffer_offset_{0};
  std::span<std::byte> data_;
};

} // namespace Gloom

#endif // BUFFER_H