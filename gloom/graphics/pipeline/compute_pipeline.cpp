#include "core/include/tools.h"
#include "graphics/include/debug.h"
#include "pipeline.ipp"

namespace Gloom {

ComputePipeline::ComputePipeline(const std::filesystem::path &path) {
  glCreateProgramPipelines(1, &compute_pipeline_);

  auto shader_bin = ReadFile(path);
  auto source_cstr = shader_bin.c_str();

  compute_shader_ = glCreateShaderProgramv(GL_COMPUTE_SHADER, 1, &source_cstr);

  bool status = GetShaderLinkStatus(compute_shader_);

  if (status == false) {
  }

  glUseProgramStages(compute_pipeline_, GL_COMPUTE_SHADER_BIT, compute_shader_);
}

ComputePipeline::~ComputePipeline() { glDeleteProgramPipelines(1, &compute_pipeline_); }

void ComputePipeline::Bind() { glBindProgramPipeline(compute_pipeline_); }

} // namespace Gloom
