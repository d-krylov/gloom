#include "buffer.ipp"

namespace Gloom {

Buffer::Buffer(BufferTarget target, uint64_t capacity, BufferStorage storage)
  : target_(target), size_(0), capacity_(capacity), storage_(storage) {
  glCreateBuffers(1, &buffer_);
  glNamedBufferStorage(buffer_, capacity_, nullptr, uint16_t(storage_));
}

Buffer::Buffer(Buffer &&other) noexcept
  : buffer_{std::exchange(other.buffer_, 0)}, target_(other.target_), storage_(other.storage_),
    size_(other.size_), capacity_(other.capacity_) {}

Buffer::~Buffer() { glDeleteBuffers(1, &buffer_); }

void Buffer::Map(uint64_t offset, uint64_t size, MapAccess access) {
  CORE_VERIFY(storage_ != BufferStorage::DYNAMIC_STORAGE);
  auto raw = glMapNamedBufferRange(buffer_, offset, size, uint16_t(access));
  if (raw) {
    auto byte_pointer = static_cast<std::byte *>(raw);
    data_ = std::span<std::byte>(byte_pointer, byte_pointer + size);
  }
}

void Buffer::Unmap() {
  glUnmapNamedBuffer(buffer_);
  data_ = std::span<std::byte>();
}

void Buffer::Flush(uint64_t offset, uint64_t size) {
  glFlushMappedNamedBufferRange(buffer_, offset, size);
}

void Buffer::Resize(uint64_t size) { size_ = size; }

void Buffer::Bind() { glBindBuffer(uint16_t(target_), buffer_); }

void Buffer::Bind(uint32_t index) { glBindBufferBase(uint16_t(target_), index, buffer_); }

} // namespace Gloom
