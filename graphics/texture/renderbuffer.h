#ifndef RENDERBUFFER_H
#define RENDERBUFFER_H

#include "graphics_types.h"

namespace Gloom {

class Renderbuffer {
public:
  Renderbuffer();
  ~Renderbuffer();

private:
  Types::Handle renderbuffer_{0};
};

} // namespace Gloom

#endif // RENDERBUFFER_H