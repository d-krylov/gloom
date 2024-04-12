#include "buffer.h"
#include "gloom_assert.h"

namespace Gloom {

Buffer::Buffer(Types::BufferTarget target, Types::BufferStorage storage,
               std::size_t size)
    : target_(target), storage_(storage), buffer_size_(size) {
  glCreateBuffers(1, &buffer_handle_);
  glNamedBufferStorage(buffer_handle_, buffer_size_, nullptr,
                       static_cast<uint16_t>(storage_));
}

Buffer::~Buffer() { Destroy(); }

void Buffer::Destroy() { glDeleteBuffers(1, &buffer_handle_); }

void Buffer::MapRange(std::size_t offset, std::size_t size) {
  GLOOM_VERIFY(data_.empty() == true);
  GLOOM_VERIFY(offset + size <= buffer_size_);
  auto raw = static_cast<std::byte *>(glMapNamedBufferRange(
      buffer_handle_, offset, size, static_cast<uint16_t>(storage_)));
  GLOOM_VERIFY(raw != nullptr);
  data_ = std::span<std::byte>(raw, size);
}

void Buffer::Unmap() {
  GLOOM_VERIFY(data_.empty() == false);
  auto result = glUnmapNamedBuffer(buffer_handle_);
  GLOOM_VERIFY(result == GL_TRUE);
  data_ = std::span<std::byte>();
}

void Buffer::FlushRange(std::size_t offset, std::size_t size) {
  GLOOM_VERIFY(offset + size <= buffer_size_);
  glFlushMappedNamedBufferRange(buffer_handle_, offset, size);
}

void Buffer::SetData(std::span<const std::byte> data, std::size_t offset) {
  GLOOM_VERIFY(storage_ == Types::BufferStorage::DYNAMIC_STORAGE);
  GLOOM_VERIFY(offset + data.size() <= buffer_size_);
  glNamedBufferSubData(buffer_handle_, offset, data.size(), data.data());
}

} // namespace Gloom