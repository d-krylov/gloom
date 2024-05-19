#include "sampler.h"

namespace Gloom {

Sampler::Sampler() { glCreateSamplers(1, &sampler_); }

Sampler::~Sampler() { glDeleteSamplers(1, &sampler_); }

void Sampler::Bind(uint32_t unit) { glBindSampler(unit, sampler_); }

void Sampler::SetParameters() {}

} // namespace Gloom