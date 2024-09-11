#include "renderbuffer.h"

namespace Gloom {

Renderbuffer::Renderbuffer(InternalFormat format, uint32_t width, uint32_t height, uint32_t samples)
  : format_(format), width_(width), height_(height), samples_(samples) {
  glCreateRenderbuffers(1, &renderbuffer_);
  CreateStorage();
}

Renderbuffer::~Renderbuffer() { glDeleteRenderbuffers(1, &renderbuffer_); }

void Renderbuffer::CreateStorage() {
  glNamedRenderbufferStorageMultisample(renderbuffer_, samples_, uint16_t(format_), width_,
                                        height_);
}

void Renderbuffer::Bind() { glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer_); }

} // namespace Gloom