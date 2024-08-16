#ifndef GLOOM_CORE_TYPES_H
#define GLOOM_CORE_TYPES_H

#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/normal.hpp>
#include <glm/gtx/quaternion.hpp>
#include <optional>
#include <span>

namespace Gloom {

using Vector2f = glm::vec2;
using Vector3f = glm::vec3;
using Vector4f = glm::vec4;
using Vector2i = glm::ivec2;
using Vector3i = glm::ivec3;
using Vector4i = glm::ivec4;
using Vector2u = glm::uvec2;
using Vector3u = glm::uvec3;
using Vector4u = glm::uvec4;
using Vector2d = glm::dvec2;
using Vector3d = glm::dvec3;
using Vector4d = glm::dvec4;
using Matrix3f = glm::mat3x3;
using Matrix4f = glm::mat4x4;
using Quaternion = glm::quat;

constexpr auto X = Vector3f(1.0f, 0.0f, 0.0f);
constexpr auto Y = Vector3f(0.0f, 1.0f, 0.0f);
constexpr auto Z = Vector3f(0.0f, 0.0f, 1.0f);

constexpr float PI = glm::pi<float>();

template <typename T> std::byte *ToBytePointer(T *data) {
  return reinterpret_cast<std::byte *>(data);
}

// clang-format off
constexpr inline std::size_t operator""_KiB(unsigned long long int x) { return 1024ULL * x; }
constexpr inline std::size_t operator""_MiB(unsigned long long int x) { return 1024_KiB * x; }
// clang-format on

[[nodiscard]] inline int32_t GetBinaryLogarithm(int32_t value) {
  int32_t ret{0};
  while (value > 1) {
    value >>= 1;
    ret++;
  }
  return ret;
}

} // namespace Gloom

#endif // GLOOM_CORE_TYPES_H