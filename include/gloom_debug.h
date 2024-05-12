#ifndef GLOOM_DEBUG_H
#define GLOOM_DEBUG_H

#include "graphics_types.h"
#include <optional>
#include <string>

namespace Gloom ::Debug {

std::optional<std::string> GetShaderLog(Types::Handle shader_handle);

bool GetShaderLinkStatus(Types::Handle shader_handle);

void EnableDebug();

} // namespace Gloom::Debug

#endif // GLOOM_DEBUG_H