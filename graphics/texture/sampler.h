#ifndef SAMPLER_H
#define SAMPLER_H

#include "graphics/include/graphics_types.h"

namespace Gloom {

class Sampler {
public:
  Sampler(TextureMagnificationFunction mag, TextureMinifyingFunction min, TextureWrapMode s,
          TextureWrapMode t, TextureWrapMode r);
  ~Sampler();

  void Bind(uint32_t unit);
  void Unbind(uint32_t unit);

  void SetParameters(TextureMagnificationFunction mag, TextureMinifyingFunction min,
                     TextureWrapMode s, TextureWrapMode t, TextureWrapMode r);

private:
  Handle sampler_{0};
};

} // namespace Gloom

#endif // SAMPLER_H