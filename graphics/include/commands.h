#ifndef GLOOM_COMMANDS_H
#define GLOOM_COMMANDS_H

#include "graphics_types.h"
#include <span>

namespace Gloom ::Commands {

struct BlendInformation {
  BlendEquation equation_;
  BlendFunctionSeparate source_rgb_;
  BlendFunctionSeparate destination_rgb_;
  BlendFunctionSeparate source_alpha_;
  BlendFunctionSeparate destination_alpha_;
};

struct StencilInformation {
  StencilFunction funtion_;
  StencilOption fail_;
  StencilOption zfail_;
  StencilOption zpass_;
  int32_t reference_;
  uint32_t mask_;
};

// clang-format off
void SetStencilTesting(bool b, const StencilInformation &stencil_information = StencilInformation{});
void SetBlending(bool b, const BlendInformation &blend_information = BlendInformation{});
void SetPolygonMode(PolygonMode = PolygonMode::FILL);
void SetScissor(bool b, const Vector4i &scissor = Vector4i{});
void SetPrimitiveRestart(bool b);
void DrawArrays(int32_t first, uint32_t count, PrimitiveKind kind = PrimitiveKind::TRIANGLES);
void DrawArraysInstanced(PrimitiveKind kind, int32_t first, uint32_t count, uint32_t instance_count);
void DrawArraysIndirect(uint32_t count, PrimitiveKind kind = PrimitiveKind::TRIANGLES, uint32_t stride = 0);

void Clear(bool depth = false);
void SetMultisample(bool b);
void SetFaceCulling(bool b);
void SetDepthTesting(bool b);
void SetViewport(int32_t x, int32_t y, uint32_t width, uint32_t height);

void DrawElements(PrimitiveKind kind, uint32_t count);

 


void DrawElementsBaseVertex(PrimitiveKind kind, uint32_t count, CoreType index_type, uint64_t offset, int32_t base_vertex);
// clang-format on

} // namespace Gloom::Commands

#endif // GLOOM_COMMANDS_H