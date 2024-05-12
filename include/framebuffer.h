#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "graphics_types.h"

namespace Gloom {

class Framebuffer {
public:
  Framebuffer();

  ~Framebuffer();

  [[nodiscard]] Types::Handle GetHandle() const { return framebuffer_handle_; }

  void Bind();
  void Unbind();

protected:
  bool Verify();

private:
  Types::Handle framebuffer_handle_{0};
};

} // namespace Gloom

#endif // FRAMEBUFFER_H