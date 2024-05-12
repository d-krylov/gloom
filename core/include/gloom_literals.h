#ifndef GLOOM_LITERALS_H
#define GLOOM_LITERALS_H

#include <cstdint>

namespace Gloom {

constexpr inline std::size_t operator""_KiB(unsigned long long int x) {
  return 1024ULL * x;
}

constexpr inline std::size_t operator""_MiB(unsigned long long int x) {
  return 1024_KiB * x;
}

} // namespace Gloom

#endif // GLOOM_LITERALS_H