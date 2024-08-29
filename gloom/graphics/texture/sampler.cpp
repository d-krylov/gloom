#include "sampler.h"

namespace Gloom {

Sampler::Sampler(MagFilter mag, MinFilter min, WrapMode s, WrapMode t, WrapMode r) {
  glCreateSamplers(1, &sampler_);
}

Sampler::~Sampler() { glDeleteSamplers(1, &sampler_); }

void Sampler::Bind(uint32_t unit) { glBindSampler(unit, sampler_); }
void Sampler::Unbind(uint32_t unit) { glBindSampler(unit, 0); }

void Sampler::SetParameters(MagFilter mag, MinFilter min, WrapMode s, WrapMode t, WrapMode r) {
  glTextureParameteri(sampler_, GL_TEXTURE_MIN_FILTER, uint16_t(min));
  glTextureParameteri(sampler_, GL_TEXTURE_MAG_FILTER, uint16_t(mag));
  glTextureParameteri(sampler_, GL_TEXTURE_WRAP_S, uint16_t(s));
  glTextureParameteri(sampler_, GL_TEXTURE_WRAP_T, uint16_t(t));
  glTextureParameteri(sampler_, GL_TEXTURE_WRAP_R, uint16_t(r));
}

} // namespace Gloom