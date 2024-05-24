#ifndef GLOOM_DEBUG_H
#define GLOOM_DEBUG_H

#include "graphics_types.h"
#include <string>

namespace Gloom {

std::string GetShaderLog(Types::Handle shader_handle);

bool GetShaderLinkStatus(Types::Handle shader_handle);

void EnableDebug();

} // namespace Gloom

#endif // GLOOM_DEBUG_H