#ifndef GLOOM_BUFFER_IPP
#define GLOOM_BUFFER_IPP

#include "buffer.h"

namespace Gloom {

template <ContiguousSizedRange R> void Buffer::Push(R &&source) {
  CORE_VERIFY(storage_ == BufferStorage::DYNAMIC_STORAGE);
  auto size = std::ranges::size(source) * sizeof(std::ranges::range_value_t<R>);
  glNamedBufferSubData(buffer_, size_, size, std::ranges::data(source));
  size_ += size;
}

} // namespace Gloom

#endif // GLOOM_BUFFER_IPP