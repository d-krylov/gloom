#include "shader_information.h"
#include <optional>

namespace Gloom {

// clang-format off
std::optional<Types::ShaderIndex> GetShaderStage(const std::filesystem::path &path) {
  auto extension = path.extension().string();
  if (extension == ".vert") { return Types::ShaderIndex::VERTEX; }
  if (extension == ".geom") { return Types::ShaderIndex::GEOMETRY; }
  if (extension == ".tesc") { return Types::ShaderIndex::TESSELATION_CONTROL; }
  if (extension == ".tese") { return Types::ShaderIndex::TESSELATION_EVALUATION; }
  if (extension == ".frag") { return Types::ShaderIndex::FRAGMENT; }
  if (extension == ".comp") { return Types::ShaderIndex::COMPUTE; }
  return {};
}
// clang-format on

} // namespace Gloom