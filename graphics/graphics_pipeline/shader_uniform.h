#ifndef SHADER_UNIFORM_H
#define SHADER_UNIFORM_H

#include "gloom_assert.h"
#include "graphics_types.h"
#include <type_traits>

namespace Gloom {

// clang-format off
template <typename T>
inline void SetUniformInternal(uint32_t shader, int32_t location, T const &value, bool transpose) {
  if constexpr (std::is_same_v<T, int32_t>)              glProgramUniform1i(shader, location, value);
  else if constexpr (std::is_same_v<T, uint32_t>)        glProgramUniform1ui(shader, location, value);
  else if constexpr (std::is_same_v<T, bool>)            glProgramUniform1ui(shader, location, value);
  else if constexpr (std::is_same_v<T, float>)           glProgramUniform1f(shader, location, value);
  else if constexpr (std::is_same_v<T, double>)          glProgramUniform1d(shader, location, value);
  else if constexpr (std::is_same_v<T, Types::Vector2f>) glProgramUniform2fv(shader, location, 1, Types::Cast(value));
  else if constexpr (std::is_same_v<T, Types::Vector3f>) glProgramUniform3fv(shader, location, 1, Types::Cast(value));
  else if constexpr (std::is_same_v<T, Types::Vector4f>) glProgramUniform4fv(shader, location, 1, Types::Cast(value));
  else if constexpr (std::is_same_v<T, Types::Vector2i>) glProgramUniform2iv(shader, location, 1, Types::Cast(value));
  else if constexpr (std::is_same_v<T, Types::Vector3i>) glProgramUniform3iv(shader, location, 1, Types::Cast(value));
  else if constexpr (std::is_same_v<T, Types::Vector4i>) glProgramUniform4iv(shader, location, 1, Types::Cast(value));
  else if constexpr (std::is_same_v<T, Types::Vector2u>) glProgramUniform2uiv(shader, location, 1, Types::Cast(value));
  else if constexpr (std::is_same_v<T, Types::Vector3u>) glProgramUniform3uiv(shader, location, 1, Types::Cast(value));
  else if constexpr (std::is_same_v<T, Types::Vector4u>) glProgramUniform4uiv(shader, location, 1, Types::Cast(value));
  else if constexpr (std::is_same_v<T, Types::Matrix4f>) glProgramUniformMatrix4fv(shader, location, 1, transpose, Types::Cast(value));
  else {
    GLOOM_UNREACHABLE();
  }
}
// clang-format on

} // namespace Gloom

#endif // SHADER_UNIFORM_H