#ifndef GLOOM_IMAGE_H
#define GLOOM_IMAGE_H

#include "gloom_types.h"
#include <filesystem>
#include <span>

namespace Gloom {

class Image {
public:
  Image(std::filesystem::path path);

  ~Image();

  [[nodiscard]] std::span<const std::byte> GetData() const {
    return image_data_;
  }

  [[nodiscard]] const Types::Vector2i &GetSize() const { return size_; }
  [[nodiscard]] int32_t GetWidth() const { return size_.x; }
  [[nodiscard]] int32_t GetHeigth() const { return size_.y; }
  [[nodiscard]] int32_t GetChannels() const { return channels_; }

  Types::TextureInternalFormat GetFormat() const;

private:
  int32_t channels_;
  Types::Vector2i size_;
  std::span<std::byte> image_data_;
};

} // namespace Gloom

#endif // GLOOM_IMAGE_H