#include "framebuffer.h"
#include <iostream>

namespace Gloom {

Framebuffer::Framebuffer() { glCreateFramebuffers(1, &framebuffer_); }

Framebuffer::~Framebuffer() { glDeleteFramebuffers(1, &framebuffer_); }

uint16_t Framebuffer::GetStatus() const {
  return glCheckNamedFramebufferStatus(framebuffer_, GL_FRAMEBUFFER);
}

void Framebuffer::Attach(const FramebufferAttachment &attachment) {
  auto attachment_type = static_cast<uint16_t>(attachment.attachment_type_);
  if (attachment.texture_ != nullptr) {
    if (attachment.texture_->IsLayered()) {
      glNamedFramebufferTextureLayer(framebuffer_, attachment_type, *attachment.texture_,
                                     attachment.texture_level_, attachment.texture_layer_);
    } else {
      glNamedFramebufferTexture(framebuffer_, attachment_type, *attachment.texture_,
                                attachment.texture_level_);
    }
  } else if (attachment.renderbuffer_ != nullptr) {
    glNamedFramebufferRenderbuffer(framebuffer_, attachment_type, GL_RENDERBUFFER,
                                   *attachment.renderbuffer_);
  }
  CORE_VERIFY(GetStatus() == GL_FRAMEBUFFER_COMPLETE);
}

void Framebuffer::Bind() { glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_); }

void Framebuffer::Unbind() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

} // namespace Gloom