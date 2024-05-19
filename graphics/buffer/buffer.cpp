#include "buffer.h"
#include "gloom_assert.h"

namespace Gloom {

Buffer::Buffer(Types::BufferTarget target, Types::BufferStorage storage, std::size_t size)
  : target_(target), storage_(storage), buffer_size_(size) {
  glCreateBuffers(1, &buffer_handle_);
  glNamedBufferStorage(buffer_handle_, buffer_size_, nullptr, static_cast<uint16_t>(storage_));
}

Buffer::~Buffer() { Destroy(); }

void Buffer::Destroy() { glDeleteBuffers(1, &buffer_handle_); }

void Buffer::MapRange(std::size_t offset, std::size_t size) {
  CORE_VERIFY(data_.empty() == true);
  CORE_VERIFY(offset + size <= buffer_size_);
  auto raw = static_cast<std::byte *>(
    glMapNamedBufferRange(buffer_handle_, offset, size, static_cast<uint16_t>(storage_)));
  CORE_VERIFY(raw != nullptr);
  data_ = std::span<std::byte>(raw, size);
}

void Buffer::Unmap() {
  CORE_VERIFY(data_.empty() == false);
  auto result = glUnmapNamedBuffer(buffer_handle_);
  CORE_VERIFY(result == GL_TRUE);
  data_ = std::span<std::byte>();
}

void Buffer::FlushRange(std::size_t offset, std::size_t size) {
  CORE_VERIFY(offset + size <= buffer_size_);
  glFlushMappedNamedBufferRange(buffer_handle_, offset, size);
}

void Buffer::SetData(std::span<const std::byte> raw) {
  CORE_VERIFY(storage_ == Types::BufferStorage::DYNAMIC_STORAGE);
  CORE_VERIFY(buffer_offset_ + raw.size() <= buffer_size_);
  glNamedBufferSubData(buffer_handle_, buffer_offset_, raw.size(), raw.data());
}

} // namespace Gloom