#include "buffer.h"

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

void Buffer::MapRange(std::size_t offset, std::size_t size) {}

void Buffer::Unmap() {}

void Buffer::FlushRange(uint64_t offset, uint64_t size) {
  glFlushMappedNamedBufferRange(buffer_, offset, size);
}

void Buffer::SetRawData(uint64_t offset, std::span<const std::byte> raw) {
  glNamedBufferSubData(buffer_, offset, raw.size(), raw.data());
}

void Buffer::Resize(uint64_t size) { size_ = size; }

void Buffer::Bind() { glBindBuffer(uint16_t(target_), buffer_); }

void Buffer::BindRange(uint32_t index, int64_t offset, uint64_t size) {}

} // namespace Gloom