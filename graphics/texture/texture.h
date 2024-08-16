#ifndef TEXTURE_H
#define TEXTURE_H

#include "gloom_core/include/cubemap.h"
#include "gloom_core/include/image.h"
#include "graphics/include/graphics_types.h"
#include <span>

namespace Gloom {

class Texture {
public:
  Texture(TextureTarget target, TextureInternalFormat format, int32_t w, int32_t h,
          int32_t depth = 1, uint32_t samples = 0,
          TextureMagnificationFunction mag = TextureMagnificationFunction::LINEAR,
          TextureMinifyingFunction min = TextureMinifyingFunction::LINEAR,
          TextureWrapMode s = TextureWrapMode::CLAMP_TO_EDGE,
          TextureWrapMode t = TextureWrapMode::CLAMP_TO_EDGE,
          TextureWrapMode r = TextureWrapMode::CLAMP_TO_EDGE);

  Texture(Texture &&other) noexcept;

  void BindImage(uint32_t unit, int32_t level, bool layered, uint32_t layer, Access access);

  Texture(const Image &image);

  Texture(const CubeMap &cubemap);

  ~Texture();

  NO_COPY_SEMANTIC(Texture);

  operator Handle() const { return texture_; }
  [[nodiscard]] Handle GetHandle() const { return texture_; }
  [[nodiscard]] TextureInternalFormat GetFormat() const { return internal_format_; }
  [[nodiscard]] bool IsLayered() const { return IsTextureLayered(target_); }
  [[nodiscard]] int32_t GetWidth() const { return size_.x; }
  [[nodiscard]] int32_t GetHeight() const { return size_.y; }
  [[nodiscard]] const Vector2i &GetSize() const { return size_; }

  [[nodiscard]] uint64_t GetHandleARB() const;

  void Bind(std::size_t unit);
  void SetData(std::span<const std::byte> data, int32_t xoffset = 0, int32_t yoffset = 0,
               int32_t zoffset = 0);
  void Destroy();

protected:
  void CreateStorage();
  void SetParameters(TextureMagnificationFunction mag, TextureMinifyingFunction min,
                     TextureWrapMode s, TextureWrapMode t, TextureWrapMode r);

private:
  Handle texture_{0};
  TextureTarget target_;
  TextureInternalFormat internal_format_;
  Vector2i size_;
  int32_t depth_{0};
};

} // namespace Gloom

#endif // TEXTURE_H