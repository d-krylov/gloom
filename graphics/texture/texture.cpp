#include "texture.h"

namespace Gloom {

Texture::Texture(Types::TextureTarget target, Types::TextureInternalFormat internal_format,
                 int32_t width, int32_t height)
  : target_(target), internal_format_(internal_format), size_(width, height) {
  glCreateTextures(static_cast<uint16_t>(target), 1, &texture_);
  CreateStorage();
  SetParameters();
}

Texture::~Texture() { Destroy(); }

void Texture::Destroy() { glDeleteTextures(1, &texture_); }

void Texture::CreateStorage() {
  auto dimensions = Types::GetTextureDimensions(target_);
  auto format = static_cast<uint16_t>(internal_format_);
  switch (dimensions) {
  case 1:
    glTextureStorage1D(texture_, 1, format, size_.x);
  case 2:
    glTextureStorage2D(texture_, 1, format, size_.x, size_.y);
  case 3:

  case 4:

  default:
    break;
  }
}

void Texture::SetParameters() {
  glTextureParameteri(texture_, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTextureParameteri(texture_, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTextureParameteri(texture_, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTextureParameteri(texture_, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTextureParameteri(texture_, GL_TEXTURE_WRAP_R, GL_REPEAT);
}

void Texture::SetData(std::span<const std::byte> data) {
  auto format_type = Types::GetPixelFormatAndType(internal_format_);
  auto dimensions = Types::GetTextureDimensions(target_);

  switch (dimensions) {
  case 1:
    glTextureSubImage1D(texture_, 0, 0, size_.x, static_cast<uint16_t>(format_type.first),
                        static_cast<uint16_t>(format_type.second), data.data());
    break;
  case 2:
    glTextureSubImage2D(texture_, 0, 0, 0, size_.x, size_.y,
                        static_cast<uint16_t>(format_type.first),
                        static_cast<uint16_t>(format_type.second), data.data());
    break;
  case 3:
    break;
  default:
    break;
  }
}

void Texture::Bind(std::size_t unit) { glBindTextureUnit(unit, texture_); }

} // namespace Gloom