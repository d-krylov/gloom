#ifndef GLOOM_COMMANDS_H
#define GLOOM_COMMANDS_H

#include "graphics_types.h"
#include <span>

namespace Gloom ::Commands {

struct BlendInformation {
  Types::BlendEquation equation_;
  Types::BlendFunctionSeparate source_rgb_;
  Types::BlendFunctionSeparate destination_rgb_;
  Types::BlendFunctionSeparate source_alpha_;
  Types::BlendFunctionSeparate destination_alpha_;
};

struct StencilInformation {
  Types::StencilFunction funtion_;
  Types::StencilOption fail_;
  Types::StencilOption zfail_;
  Types::StencilOption zpass_;
  int32_t reference_;
  uint32_t mask_;
};

// clang-format off
void SetStencilTesting(bool b, const StencilInformation &stencil_information = StencilInformation{});
void SetBlending(bool b, const BlendInformation &blend_information = BlendInformation{});
void SetPolygonMode(Types::PolygonMode = Types::PolygonMode::FILL);
void SetScissor(bool b, const Types::Vector4i &scissor = Types::Vector4i{});
void SetPrimitiveRestart(bool b);
void DrawArrays(Types::PrimitiveKind kind, int32_t first, uint32_t count);
void DrawArraysInstanced(Types::PrimitiveKind kind, int32_t first, uint32_t count, uint32_t instance_count);
void DrawArraysIndirect(uint32_t count, Types::PrimitiveKind kind = Types::PrimitiveKind::TRIANGLES, uint32_t stride = 0);

void Clear();
void SetFaceCulling(bool b);
void SetDepthTesting(bool b);
void SetViewport(int32_t x, int32_t y, uint32_t width, uint32_t height);

void DrawElements(Types::PrimitiveKind kind, uint32_t count);

 


void DrawElementsBaseVertex(Types::PrimitiveKind kind, uint32_t count, Types::CoreType index_type, uint64_t offset, int32_t base_vertex);
// clang-format on

} // namespace Gloom::Commands

#endif // GLOOM_COMMANDS_H