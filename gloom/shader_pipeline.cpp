#include "shader_pipeline.h"
#include "gloom_assert.h"
#include "gloom_debug.h"
#include "gloom_tools.h"

namespace Gloom {

ShaderPipeline::ShaderPipeline() {
  glCreateProgramPipelines(1, &shader_pipeline_handle_);
}

ShaderPipeline::ShaderPipeline(const std::string &vs, const std::string &fs)
    : ShaderPipeline() {
  AddShader(Types::ShaderIndex::VERTEX, vs);
  AddShader(Types::ShaderIndex::FRAGMENT, fs);
}

ShaderPipeline::ShaderPipeline(const std::filesystem::path &vs,
                               const std::filesystem::path &fs)
    : ShaderPipeline(Tools::ReadFile(vs), Tools::ReadFile(fs)) {}

ShaderPipeline::~ShaderPipeline() {
  glDeleteProgramPipelines(1, &shader_pipeline_handle_);
}

void ShaderPipeline::AddShader(Types::ShaderIndex index,
                               const std::string &source) {
  auto source_cstr = source.c_str();
  auto kind = static_cast<uint16_t>(Types::GetShaderKind(index));
  shaders_[index] = glCreateShaderProgramv(kind, 1, &source_cstr);
  bool status = Debug::GetShaderLinkStatus(shaders_[index]);
  GLOOM_VERIFY(status);
  UseStage(index);
}

void ShaderPipeline::UseStage(Types::ShaderIndex index) {
  auto stage = static_cast<uint32_t>(Types::GetShaderBit(index));
  glUseProgramStages(shader_pipeline_handle_, stage, shaders_[index]);
}

void ShaderPipeline::Bind() const {
  GLOOM_VERIFY(shader_pipeline_handle_ != 0);
  glBindProgramPipeline(shader_pipeline_handle_);
}

} // namespace Gloom