#ifndef CORE_TYPES_H
#define CORE_TYPES_H

#include "linalg/linalg.h"

namespace Gloom ::Types {

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
constexpr auto Z = Vector3f(0.0f, 1.0f, 1.0f);

constexpr float PI = 3.1415926535897f;

// clang-format off
template <typename T, int N>        T *Cast(linalg::vec<T, N> &v)    { return linalg::begin(v); }
template <typename T, int M, int N> T *Cast(linalg::mat<T, M, N> &m) { return linalg::begin(m.x); }

template <typename T, int N>        const T *Cast(const linalg::vec<T, N> &v)    { return linalg::begin(v); }
template <typename T, int M, int N> const T *Cast(const linalg::mat<T, M, N> &m) { return linalg::begin(m.x); }
// clang-format on

// clang-format off
constexpr inline std::size_t operator""_KiB(unsigned long long int x) { return 1024ULL * x; }
constexpr inline std::size_t operator""_MiB(unsigned long long int x) { return 1024_KiB * x; }
// clang-format on

} // namespace Gloom::Types

#endif // CORE_TYPES_H