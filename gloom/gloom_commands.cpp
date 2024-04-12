#include "gloom_commands.h"

namespace Gloom ::Commands {

void Clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

void SetViewport(int32_t x, int32_t y, uint32_t width, uint32_t height) {
  glViewport(x, y, width, height);
}

void DrawArrays(Types::PrimitiveKind kind, int32_t first, uint32_t count) {
  glDrawArrays(static_cast<uint16_t>(kind), first, count);
}

void DrawElements(Types::PrimitiveKind kind, std::span<uint32_t> i) {
  glDrawElements(static_cast<uint16_t>(kind), i.size(), Types::Index, i.data());
}

void DrawElements(Types::PrimitiveKind kind, uint32_t count) {
  glDrawElements(static_cast<uint16_t>(kind), count, Types::Index, nullptr);
}

void EnableFaceCulling() {
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glFrontFace(GL_CCW);
}

void EnableDepthTesting() { glEnable(GL_DEPTH_TEST); }

} // namespace Gloom::Commands