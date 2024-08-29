#include "gloom/core/include/image.h"
#include "stb/stb_image.h"

namespace Gloom {

Image::Image(const std::filesystem::path &path) {
  stbi_set_flip_vertically_on_load(true);
  auto data = stbi_load(path.c_str(), &size_.x, &size_.y, &channels_, STBI_default);
  if (data != nullptr) {
    image_data_ = std::as_writable_bytes(std::span(data, size_.x * size_.y * channels_));
  }
}

Image::~Image() { stbi_image_free(image_data_.data()); }

} // namespace Gloom