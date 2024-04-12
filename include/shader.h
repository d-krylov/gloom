#ifndef SHADER_H
#define SHADER_H

#include "gloom_types.h"

namespace Gloom {

class Shader {
public:
  [[nodiscard]] Types::ShaderKind GetKind() const { return shader_kind_; }
  [[nodiscard]] Types::Handle GetHandle() const { return shader_handle_; }

private:
  Types::Handle shader_handle_;
  Types::ShaderKind shader_kind_;
};

} // namespace Gloom

#endif // SHADER_H