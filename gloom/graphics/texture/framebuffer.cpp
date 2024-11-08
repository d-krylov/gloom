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
  auto level = attachment.level_;
  auto layer = attachment.layer_;
  auto type = uint16_t(attachment.type_);
  if (attachment.texture_ != nullptr) {
    if (attachment.texture_->IsLayered()) {
      glNamedFramebufferTextureLayer(framebuffer_, type, *attachment.texture_, level, layer);
    } else {
      glNamedFramebufferTexture(framebuffer_, type, *attachment.texture_, level);
    }
  } else if (attachment.renderbuffer_ != nullptr) {
    glNamedFramebufferRenderbuffer(framebuffer_, type, GL_RENDERBUFFER, *attachment.renderbuffer_);
  }

  CORE_VERIFY(GetStatus());
}

void Framebuffer::Bind() { glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_); }

void Framebuffer::Unbind() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

} // namespace Gloom