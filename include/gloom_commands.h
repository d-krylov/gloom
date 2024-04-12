#ifndef GLOOM_COMMANDS_H
#define GLOOM_COMMANDS_H

#include "gloom_types.h"
#include <span>

namespace Gloom ::Commands {

void Clear();
void EnableFaceCulling();
void EnableDepthTesting();
void SetViewport(int32_t x, int32_t y, uint32_t width, uint32_t height);
void DrawArrays(Types::PrimitiveKind kind, int32_t first, uint32_t count);
void DrawElements(Types::PrimitiveKind kind, std::span<uint32_t> i);
void DrawElements(Types::PrimitiveKind kind, uint32_t count);

} // namespace Gloom::Commands

#endif // GLOOM_COMMANDS_H