#ifndef GLOOM_DEBUG_H
#define GLOOM_DEBUG_H

#include "graphics_types.h"
#include <string>

namespace Gloom {

void EnableDebug();

[[nodiscard]] bool GetShaderLinkStatus(uint32_t shader);
[[nodiscard]] std::string GetShaderLog(uint32_t shader);

} // namespace Gloom

#endif // GLOOM_DEBUG_H