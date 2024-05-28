#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "core_types.h"
#include "vertex.h"

namespace Gloom {

std::array<Vertex, 36> MakeBox();
std::array<Vertex, 24> MakeOctahedron();

} // namespace Gloom

#endif // PRIMITIVES_H