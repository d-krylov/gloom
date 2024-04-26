#ifndef RENDERBUFFER_H
#define RENDERBUFFER_H

#include "gloom_types.h"

namespace Gloom {

class Renderbuffer {
public:
  Renderbuffer();
  ~Renderbuffer();

private:
  Types::Handle renderbuffer_handle_{0};
};

} // namespace Gloom

#endif // RENDERBUFFER_H