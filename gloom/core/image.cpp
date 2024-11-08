#include "core/include/image.h"
#include "stb/stb_image.h"

namespace Gloom {

Image::Image(int32_t width, int32_t height, int32_t channels)
  : width_(width), height_(height), channels_(channels) {
  data_ = std::vector<std::byte>(GetSize(), std::byte(0xff));
}

Image::Image(const std::filesystem::path &path) {
  stbi_set_flip_vertically_on_load(true);
  auto data = stbi_load(path.c_str(), &width_, &height_, &channels_, STBI_default);
  if (data != nullptr) {
    data_ = std::vector<std::byte>(reinterpret_cast<const std::byte *>(data),
                                   reinterpret_cast<const std::byte *>(data) + GetSize());
  }
  stbi_image_free(data);
}

} // namespace Gloom