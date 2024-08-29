#include "renderbuffer.h"

namespace Gloom {

Renderbuffer::Renderbuffer(InternalFormat internal_format, int32_t width, int32_t height,
                           uint32_t samples)
  : internal_format_(internal_format), size_(width, height), samples_(samples) {
  glCreateRenderbuffers(1, &renderbuffer_);
  CreateStorage();
}

Renderbuffer::~Renderbuffer() { glDeleteRenderbuffers(1, &renderbuffer_); }

void Renderbuffer::CreateStorage() {
  glNamedRenderbufferStorageMultisample(renderbuffer_, samples_,
                                        static_cast<uint16_t>(internal_format_), size_.x, size_.y);
}

void Renderbuffer::Bind() { glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer_); }

} // namespace Gloom