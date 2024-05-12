#ifndef TEXTURE_H
#define TEXTURE_H

#include "gloom_image.h"
#include "graphics_types.h"
#include <span>

namespace Gloom {

struct TextureInformation {
  int32_t width_;
  int32_t height_;
  Types::TextureTarget target;
  Types::TextureInternalFormat internal_format_;
  Types::TextureMagnificationFunction mag_filter_;
  Types::TextureMinifyingFunction min_filter_;
};

class Texture {
public:
  Texture(Types::TextureTarget target,
          Types::TextureInternalFormat internal_format, int32_t width,
          int32_t height);

  Texture(Types::TextureTarget target,
          Types::TextureInternalFormat internal_format, Types::Vector2i size)
      : Texture(target, internal_format, size.x, size.y) {}

  Texture(Types::TextureTarget target, const Image &image)
      : Texture(target, image.GetFormat(), image.GetSize()) {}

  ~Texture();

  operator Types::Handle() const { return texture_handle_; }

  [[nodiscard]] Types::TextureInternalFormat GetFormat() const {
    return internal_format_;
  }

  [[nodiscard]] int32_t GetWidth() const { return size_.x; }
  [[nodiscard]] int32_t GetHeight() const { return size_.y; }
  [[nodiscard]] const Types::Vector2i &GetSize() const { return size_; }

  void Bind(std::size_t unit);
  void SetData(std::span<const std::byte> data);

protected:
  void CreateStorage();
  void SetParameters();

private:
  Types::Handle texture_handle_{0};
  Types::TextureTarget target_;
  Types::TextureInternalFormat internal_format_;
  Types::Vector2i size_;
};

} // namespace Gloom

#endif // TEXTURE_H