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

void DrawElementsBaseVertex(Types::PrimitiveKind kind, uint32_t count,
                            Types::CoreType index_type, uint64_t offset,
                            int32_t base_vertex) {
  glDrawElementsBaseVertex(static_cast<uint16_t>(kind), count,
                           static_cast<uint16_t>(index_type),
                           reinterpret_cast<void *>(offset), base_vertex);
}

void SetFaceCulling(bool b) {
  b ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glFrontFace(GL_CCW);
}

void SetStencilTesting(bool b) {
  b ? glEnable(GL_STENCIL_TEST) : glDisable(GL_STENCIL_TEST);
}

void SetDepthTesting(bool b) {
  b ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
}

void SetBlending(bool b, Types::BlendEquation equation,
                 Types::BlendFunctionSeparate source_rgb,
                 Types::BlendFunctionSeparate destination_rgb,
                 Types::BlendFunctionSeparate source_alpha,
                 Types::BlendFunctionSeparate destination_alpha) {
  b ? glEnable(GL_BLEND) : glDisable(GL_BLEND);
  if (b) {
    glBlendEquation(static_cast<uint16_t>(equation));
    glBlendFuncSeparate(static_cast<uint16_t>(source_rgb),
                        static_cast<uint16_t>(destination_rgb),
                        static_cast<uint16_t>(source_alpha),
                        static_cast<uint16_t>(destination_alpha));
  }
}

} // namespace Gloom::Commands