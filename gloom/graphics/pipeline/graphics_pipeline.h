#ifndef GLOOM_GRAPHICS_PIPELINE_H
#define GLOOM_GRAPHICS_PIPELINE_H

#include "graphics/include/graphics_types.h"
#include <array>
#include <filesystem>
#include <string>

namespace Gloom {

class GraphicsPipeline {
public:
  GraphicsPipeline(const std::initializer_list<std::filesystem::path> &paths);

  ~GraphicsPipeline();

  operator uint32_t() const { return graphics_pipeline_; }

  template <typename T>
  void SetUniform(ShaderKind kind, std::string_view name, T value, bool transpose = false);

  void Bind() const;

private:
  void AddShader(ShaderKind kind, const std::string &source);

private:
  uint32_t graphics_pipeline_{0};
  std::array<uint32_t, SHADER_STAGES_COUNT> shaders_;
};

} // namespace Gloom

#endif // GLOOM_GRAPHICS_PIPELINE_H