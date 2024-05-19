#ifndef SAMPLER_H
#define SAMPLER_H

#include "graphics_types.h"

namespace Gloom {

class Sampler {
public:
  Sampler();
  ~Sampler();

  void Bind(uint32_t unit);

  void SetParameters();

private:
  Types::Handle sampler_{0};
};

} // namespace Gloom

#endif // SAMPLER_H