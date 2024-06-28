#include "gloom_core/include/image.h"
#include "stb/stb_image.h"

namespace Gloom {

Image::Image(const std::filesystem::path &path) {
  auto data = ToBytePointer(stbi_load(path.c_str(), &size_.x, &size_.y, &channels_, 0));
  if (data != nullptr) {
    image_data_ = std::span<std::byte>(data, size_.x * size_.y * channels_);
  }
}

Image::~Image() { stbi_image_free(image_data_.data()); }

} // namespace Gloom