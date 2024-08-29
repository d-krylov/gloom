#ifndef GLOOM_TEXTURE_2D_H
#define GLOOM_TEXTURE_2D_H

#include "texture.h"

namespace Gloom {

class Image;

class Texture2D final : public Texture {
public:
  Texture2D() = default;

  Texture2D(const Image &image);

  Texture2D(uint32_t w, uint32_t h, InternalFormat format, std::span<const std::byte> data = {});
};

class TextureDepth final : public Texture {
public:
  TextureDepth(uint32_t width, uint32_t height,
               InternalFormat format = InternalFormat::DEPTH_COMPONENT32F)
    : Texture(width, height, 1, TextureTarget::TEXTURE_2D, format, false, MinFilter::NEAREST,
              MagFilter::NEAREST, WrapMode::CLAMP_TO_BORDER, WrapMode::CLAMP_TO_BORDER,
              WrapMode::CLAMP_TO_BORDER) {}
};

} // namespace Gloom

#endif // GLOOM_TEXTURE_2D_H