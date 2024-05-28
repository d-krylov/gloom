#include "texture.h"

namespace Gloom {

Texture::Texture(Types::TextureTarget target, Types::TextureInternalFormat internal_format,
                 int32_t width, int32_t height,
                 const Types::SamplerCreateInformation &sampler_ci)
  : target_(target), internal_format_(internal_format), size_(width, height) {
  glCreateTextures(static_cast<uint16_t>(target), 1, &texture_);
  CreateStorage();
  SetParameters(sampler_ci);
}

Texture::Texture(const Image &image)
  : Texture(Types::TextureTarget::TEXTURE_2D, image.GetFormat(), image.GetWidth(),
            image.GetHeight()) {
  SetData(image.GetData());
}

Texture::~Texture() { Destroy(); }

void Texture::Destroy() { glDeleteTextures(1, &texture_); }

void Texture::CreateStorage() {
  auto dimensions = Types::GetTextureDimensions(target_);
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

// clang-format off
void Texture::SetParameters(const Types::SamplerCreateInformation &sampler_ci) {
  glTextureParameteri(texture_, GL_TEXTURE_MIN_FILTER, static_cast<uint16_t>(sampler_ci.minifying_filter_));
  glTextureParameteri(texture_, GL_TEXTURE_MAG_FILTER, static_cast<uint16_t>(sampler_ci.magnification_filter_));
  glTextureParameteri(texture_, GL_TEXTURE_WRAP_S, static_cast<uint16_t>(sampler_ci.wrap_mode_[0]));
  glTextureParameteri(texture_, GL_TEXTURE_WRAP_T, static_cast<uint16_t>(sampler_ci.wrap_mode_[1]));
  glTextureParameteri(texture_, GL_TEXTURE_WRAP_R, static_cast<uint16_t>(sampler_ci.wrap_mode_[2]));

  glGenerateTextureMipmap(texture_);
}
// clang-format on

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