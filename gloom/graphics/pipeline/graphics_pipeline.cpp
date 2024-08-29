#include "graphics_pipeline.h"
#include "gloom/core/include/tools.h"
#include "gloom/graphics/include/debug.h"
#include <iostream>

namespace Gloom {

GraphicsPipeline::GraphicsPipeline(const std::initializer_list<std::filesystem::path> &paths) {
  glCreateProgramPipelines(1, &graphics_pipeline_);
  for (const auto &path : paths) {
    auto shader_bin = ReadFile(path);
    auto shader_kind = GetShaderKind(path);
    AddShader(shader_kind.value(), shader_bin);
  }
}

GraphicsPipeline::~GraphicsPipeline() { glDeleteProgramPipelines(1, &graphics_pipeline_); }

void GraphicsPipeline::AddShader(ShaderKind kind, const std::string &source) {
  auto source_cstr = source.c_str();
  auto index = GetShaderIndex(kind);
  shaders_[index] = glCreateShaderProgramv(uint16_t(kind), 1, &source_cstr);

  bool status = GetShaderLinkStatus(shaders_[index]);

  if (status == false) {
    std::cout << GetShaderLog(shaders_[index]) << std::endl;
    CORE_VERIFY(status);
  }

  glUseProgramStages(graphics_pipeline_, uint32_t(GetShaderBit(kind)), shaders_[index]);
}

void GraphicsPipeline::Bind() const {
  CORE_VERIFY(graphics_pipeline_ != 0);
  glBindProgramPipeline(graphics_pipeline_);
}

} // namespace Gloom