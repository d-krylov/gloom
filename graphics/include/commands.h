#ifndef GLOOM_COMMANDS_H
#define GLOOM_COMMANDS_H

#include "graphics_types.h"
#include <span>

namespace Gloom ::Commands {

void Clear();
void SetFaceCulling(bool b);
void SetDepthTesting(bool b);
void SetStencilTesting(bool b);
void SetBlending(bool b, Types::BlendEquation equation,
                 Types::BlendFunctionSeparate source_rgb,
                 Types::BlendFunctionSeparate destination_rgb,
                 Types::BlendFunctionSeparate source_alpha,
                 Types::BlendFunctionSeparate destination_alpha);

void SetViewport(int32_t x, int32_t y, uint32_t width, uint32_t height);
void DrawArrays(Types::PrimitiveKind kind, int32_t first, uint32_t count);
void DrawElements(Types::PrimitiveKind kind, std::span<uint32_t> i);
void DrawElements(Types::PrimitiveKind kind, uint32_t count);
void DrawElementsBaseVertex(Types::PrimitiveKind kind, uint32_t count,
                            Types::CoreType index_type, uint64_t offset, int32_t base_vertex);

} // namespace Gloom::Commands

#endif // GLOOM_COMMANDS_H