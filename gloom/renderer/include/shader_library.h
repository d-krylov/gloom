#ifndef GLOOM_SHADER_LIBRARY_H
#define GLOOM_SHADER_LIBRARY_H

#include "gloom/graphics/pipeline/graphics_pipeline.h"
#include <array>

namespace Gloom {

constexpr inline uint32_t GRAPHICS_PIPELINES_COUNT = 5;

class ShaderLibrary {
public:
  ShaderLibrary();

  static ShaderLibrary &Get() { return *shader_library_instance_; }

  GraphicsPipeline &GetGraphicsPipeline(uint32_t i) { return graphics_pipelines_[i]; }

private:
  std::array<GraphicsPipeline, GRAPHICS_PIPELINES_COUNT> graphics_pipelines_;

  static ShaderLibrary *shader_library_instance_;
};

} // namespace Gloom

#endif // GLOOM_SHADER_LIBRARY_H