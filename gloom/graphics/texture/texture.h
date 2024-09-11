#ifndef TEXTURE_H
#define TEXTURE_H

#include "gloom/core/include/cubemap.h"
#include "gloom/graphics/include/graphics_types.h"
#include <span>

namespace Gloom {

struct Wrap {
  Wrap(WrapMode v) : s_(v), t_(v), r_(v) {}
  Wrap(WrapMode s, WrapMode t, WrapMode r) : s_(s), t_(t), r_(r) {}
  WrapMode s_;
  WrapMode t_;
  WrapMode r_;
};

class Texture {
public:
  Texture() = default;

  Texture(int32_t width, int32_t height, int32_t depth, TextureTarget target, InternalFormat format,
          bool mipmap, MinFilter min, MagFilter mag, const Wrap &wrap);

  NO_COPY_SEMANTIC(Texture);

  Texture(Texture &&other) noexcept;

  ~Texture();

  void BindImage(uint32_t unit, int32_t level, bool layered, uint32_t layer, Access access);

  operator uint32_t() const { return texture_; }
  [[nodiscard]] uint32_t GetHandle() const { return texture_; }
  [[nodiscard]] InternalFormat GetFormat() const { return format_; }
  [[nodiscard]] bool IsLayered() const { return IsTextureLayered(target_); }

  [[nodiscard]] int32_t GetWidth() const { return size_.x; }
  [[nodiscard]] int32_t GetHeight() const { return size_.y; }
  [[nodiscard]] int32_t GetDepth() const { return size_.z; }
  [[nodiscard]] const Vector3i &GetSize() const { return size_; }

  [[nodiscard]] uint64_t GetHandleARB() const;

  void Bind(std::size_t unit);
  void SetData(std::span<const std::byte> data, int32_t x = 0, int32_t y = 0, int32_t z = 0);

protected:
  void CreateStorage();
  void SetParameters(MagFilter mag, MinFilter min, const Wrap &wrap);

private:
  uint32_t texture_{0};
  TextureTarget target_;
  InternalFormat format_;
  uint32_t levels_{1};
  Vector3i size_;
};

} // namespace Gloom

#endif // TEXTURE_H