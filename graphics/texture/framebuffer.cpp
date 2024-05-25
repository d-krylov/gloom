#include "framebuffer.h"

namespace Gloom {

Framebuffer::Framebuffer() { glCreateFramebuffers(1, &framebuffer_); }

bool Framebuffer::Verify() {
  auto status = glCheckNamedFramebufferStatus(framebuffer_, GL_FRAMEBUFFER);
  return status = GL_FRAMEBUFFER_COMPLETE;
}

void Framebuffer::Attach(const FramebufferAttachment &attachment) {}

void Framebuffer::Bind() { glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_); }

void Framebuffer::Unbind() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

} // namespace Gloom