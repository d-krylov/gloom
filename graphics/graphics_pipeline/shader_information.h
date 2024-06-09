#ifndef SHADER_REFLECTION_H
#define SHADER_REFLECTION_H

#include "graphics_types.h"
#include "tools.h"

namespace Gloom {

class ShaderInformation {
public:
  ShaderInformation(const std::filesystem::path &path);

  ShaderKind GetShaderKind() const { return kind_; }

private:
  ShaderKind kind_;
  std::string source_;
};

} // namespace Gloom

#endif // SHADER_REFLECTION_H