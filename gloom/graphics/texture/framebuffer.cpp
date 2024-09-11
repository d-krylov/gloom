#include "framebuffer.h"
#include "renderbuffer.h"
#include "texture.h"
#include <iostream>

namespace Gloom {

Framebuffer::Framebuffer() { glCreateFramebuffers(1, &framebuffer_); }

Framebuffer::~Framebuffer() { glDeleteFramebuffers(1, &framebuffer_); }

uint16_t Framebuffer::GetStatus() const {
  return glCheckNamedFramebufferStatus(framebuffer_, GL_FRAMEBUFFER);
}

void Framebuffer::Attach(const FramebufferAttachment &attachment) {
  if (attachment.texture_ != nullptr) {
    if (attachment.texture_->IsLayered()) {
      glNamedFramebufferTextureLayer(framebuffer_, uint16_t(attachment.type_), *attachment.texture_,
                                     attachment.level_, attachment.layer_);
    } else {
      glNamedFramebufferTexture(framebuffer_, uint16_t(attachment.type_), *attachment.texture_,
                                attachment.level_);
    }
  } else if (attachment.renderbuffer_ != nullptr) {
    glNamedFramebufferRenderbuffer(framebuffer_, uint16_t(attachment.type_), GL_RENDERBUFFER,
                                   *attachment.renderbuffer_);
  }

  CORE_VERIFY(GetStatus());
}

void Framebuffer::Bind() { glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_); }

void Framebuffer::Unbind() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

} // namespace Gloom