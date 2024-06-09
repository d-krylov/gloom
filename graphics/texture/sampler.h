#ifndef SAMPLER_H
#define SAMPLER_H

#include "graphics_types.h"

namespace Gloom {

class Sampler {
public:
  Sampler(const SamplerCreateInformation &sampler_ci);
  ~Sampler();

  void Bind(uint32_t unit);
  void Unbind(uint32_t unit);

  void SetParameters(const SamplerCreateInformation &sampler_ci);

private:
  Handle sampler_{0};
};

} // namespace Gloom

#endif // SAMPLER_H