#ifndef GLOOM_FRAMEBUFFER_H
#define GLOOM_FRAMEBUFFER_H

#include "gloom/graphics/include/graphics_types.h"

namespace Gloom {

class Texture;
class Renderbuffer;

struct FramebufferAttachment {
  FramebufferAttachment(AttachmentType type, Texture *texture, uint32_t texture_level = 0,
                        uint32_t texture_layer = 0)
    : type_{type}, texture_level_{texture_level}, texture_layer_{texture_layer}, texture_{texture} {
  }

  FramebufferAttachment(AttachmentType type, Renderbuffer *renderbuffer)
    : type_{type}, renderbuffer_{renderbuffer} {}

  AttachmentType type_;
  uint32_t texture_level_{0};
  uint32_t texture_layer_{0};
  Texture *texture_{nullptr};
  Renderbuffer *renderbuffer_{nullptr};
};

class Framebuffer {
public:
  Framebuffer();

  ~Framebuffer();

  NO_COPY_SEMANTIC(Framebuffer);

  operator uint32_t() const { return framebuffer_; }

  void Bind();
  void Unbind();
  void Attach(const FramebufferAttachment &attachment);

  uint16_t GetStatus() const;

protected:
  bool Verify();

private:
  uint32_t framebuffer_{0};
};

} // namespace Gloom

#endif // GLOOM_FRAMEBUFFER_H