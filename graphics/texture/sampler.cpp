#include "sampler.h"

namespace Gloom {

Sampler::Sampler(const SamplerCreateInformation &sampler_ci) {
  glCreateSamplers(1, &sampler_);
}

Sampler::~Sampler() { glDeleteSamplers(1, &sampler_); }

void Sampler::Bind(uint32_t unit) { glBindSampler(unit, sampler_); }
void Sampler::Unbind(uint32_t unit) { glBindSampler(unit, 0); }

// clang-format off
void Sampler::SetParameters(const SamplerCreateInformation &sampler_ci) {
  glSamplerParameterf(sampler_, GL_TEXTURE_MIN_FILTER, static_cast<uint16_t>(sampler_ci.minifying_filter_));
  glSamplerParameterf(sampler_, GL_TEXTURE_MAG_FILTER, static_cast<uint16_t>(sampler_ci.magnification_filter_));
  glSamplerParameterf(sampler_, GL_TEXTURE_WRAP_S, static_cast<uint16_t>(sampler_ci.wrap_mode_[0]));
  glSamplerParameterf(sampler_, GL_TEXTURE_WRAP_T, static_cast<uint16_t>(sampler_ci.wrap_mode_[1]));
  glSamplerParameterf(sampler_, GL_TEXTURE_WRAP_R, static_cast<uint16_t>(sampler_ci.wrap_mode_[2]));
  glSamplerParameterf(sampler_, GL_TEXTURE_COMPARE_FUNC, static_cast<uint16_t>(sampler_ci.compare_function_));
}
// clang-format on

} // namespace Gloom