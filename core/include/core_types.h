#ifndef CORE_TYPES_H
#define CORE_TYPES_H

#include "linalg/linalg.h"

namespace Gloom {

using Vector2f = linalg::aliases::float2;
using Vector3f = linalg::aliases::float3;
using Vector4f = linalg::aliases::float4;
using Vector2i = linalg::aliases::int2;
using Vector3i = linalg::aliases::int3;
using Vector4i = linalg::aliases::int4;
using Vector2u = linalg::aliases::uint2;
using Vector3u = linalg::aliases::uint3;
using Vector4u = linalg::aliases::uint4;
using Vector2d = linalg::aliases::double2;
using Matrix4f = linalg::aliases::float4x4;

constexpr auto X = Vector3f(1.0f, 0.0f, 0.0f);
constexpr auto Y = Vector3f(0.0f, 1.0f, 0.0f);
constexpr auto Z = Vector3f(0.0f, 1.0f, 0.0f);

constexpr float PI = 3.1415926535897f;

// clang-format off
template <typename T, int N>              T *Cast(      linalg::vec<T, N> &v)    { return linalg::begin(v); }
template <typename T, int M, int N>       T *Cast(      linalg::mat<T, M, N> &m) { return linalg::begin(m.x); }
template <typename T, int N>        const T *Cast(const linalg::vec<T, N> &v)    { return linalg::begin(v); }
template <typename T, int M, int N> const T *Cast(const linalg::mat<T, M, N> &m) { return linalg::begin(m.x); }
// clang-format on

template <typename T> std::byte *ToBytePointer(T *data) {
  return reinterpret_cast<std::byte *>(data);
}

[[nodiscard]] float Radians(float degrees);
[[nodiscard]] float Degrees(float radians);
[[nodiscard]] Matrix4f Translate(const Vector3f &v);
[[nodiscard]] Matrix4f RotateX(float degrees);
[[nodiscard]] Matrix4f RotateY(float degrees);
[[nodiscard]] Matrix4f RotateZ(float degrees);

[[nodiscard]] int32_t GetLog(int32_t value);

[[nodiscard]] Vector3f GetNormal(const Vector3f &a, const Vector3f &b, const Vector3f &c);
[[nodiscard]] Matrix4f GetOrthographic(float L, float R, float B, float T, float N, float F);

// clang-format off
constexpr inline std::size_t operator""_KiB(unsigned long long int x) { return 1024ULL * x; }
constexpr inline std::size_t operator""_MiB(unsigned long long int x) { return 1024_KiB * x; }
// clang-format on

} // namespace Gloom

#endif // CORE_TYPES_H