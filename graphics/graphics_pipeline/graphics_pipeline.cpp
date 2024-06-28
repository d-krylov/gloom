#include "graphics_pipeline.h"
#include "debug.h"
#include "gloom_core/include/tools.h"
#include <iostream>

namespace Gloom {

GraphicsPipeline::GraphicsPipeline() { glCreateProgramPipelines(1, &shader_pipeline_handle_); }

GraphicsPipeline::GraphicsPipeline(const std::initializer_list<std::filesystem::path> &paths)
  : GraphicsPipeline() {
  for (const auto &path : paths) {
    auto shader_bin = ReadFile(path);
    auto shader_index = GetShaderIndex(path);
    CORE_VERIFY(shader_index.has_value());
    AddShader(shader_index.value(), shader_bin);
  }
}

GraphicsPipeline::~GraphicsPipeline() {
  glDeleteProgramPipelines(1, &shader_pipeline_handle_);
}

void GraphicsPipeline::AddShader(ShaderIndex index, const std::string &source) {
  auto source_cstr = source.c_str();
  auto kind = static_cast<uint16_t>(GetShaderKind(index));
  shaders_[index] = glCreateShaderProgramv(kind, 1, &source_cstr);
  bool status = GetShaderLinkStatus(shaders_[index]);

  if (status == false) {
    std::cout << GetShaderLog(shaders_[index]) << std::endl;
  }

  CORE_VERIFY(status);
  UseStage(index);
}

void GraphicsPipeline::UseStage(ShaderIndex index) {
  auto stage = static_cast<uint32_t>(GetShaderBit(index));
  glUseProgramStages(shader_pipeline_handle_, stage, shaders_[index]);
}

void GraphicsPipeline::Bind() const {
  CORE_VERIFY(shader_pipeline_handle_ != 0);
  glBindProgramPipeline(shader_pipeline_handle_);
}

} // namespace Gloom