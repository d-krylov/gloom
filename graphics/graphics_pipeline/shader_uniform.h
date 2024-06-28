#ifndef GLOOM_SHADER_UNIFORM_H
#define GLOOM_SHADER_UNIFORM_H

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
  else if constexpr (std::is_same_v<T, Vector2f>) glProgramUniform2fv(shader, location, 1, glm::value_ptr(value));
  else if constexpr (std::is_same_v<T, Vector3f>) glProgramUniform3fv(shader, location, 1, glm::value_ptr(value));
  else if constexpr (std::is_same_v<T, Vector4f>) glProgramUniform4fv(shader, location, 1, glm::value_ptr(value));
  else if constexpr (std::is_same_v<T, Vector2i>) glProgramUniform2iv(shader, location, 1, glm::value_ptr(value));
  else if constexpr (std::is_same_v<T, Vector3i>) glProgramUniform3iv(shader, location, 1, glm::value_ptr(value));
  else if constexpr (std::is_same_v<T, Vector4i>) glProgramUniform4iv(shader, location, 1, glm::value_ptr(value));
  else if constexpr (std::is_same_v<T, Vector2u>) glProgramUniform2uiv(shader, location, 1, glm::value_ptr(value));
  else if constexpr (std::is_same_v<T, Vector3u>) glProgramUniform3uiv(shader, location, 1, glm::value_ptr(value));
  else if constexpr (std::is_same_v<T, Vector4u>) glProgramUniform4uiv(shader, location, 1, glm::value_ptr(value));
  else if constexpr (std::is_same_v<T, Matrix4f>) glProgramUniformMatrix4fv(shader, location, 1, transpose, glm::value_ptr(value));
  else {
    CORE_UNREACHABLE();
  }
}
// clang-format on

} // namespace Gloom

#endif // GLOOM_SHADER_UNIFORM_H