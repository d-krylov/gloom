#include "graphics/include/graphics_command.h"

namespace Gloom ::Command {

void ClearColor(Vector4f color) {
  glClearColor(color.r, color.g, color.b, color.a);
  glClear(GL_COLOR_BUFFER_BIT);
}

void ClearDepth(Vector4f depth) {
  glClearColor(depth.r, depth.g, depth.b, depth.a);
  glClear(GL_DEPTH_BUFFER_BIT);
}

void ClearStencil(Vector4f stencil) {
  glClearColor(stencil.r, stencil.g, stencil.b, stencil.a);
  glClear(GL_STENCIL_BUFFER_BIT);
}

void SetViewport(int32_t x, int32_t y, uint32_t width, uint32_t height) {
  glViewport(x, y, width, height);
}

void DrawArrays(int32_t first, uint32_t count, PrimitiveKind kind) {
  glDrawArrays(uint16_t(kind), first, count);
}

void DrawElements(uint32_t count, uint64_t offset, IndexType index, PrimitiveKind kind) {
  glDrawElements(uint16_t(kind), count, uint16_t(index), (void *)offset);
}

void DrawArraysInstanced(uint32_t indices_count, uint32_t instance_count, uint32_t first,
                         PrimitiveKind kind) {
  glDrawArraysInstanced(uint16_t(kind), first, indices_count, instance_count);
}

void DrawElementsBaseVertex(uint32_t count, int32_t base_vertex, std::byte *offset, IndexType index,
                            PrimitiveKind kind) {
  glDrawElementsBaseVertex(uint16_t(kind), count, uint16_t(index), offset, base_vertex);
}

void EnableBlending(bool b) { b ? glEnable(GL_BLEND) : glDisable(GL_BLEND); }
void EnableScissor(bool b) { b ? glEnable(GL_SCISSOR_TEST) : glDisable(GL_SCISSOR_TEST); }
void EnableDepthTest(bool b) { b ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST); }
void EnableMultisample(bool b) { b ? glEnable(GL_MULTISAMPLE) : glDisable(GL_MULTISAMPLE); }
void EnableStencilTest(bool b) { b ? glEnable(GL_STENCIL_TEST) : glDisable(GL_STENCIL_TEST); }
void EnableFaceCulling(bool b) { b ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE); }

void SetStencilFunction(ComparasionFunction function, int32_t reference, uint32_t mask) {
  glStencilFunc(uint16_t(function), reference, mask);
}

void SetScissor(int32_t x, int32_t y, uint32_t w, uint32_t h) { glScissor(x, y, w, h); }

void SetStencilOperation(StencilOperation fail, StencilOperation zfail, StencilOperation zpass) {
  glStencilOp(uint16_t(fail), uint16_t(zfail), uint16_t(zpass));
}

void SetBlendOperation(BlendOperation op) { glBlendEquation(uint16_t(op)); }

void SetBlendFunction(BlendFactor srgb, BlendFactor drgb, BlendFactor sa, BlendFactor da) {
  glBlendFuncSeparate(uint16_t(srgb), uint16_t(drgb), uint16_t(sa), uint16_t(da));
}

void SetPolygonMode(PolygonMode mode) {
  glPolygonMode(GL_FRONT_AND_BACK, static_cast<uint16_t>(mode));
}

void DispatchCompute(uint32_t groups_x, uint32_t groups_y, uint32_t groups_z) {
  glDispatchCompute(groups_x, groups_y, groups_z);
}

void MemoryBarrier(BarrierBit bb) { glMemoryBarrier(uint32_t(bb)); }

} // namespace Gloom::Command