#include "framebuffer.h"

namespace Gloom {

Framebuffer::Framebuffer() { glCreateFramebuffers(1, &framebuffer_); }

bool Framebuffer::Verify() {
  auto status = glCheckNamedFramebufferStatus(framebuffer_, GL_FRAMEBUFFER);
  return status = GL_FRAMEBUFFER_COMPLETE;
}

void Framebuffer::Attach(const Texture &texture) {
  if (texture.IsLayered()) {
    // glNamedFramebufferTextureLayer(framebuffer_, );
  } else {
    glNamedFramebufferTexture(framebuffer_, GL_COLOR_ATTACHMENT0, texture, 0);
  }
  Verify();
}

void Framebuffer::Bind() { glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_); }

void Framebuffer::Unbind() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

} // namespace Gloom