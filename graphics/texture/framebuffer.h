#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "renderbuffer.h"
#include "texture.h"

namespace Gloom {

struct FramebufferAttachment {
  FramebufferAttachment(FramebufferAttachmentType attachment_type, Texture *texture,
                        uint32_t texture_level = 0, uint32_t texture_layer = 0)
    : attachment_type_{attachment_type}, texture_level_{texture_level},
      texture_layer_{texture_layer}, texture_{texture} {}

  FramebufferAttachment(FramebufferAttachmentType attachment_type, Renderbuffer *renderbuffer)
    : attachment_type_{attachment_type}, renderbuffer_{renderbuffer} {}

  FramebufferAttachmentType attachment_type_;
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

  operator Handle() const { return framebuffer_; }

  void Bind();
  void Unbind();
  void Attach(const FramebufferAttachment &attachment);

  uint16_t GetStatus() const;

protected:
  bool Verify();

private:
  Handle framebuffer_{0};
};

} // namespace Gloom

#endif // FRAMEBUFFER_H