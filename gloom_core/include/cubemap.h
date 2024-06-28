#ifndef GLOOM_CUBEMAP_H
#define GLOOM_CUBEMAP_H

#include "graphics_types.h"
#include <span>

namespace Gloom {

class CubeMap {
public:
  CubeMap(const std::initializer_list<std::filesystem::path> &pathes_RL_TB_BF);

  ~CubeMap();

  [[nodiscard]] std::span<const std::byte> GetData(uint32_t i) const;

  [[nodiscard]] const Vector2i &GetSize() const { return size_; }
  [[nodiscard]] int32_t GetWidth() const { return size_.x; }
  [[nodiscard]] int32_t GetHeight() const { return size_.y; }
  [[nodiscard]] int32_t GetChannels() const { return channels_; }

  [[nodiscard]] TextureInternalFormat GetFormat() const {
    return GetFormatFromChannels(channels_);
  }

private:
  int32_t channels_;
  Vector2i size_;
  std::array<std::byte *, 6> data_;
};

} // namespace Gloom

#endif // GLOOM_CUBEMAP_H