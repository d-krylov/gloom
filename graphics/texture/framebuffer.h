#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "graphics_types.h"
#include "texture.h"

namespace Gloom {

class Framebuffer {
public:
  Framebuffer();

  ~Framebuffer();

  operator Types::Handle() const { return framebuffer_; }

  void Bind();
  void Unbind();

  void Attach(const Texture &texture);

protected:
  bool Verify();

private:
  Types::Handle framebuffer_{0};
};

} // namespace Gloom

#endif // FRAMEBUFFER_H