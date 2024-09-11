#ifndef GLOOM_RENDERBUFFER_H
#define GLOOM_RENDERBUFFER_H

#include "gloom/graphics/include/graphics_types.h"

namespace Gloom {

class Renderbuffer {
public:
  Renderbuffer(InternalFormat internal_format, uint32_t width, uint32_t height,
               uint32_t samples = 0);

  ~Renderbuffer();

  operator uint32_t() const { return renderbuffer_; }

  void Bind();

protected:
  void CreateStorage();

private:
  uint32_t renderbuffer_{0};
  InternalFormat format_;
  uint32_t width_;
  uint32_t height_;
  uint32_t samples_;
};

} // namespace Gloom

#endif // GLOOM_RENDERBUFFER_H