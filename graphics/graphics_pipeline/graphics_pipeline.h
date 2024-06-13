#ifndef GLOOM_SHADER_PIPELINE_H
#define GLOOM_SHADER_PIPELINE_H

#include "graphics_types.h"
#include "shader_uniform.h"
#include <array>
#include <filesystem>
#include <string>

namespace Gloom {

class GraphicsPipeline {
public:
  GraphicsPipeline();
  GraphicsPipeline(const std::initializer_list<std::filesystem::path> &paths);

  ~GraphicsPipeline();

  operator Handle() const { return shader_pipeline_handle_; }

  template <typename T>
  void SetUniform(ShaderIndex index, std::string_view name, T value, bool transpose = false) {
    auto location = glGetUniformLocation(shaders_[index], name.data());
    SetUniformInternal(shaders_[index], location, value, transpose);
  }

  void AddShader(ShaderIndex index, const std::string &source);
  void UseStage(ShaderIndex index);

  void Bind() const;

private:
  Handle shader_pipeline_handle_{0};
  std::array<Handle, SHADER_STAGES_COUNT> shaders_;
};

} // namespace Gloom

#endif // GLOOM_SHADER_PIPELINE_H