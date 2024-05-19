#include "renderbuffer.h"

namespace Gloom {

Renderbuffer::Renderbuffer() { glCreateRenderbuffers(1, &renderbuffer_); }

Renderbuffer::~Renderbuffer() { glDeleteRenderbuffers(1, &renderbuffer_); }

} // namespace Gloom