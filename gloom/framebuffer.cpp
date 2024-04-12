#include "framebuffer.h"

namespace Gloom {

Framebuffer::Framebuffer() { glCreateFramebuffers(1, &framebuffer_handle_); }

void Framebuffer::Bind() {
  glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_handle_);
}

void Framebuffer::Unbind() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

} // namespace Gloom