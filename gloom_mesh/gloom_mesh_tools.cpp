#include "gloom_mesh_tools.h"
#include "gloom_assert.h"

namespace Gloom {

std::vector<Types::Vector3i>
Triangulate(const std::vector<std::vector<int32_t>> &faces) {
  std::vector<Types::Vector3i> ret;
  for (const auto &face : faces) {
    GLOOM_VERIFY(face.size() > 2);
    for (std::size_t i = 2; i < face.size(); i++) {
      ret.emplace_back(Types::Vector3i(face[0], face[i - 1], face[i]));
    }
  }
  return ret;
}

} // namespace Gloom