#ifndef SHADER_PIPELINE_H
#define SHADER_PIPELINE_H

#include "graphics_types.h"
#include "shader_uniform.h"
#include <array>
#include <filesystem>
#include <string>

namespace Gloom {

class GraphicsPipeline {
public:
  GraphicsPipeline();
  GraphicsPipeline(const std::string &vs, const std::string &fs);
  GraphicsPipeline(const std::filesystem::path &vs,
                   const std::filesystem::path &fs);

  ~GraphicsPipeline();

  operator Types::Handle() const { return shader_pipeline_handle_; }

  template <typename T>
  void SetUniform(Types::ShaderIndex index, std::string_view name, T value,
                  bool transpose = false) {
    auto location = glGetUniformLocation(shaders_[index], name.data());
    SetUniformInternal(shaders_[index], location, value, transpose);
  }

  void AddShader(Types::ShaderIndex index, const std::string &source);
  void UseStage(Types::ShaderIndex index);

  void Bind() const;

private:
  Types::Handle shader_pipeline_handle_{0};
  std::array<Types::Handle, Types::SHADER_STAGES_COUNT> shaders_;
};

} // namespace Gloom

#endif // SHADER_PIPELINE_H