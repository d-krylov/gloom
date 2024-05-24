#include "graphics_pipeline.h"
#include "debug.h"
#include "tools.h"

namespace Gloom {

GraphicsPipeline::GraphicsPipeline() { glCreateProgramPipelines(1, &shader_pipeline_handle_); }

GraphicsPipeline::GraphicsPipeline(const std::string &vs, const std::string &fs)
  : GraphicsPipeline() {
  AddShader(Types::ShaderIndex::VERTEX, vs);
  AddShader(Types::ShaderIndex::FRAGMENT, fs);
}

GraphicsPipeline::GraphicsPipeline(const std::filesystem::path &vs,
                                   const std::filesystem::path &fs)
  : GraphicsPipeline(ReadFile(vs), ReadFile(fs)) {}

GraphicsPipeline::~GraphicsPipeline() {
  glDeleteProgramPipelines(1, &shader_pipeline_handle_);
}

void GraphicsPipeline::AddShader(Types::ShaderIndex index, const std::string &source) {
  auto source_cstr = source.c_str();
  auto kind = static_cast<uint16_t>(Types::GetShaderKind(index));
  shaders_[index] = glCreateShaderProgramv(kind, 1, &source_cstr);
  bool status = GetShaderLinkStatus(shaders_[index]);
  CORE_VERIFY(status);
  UseStage(index);
}

void GraphicsPipeline::UseStage(Types::ShaderIndex index) {
  auto stage = static_cast<uint32_t>(Types::GetShaderBit(index));
  glUseProgramStages(shader_pipeline_handle_, stage, shaders_[index]);
}

void GraphicsPipeline::Bind() const {
  CORE_VERIFY(shader_pipeline_handle_ != 0);
  glBindProgramPipeline(shader_pipeline_handle_);
}

} // namespace Gloom