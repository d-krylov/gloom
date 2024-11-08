#include "texture_2d.h"
#include "core/include/image.h"

namespace Gloom {

Texture2D::Texture2D(const Image &image)
  : Texture(image.GetWidth(), image.GetHeight(), 1, TextureTarget::TEXTURE_2D, image.GetFormat(),
            true, MinFilter::LINEAR, MagFilter::LINEAR, WrapMode::CLAMP_TO_EDGE) {
  SetData(image.GetData());
}

Texture2D::Texture2D(uint32_t width, uint32_t height, InternalFormat format,
                     std::span<const std::byte> data)
  : Texture(width, height, 1, TextureTarget::TEXTURE_2D, format, false, MinFilter::LINEAR,
            MagFilter::LINEAR, WrapMode::CLAMP_TO_EDGE) {
  if (data.empty() == false) {
    SetData(data);
  }
}

Texture2DArray::Texture2DArray(uint32_t width, uint32_t height, uint32_t layers,
                               InternalFormat format, bool mipmap, MinFilter min, MagFilter mag)
  : Texture(width, height, layers, TextureTarget::TEXTURE_2D_ARRAY, format, mipmap, min, mag,
            WrapMode::CLAMP_TO_EDGE) {}

} // namespace Gloom