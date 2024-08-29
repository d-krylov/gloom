#include "texture.h"

namespace Gloom {

Texture::Texture(int32_t width, int32_t height, int32_t depth, TextureTarget target,
                 InternalFormat format, bool mipmap, MinFilter min, MagFilter mag, WrapMode s,
                 WrapMode t, WrapMode r)
  : size_(width, height, depth), target_(target), format_(format) {
  glCreateTextures(uint16_t(target_), 1, &texture_);
  CreateStorage();
  if (mipmap == true) {
    glGenerateTextureMipmap(texture_);
  }
}

Texture::Texture(Texture &&other) noexcept
  : texture_{std::exchange(other.texture_, 0)}, target_(other.target_), format_(other.format_),
    size_(other.size_) {}

Texture::~Texture() { glDeleteTextures(1, &texture_); }

void Texture::CreateStorage() {
  auto dimensions = GetTextureDimensions(target_);
  switch (dimensions) {
  case 1:
    glTextureStorage1D(texture_, 1, uint16_t(format_), size_.x);
    break;
  case 2:
    glTextureStorage2D(texture_, 1, uint16_t(format_), size_.x, size_.y);
    break;
  case 3:
    glTextureStorage3D(texture_, 0, uint16_t(format_), size_.x, size_.y, size_.z);
    break;
  default:
    break;
  }
}

void Texture::SetData(std::span<const std::byte> data, int32_t x, int32_t y, int32_t z) {
  auto ft = GetPixelFormatAndType(format_);
  auto format = uint16_t(ft.first);
  auto type = uint16_t(ft.second);
  auto d = (target_ == TextureTarget::TEXTURE_CUBE_MAP) ? 3 : GetTextureDimensions(target_);
  switch (d) {
  case 1:
    glTextureSubImage1D(texture_, 0, 0, size_.x, format, type, data.data());
    break;
  case 2:
    glTextureSubImage2D(texture_, 0, x, y, size_.x, size_.y, format, type, data.data());
    break;
  case 3:
    glTextureSubImage3D(texture_, 0, x, y, z, size_.x, size_.y, size_.z, format, type, data.data());
    break;
  default:
    break;
  }
}

void Texture::SetParameters(MagFilter mag, MinFilter min, WrapMode s, WrapMode t, WrapMode r) {
  glTextureParameteri(texture_, GL_TEXTURE_MIN_FILTER, uint16_t(min));
  glTextureParameteri(texture_, GL_TEXTURE_MAG_FILTER, uint16_t(mag));
  glTextureParameteri(texture_, GL_TEXTURE_WRAP_S, uint16_t(s));
  glTextureParameteri(texture_, GL_TEXTURE_WRAP_T, uint16_t(t));
  glTextureParameteri(texture_, GL_TEXTURE_WRAP_R, uint16_t(r));
}

void Texture::Bind(std::size_t unit) { glBindTextureUnit(unit, texture_); }

uint64_t Texture::GetHandleARB() const { return glGetTextureHandleARB(texture_); }

void Texture::BindImage(uint32_t unit, int32_t level, bool layered, uint32_t layer, Access access) {
  glBindImageTexture(unit, texture_, level, layered, layer, uint16_t(access), uint16_t(format_));
}

} // namespace Gloom