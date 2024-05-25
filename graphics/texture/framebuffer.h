#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "graphics_types.h"
#include "renderbuffer.h"
#include "texture.h"

namespace Gloom {

struct FramebufferAttachment {
  Types::FramebufferAttachmentType attachment_type_;
  uint32_t attachment_index_{0};
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

  operator Types::Handle() const { return framebuffer_; }

  void Bind();
  void Unbind();

  void Attach(const FramebufferAttachment &attachment);

protected:
  bool Verify();

private:
  Types::Handle framebuffer_{0};
};

} // namespace Gloom

#endif // FRAMEBUFFER_H