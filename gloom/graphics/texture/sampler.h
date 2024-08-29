#ifndef GLOOM_SAMPLER_H
#define GLOOM_SAMPLER_H

#include "gloom/graphics/include/graphics_types.h"

namespace Gloom {

class Sampler {
public:
  Sampler(MagFilter mag, MinFilter min, WrapMode s, WrapMode t, WrapMode r);
  ~Sampler();

  void Bind(uint32_t unit);
  void Unbind(uint32_t unit);

  void SetParameters(MagFilter mag, MinFilter min, WrapMode s, WrapMode t, WrapMode r);

private:
  uint32_t sampler_{0};
};

} // namespace Gloom

#endif // GLOOM_SAMPLER_H