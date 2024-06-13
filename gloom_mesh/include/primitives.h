#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "gloom_core/include/core_types.h"
#include "vertex.h"

namespace Gloom {

[[nodiscard]] std::array<Vertex, 6> MakeSquare();
[[nodiscard]] std::array<Vertex, 36> MakeBox();
[[nodiscard]] std::array<Vertex, 24> MakeOctahedron();

} // namespace Gloom

#endif // PRIMITIVES_H