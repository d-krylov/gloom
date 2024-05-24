#include "buffer.h"

namespace Gloom {

Buffer::Buffer(Types::BufferTarget target, std::size_t size, Types::BufferStorage storage)
  : target_(target), buffer_size_(size), storage_(storage) {
  glCreateBuffers(1, &buffer_);
  glNamedBufferStorage(buffer_, buffer_size_, nullptr, static_cast<uint16_t>(storage_));
}

Buffer::~Buffer() { Destroy(); }

void Buffer::Destroy() { glDeleteBuffers(1, &buffer_); }

void Buffer::MapRange(std::size_t offset, std::size_t size) {
  CORE_VERIFY(data_.empty() == true);
  CORE_VERIFY(offset + size <= buffer_size_);
  auto raw = static_cast<std::byte *>(
    glMapNamedBufferRange(buffer_, offset, size, static_cast<uint16_t>(storage_)));
  CORE_VERIFY(raw != nullptr);
  data_ = std::span<std::byte>(raw, size);
}

void Buffer::Unmap() {
  CORE_VERIFY(data_.empty() == false);
  auto result = glUnmapNamedBuffer(buffer_);
  CORE_VERIFY(result == GL_TRUE);
  data_ = std::span<std::byte>();
}

void Buffer::FlushRange(std::size_t offset, std::size_t size) {
  CORE_VERIFY(offset + size <= buffer_size_);
  glFlushMappedNamedBufferRange(buffer_, offset, size);
}

void Buffer::SetData(std::span<const std::byte> raw) {
  CORE_VERIFY(storage_ == Types::BufferStorage::DYNAMIC_STORAGE);
  CORE_VERIFY(buffer_offset_ + raw.size() <= buffer_size_);
  glNamedBufferSubData(buffer_, buffer_offset_, raw.size(), raw.data());
}

void Buffer::Bind() { glBindBuffer(static_cast<uint16_t>(target_), buffer_); }

void Buffer::BindRange(uint32_t index, int64_t offset, uint64_t size) {
  size = (size == Types::WHOLE_SIZE) ? buffer_size_ : size;
  glBindBufferRange(static_cast<uint16_t>(target_), index, buffer_, offset, size);
}

} // namespace Gloom