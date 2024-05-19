#ifndef SHADER_REFLECTION_H
#define SHADER_REFLECTION_H

#include "gloom_tools.h"
#include "graphics_types.h"

namespace Gloom {

class ShaderInformation {
public:
  ShaderInformation(std::filesystem::path path);

  Types::ShaderKind GetShaderKind() const { return kind_; }

private:
  Types::ShaderKind kind_;
  std::string source_;
};

} // namespace Gloom

#endif // SHADER_REFLECTION_H