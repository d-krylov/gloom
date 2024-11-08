#ifndef GLOOM_IMAGE_H
#define GLOOM_IMAGE_H

#include "graphics/include/graphics_types.h"
#include <filesystem>
#include <vector>

namespace Gloom {

class Image {
public:
  Image(int32_t width = 1, int32_t height = 1, int32_t channels = 4);
  Image(const std::filesystem::path &path);

  [[nodiscard]] std::span<const std::byte> GetData() const { return data_; }

  [[nodiscard]] int32_t GetWidth() const { return width_; }
  [[nodiscard]] int32_t GetHeight() const { return height_; }
  [[nodiscard]] int32_t GetChannels() const { return channels_; }
  [[nodiscard]] int32_t GetSize() const { return width_ * height_ * channels_; }

  [[nodiscard]] InternalFormat GetFormat() const { return GetInternalFormat(channels_); }

private:
  int32_t channels_;
  int32_t width_;
  int32_t height_;
  std::vector<std::byte> data_;
};

} // namespace Gloom

#endif // GLOOM_IMAGE_H