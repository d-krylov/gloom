#include "texture.h"

namespace Gloom {

Texture::Texture(const TextureDescription &description)
  : target_(description.target_), internal_format_(description.format_),
    size_(description.size_.xy()) {
  glCreateTextures(static_cast<uint16_t>(target_), 1, &texture_);
  CreateStorage();
  SetParameters(description.sampler_ci_);
}

Texture::Texture(const Image &image)
  : Texture{TextureDescription{.size_ = Vector3i(image.GetSize(), 0),
                               .target_ = TextureTarget::TEXTURE_2D,
                               .format_ = image.GetFormat()}} {
  SetData(image.GetData());
}

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

uint64_t Texture::GetHandleARB() const { return glGetTextureHandleARB(texture_); }

// clang-format off
void Texture::SetParameters(const SamplerCreateInformation &sampler_ci) {
  glTextureParameteri(texture_, GL_TEXTURE_MIN_FILTER, static_cast<uint16_t>(sampler_ci.minifying_filter_));
  glTextureParameteri(texture_, GL_TEXTURE_MAG_FILTER, static_cast<uint16_t>(sampler_ci.magnification_filter_));
  glTextureParameteri(texture_, GL_TEXTURE_WRAP_S, static_cast<uint16_t>(sampler_ci.wrap_mode_[0]));
  glTextureParameteri(texture_, GL_TEXTURE_WRAP_T, static_cast<uint16_t>(sampler_ci.wrap_mode_[1]));
  glTextureParameteri(texture_, GL_TEXTURE_WRAP_R, static_cast<uint16_t>(sampler_ci.wrap_mode_[2]));

  glGenerateTextureMipmap(texture_);
}
// clang-format on

void Texture::SetData(std::span<const std::byte> data) {
  auto format_type = GetPixelFormatAndType(internal_format_);
  auto dimensions = GetTextureDimensions(target_);

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