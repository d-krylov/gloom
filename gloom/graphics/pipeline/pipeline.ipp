#ifndef GLOOM_SHADER_UNIFORM_H
#define GLOOM_SHADER_UNIFORM_H

#include "compute_pipeline.h"
#include "graphics_pipeline.h"
#include <type_traits>

namespace Gloom {

// clang-format off
template <typename T>
inline void SetShaderUniform(uint32_t shader, int32_t location, T const &value, bool transpose) {
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
    UNREACHABLE();
  }
}
// clang-format on

template <typename T>
void GraphicsPipeline::SetUniform(ShaderKind kind, std::string_view name, T value, bool transpose) {
  auto index = GetShaderIndex(kind);
  auto location = glGetUniformLocation(shaders_[index], name.data());
  SetShaderUniform(shaders_[index], location, value, transpose);
}

template <typename T>
void ComputePipeline::SetUniform(std::string_view name, T value, bool transpose) {
  auto location = glGetUniformLocation(compute_shader_, name.data());
  SetShaderUniform(compute_shader_, location, value, transpose);
}

} // namespace Gloom

#endif // GLOOM_SHADER_UNIFORM_H