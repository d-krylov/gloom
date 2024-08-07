#include "commands.h"

namespace Gloom ::Commands {

void Clear(bool depth) { glClear(GL_COLOR_BUFFER_BIT | (depth ? GL_DEPTH_BUFFER_BIT : 0)); }

void SetViewport(int32_t x, int32_t y, uint32_t width, uint32_t height) {
  glViewport(x, y, width, height);
}

void DrawElements(PrimitiveKind kind, uint32_t count) {
  glDrawElements(static_cast<uint16_t>(kind), count, Index, nullptr);
}

void DrawElementsBaseVertex(PrimitiveKind kind, uint32_t count, CoreType index_type,
                            uint64_t offset, int32_t base_vertex) {
  glDrawElementsBaseVertex(static_cast<uint16_t>(kind), count,
                           static_cast<uint16_t>(index_type), reinterpret_cast<void *>(offset),
                           base_vertex);
}

void SetMultisample(bool b) { b ? glEnable(GL_MULTISAMPLE) : glDisable(GL_MULTISAMPLE); }

void SetFaceCulling(bool b) {
  b ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glFrontFace(GL_CCW);
}

void DrawArrays(int32_t first, uint32_t count, PrimitiveKind kind) {
  glDrawArrays(static_cast<uint16_t>(kind), first, count);
}

void DrawArraysInstanced(PrimitiveKind kind, int32_t first, uint32_t count,
                         uint32_t instance_count) {
  glDrawArraysInstanced(static_cast<uint16_t>(kind), first, count, instance_count);
}

void DrawArraysIndirect(uint32_t count, PrimitiveKind kind, uint32_t stride) {
  glMultiDrawArraysIndirect(static_cast<uint16_t>(kind), nullptr, count, stride);
}

void SetPrimitiveRestart(bool b) {
  b ? glEnable(GL_PRIMITIVE_RESTART) : glDisable(GL_PRIMITIVE_RESTART);
}

void SetStencilTesting(bool b, const StencilInformation &stencil_information) {
  b ? glEnable(GL_STENCIL_TEST) : glDisable(GL_STENCIL_TEST);
  if (b) {
    glStencilFunc(static_cast<uint16_t>(stencil_information.funtion_),
                  stencil_information.reference_, stencil_information.mask_);
    glStencilOp(static_cast<uint16_t>(stencil_information.fail_),
                static_cast<uint16_t>(stencil_information.zfail_),
                static_cast<uint16_t>(stencil_information.zpass_));
  }
}

void SetDepthTesting(bool b) { b ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST); }

void SetScissor(bool b, const Vector4i &scissor) {
  b ? glEnable(GL_SCISSOR_TEST) : glDisable(GL_SCISSOR_TEST);
  if (b) {
    glScissor(scissor.x, scissor.y, scissor.z, scissor.w);
  }
}

void SetBlending(bool b, const BlendInformation &bi) {
  b ? glEnable(GL_BLEND) : glDisable(GL_BLEND);
  if (b) {
    glBlendEquation(static_cast<uint16_t>(bi.equation_));
    glBlendFuncSeparate(
      static_cast<uint16_t>(bi.source_rgb_), static_cast<uint16_t>(bi.destination_rgb_),
      static_cast<uint16_t>(bi.source_alpha_), static_cast<uint16_t>(bi.destination_alpha_));
  }
}

void SetPolygonMode(PolygonMode mode) {
  glPolygonMode(GL_FRONT_AND_BACK, static_cast<uint16_t>(mode));
}

void DispatchCompute(uint32_t groups_x, uint32_t groups_y, uint32_t groups_z) {
  glDispatchCompute(groups_x, groups_y, groups_z);
}

void MemoryBarrier(BarrierBit bb) { glMemoryBarrier(uint32_t(bb)); }

} // namespace Gloom::Commands