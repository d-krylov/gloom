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

  void SetData(std::span<const std::byte> data, std::size_t offset = 0);
  void FlushRange(std::size_t offset, std::size_t size);
  void MapRange(std::size_t offset, std::size_t size);
  void Unmap();

  [[nodiscard]] std::size_t GetSize() const { return buffer_size_; }
  [[nodiscard]] Types::Handle GetHandle() const { return buffer_handle_; }
  [[nodiscard]] Types::BufferTarget GetTarget() const { return target_; }
  [[nodiscard]] Types::BufferStorage GetStorage() const { return storage_; }

protected:
  void Destroy();

private:
  Types::Handle buffer_handle_{0};
  Types::BufferTarget target_;
  Types::BufferStorage storage_;
  std::size_t buffer_size_{0};
  std::span<std::byte> data_;
};

} // namespace Gloom

#endif // BUFFER_H