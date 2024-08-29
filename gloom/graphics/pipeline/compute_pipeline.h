#ifndef GLOOM_COMPUTE_PIPELINE_H
#define GLOOM_COMPUTE_PIPELINE_H

#include "shader_uniform.h"

namespace Gloom {

class ComputePipeline {
public:
  ComputePipeline(const std::filesystem::path &path);

  ~ComputePipeline();

  void Bind();

  template <typename T> void SetUniform(std::string_view name, T value, bool transpose = false) {
    auto location = glGetUniformLocation(compute_shader_, name.data());
    SetShaderUniform(compute_shader_, location, value, transpose);
  }

private:
  uint32_t compute_pipeline_;
  uint32_t compute_shader_;
};

} // namespace Gloom

#endif // GLOOM_COMPUTE_PIPELINE_H