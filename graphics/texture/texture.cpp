#include "texture.h"

namespace Gloom {

Texture::Texture(TextureTarget target, TextureInternalFormat format, int32_t w, int32_t h,
                 int32_t depth, uint32_t samples, TextureMagnificationFunction mag,
                 TextureMinifyingFunction min, TextureWrapMode s, TextureWrapMode t,
                 TextureWrapMode r)
  : target_(target), internal_format_(format), size_(w, h), depth_(depth) {
  glCreateTextures(static_cast<uint16_t>(target_), 1, &texture_);
  CreateStorage();
  SetParameters(mag, min, s, t, r);
}

Texture::Texture(const Image &image)
  : Texture(TextureTarget::TEXTURE_2D, image.GetFormat(), image.GetWidth(),
            image.GetHeight()) {
  SetData(image.GetData());
}

Texture::Texture(const CubeMap &cubemap)
  : Texture(TextureTarget::TEXTURE_CUBE_MAP, cubemap.GetFormat(), cubemap.GetWidth(),
            cubemap.GetHeight()) {
  for (int32_t i = 0; i < 6; ++i) {
    auto data = cubemap.GetData(i);
    SetData(data, 0, 0, i);
  }
}

Texture::Texture(Texture &&other) noexcept
  : texture_{std::exchange(other.texture_, 0)}, target_(other.target_),
    internal_format_(other.internal_format_), size_(other.size_), depth_(other.depth_) {}

Texture::~Texture() { Destroy(); }

void Texture::Destroy() { glDeleteTextures(1, &texture_); }

void Texture::CreateStorage() {
  auto dimensions = GetTextureDimensions(target_);
  auto format = static_cast<uint16_t>(internal_format_);
  switch (dimensions) {
  case 1:
    glTextureStorage1D(texture_, 1, format, size_.x);
    break;
  case 2:
    glTextureStorage2D(texture_, 1, format, size_.x, size_.y);
    break;
  case 3:
    glTextureStorage3D(texture_, 0, format, size_.x, size_.y, depth_);
    break;
  default:
    break;
  }
}

void Texture::BindImage(uint32_t unit, int32_t level, bool layered, uint32_t layer,
                        Access access) {
  glBindImageTexture(unit, texture_, level, layered, layer, uint16_t(access),
                     uint16_t(internal_format_));
}

uint64_t Texture::GetHandleARB() const { return glGetTextureHandleARB(texture_); }

void Texture::SetParameters(TextureMagnificationFunction mag, TextureMinifyingFunction min,
                            TextureWrapMode s, TextureWrapMode t, TextureWrapMode r) {
  glTextureParameteri(texture_, GL_TEXTURE_MIN_FILTER, uint16_t(min));
  glTextureParameteri(texture_, GL_TEXTURE_MAG_FILTER, uint16_t(mag));
  glTextureParameteri(texture_, GL_TEXTURE_WRAP_S, uint16_t(s));
  glTextureParameteri(texture_, GL_TEXTURE_WRAP_T, uint16_t(t));
  glTextureParameteri(texture_, GL_TEXTURE_WRAP_R, uint16_t(r));

  glGenerateTextureMipmap(texture_);
}

void Texture::SetData(std::span<const std::byte> data, int32_t xoffset, int32_t yoffset,
                      int32_t zoffset) {
  auto format_type = GetPixelFormatAndType(internal_format_);
  auto dimensions =
    (target_ == TextureTarget::TEXTURE_CUBE_MAP) ? 3 : GetTextureDimensions(target_);

  switch (dimensions) {
  case 1:
    glTextureSubImage1D(texture_, 0, 0, size_.x, static_cast<uint16_t>(format_type.first),
                        static_cast<uint16_t>(format_type.second), data.data());
    break;
  case 2:
    glTextureSubImage2D(texture_, 0, xoffset, yoffset, size_.x, size_.y,
                        static_cast<uint16_t>(format_type.first),
                        static_cast<uint16_t>(format_type.second), data.data());
    break;
  case 3:
    glTextureSubImage3D(texture_, 0, xoffset, yoffset, zoffset, size_.x, size_.y, 1,
                        static_cast<uint16_t>(format_type.first),
                        static_cast<uint16_t>(format_type.second), data.data());
    break;
  default:
    break;
  }
}

void Texture::Bind(std::size_t unit) { glBindTextureUnit(unit, texture_); }

} // namespace Gloom