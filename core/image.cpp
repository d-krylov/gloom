#include "image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

namespace Gloom {

Image::Image(const std::filesystem::path &path) {
  auto data = ToBytePointer(stbi_load(path.c_str(), &size_.x, &size_.y, &channels_, 0));
  if (data != nullptr) {
    image_data_ = std::span<std::byte>(data, size_.x * size_.y * channels_);
  }
}

TextureInternalFormat Image::GetFormat() const {
  switch (channels_) {
  case 3:
    return TextureInternalFormat::RGB8;
    break;
  case 4:
    return TextureInternalFormat::RGBA8;
  default:
    break;
  }
  CORE_UNREACHABLE();
}

Image::~Image() { stbi_image_free(image_data_.data()); }

} // namespace Gloom