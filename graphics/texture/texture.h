#ifndef TEXTURE_H
#define TEXTURE_H

#include "graphics_types.h"
#include "image.h"
#include <span>

namespace Gloom {

struct TextureDescription {
  Vector3i size_;
  uint32_t samples_{0};
  TextureTarget target_;
  TextureInternalFormat format_;
  SamplerCreateInformation sampler_ci_;
};

class Texture {
public:
  Texture(const TextureDescription &description);

  Texture(const Image &image);

  ~Texture();

  NO_COPY_SEMANTIC(Texture);

  operator Handle() const { return texture_; }

  [[nodiscard]] TextureInternalFormat GetFormat() const { return internal_format_; }

  [[nodiscard]] bool IsLayered() const { return IsTextureLayered(target_); }
  [[nodiscard]] int32_t GetWidth() const { return size_.x; }
  [[nodiscard]] int32_t GetHeight() const { return size_.y; }
  [[nodiscard]] const Vector2i &GetSize() const { return size_; }

  [[nodiscard]] uint64_t GetHandleARB() const;

  void Bind(std::size_t unit);
  void SetData(std::span<const std::byte> data);
  void Destroy();

protected:
  void CreateStorage();
  void SetParameters(const SamplerCreateInformation &sampler_ci);

private:
  Handle texture_{0};
  TextureTarget target_;
  TextureInternalFormat internal_format_;
  Vector2i size_;
  int32_t depth_{0};
};

} // namespace Gloom

#endif // TEXTURE_H