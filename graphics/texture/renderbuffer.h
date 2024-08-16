#ifndef RENDERBUFFER_H
#define RENDERBUFFER_H

#include "graphics/include/graphics_types.h"

namespace Gloom {

class Renderbuffer {
public:
  Renderbuffer(TextureInternalFormat internal_format, int32_t width, int32_t height,
               uint32_t samples = 0);

  ~Renderbuffer();

  operator Handle() const { return renderbuffer_; }

  void Bind();

protected:
  void CreateStorage();

private:
  Handle renderbuffer_{0};
  TextureInternalFormat internal_format_;
  Vector2i size_;
  uint32_t samples_;
};

} // namespace Gloom

#endif // RENDERBUFFER_H