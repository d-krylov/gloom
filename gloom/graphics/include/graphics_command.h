#ifndef GLOOM_GRAPHICS_COMMAND_H
#define GLOOM_GRAPHICS_COMMAND_H

#include "graphics_types.h"
#include <span>

namespace Gloom ::Command {

void Clear(bool color, bool depth = false, bool stencil = false);

void DrawArrays(int32_t first, uint32_t count, PrimitiveKind kind = PrimitiveKind::TRIANGLES);
void DrawElements(uint32_t count, uint64_t offset = 0, IndexType index = IndexType::UNSIGNED_INT,
                  PrimitiveKind kind = PrimitiveKind::TRIANGLES);

void DrawArraysInstanced(uint32_t indices_count, uint32_t instance_count, uint32_t first = 0,
                         PrimitiveKind kind = PrimitiveKind::TRIANGLES);

void DrawElementsBaseVertex(uint32_t count, int32_t base_vertex, std::byte *offset,
                            IndexType index = IndexType::UNSIGNED_INT,
                            PrimitiveKind kind = PrimitiveKind::TRIANGLES);

void EnableBlending(bool b);
void EnableScissor(bool b);
void EnableDepthTest(bool b);
void EnableMultisample(bool b);
void EnableStencilTest(bool b);
void EnableFaceCulling(bool b);
void SetScissor(int32_t x, int32_t y, uint32_t w, uint32_t h);
void SetStencilFunction(ComparasionFunction function, int32_t reference, uint32_t mask);
void SetStencilOperation(StencilOperation fail, StencilOperation zfail, StencilOperation zpass);
void SetBlendOperation(BlendOperation op);
void SetBlendFunction(BlendFactor srgb, BlendFactor drgb, BlendFactor sa, BlendFactor da);
void SetViewport(int32_t x, int32_t y, uint32_t width, uint32_t height);

void DispatchCompute(uint32_t groups_x, uint32_t groups_y, uint32_t groups_z);
void MemoryBarrier(BarrierBit bb);

ClipOrigin GetClipOrigin();

} // namespace Gloom::Command

#endif // GLOOM_GRAPHICS_COMMAND_H