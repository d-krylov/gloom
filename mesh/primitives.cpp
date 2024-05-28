#include "primitives.h"

namespace Gloom {

std::array<Vertex, 36> MakeBox() {
  return std::array<Vertex, 36>{
    // Back face
    Vertex{{-0.5f, -0.5f, -0.5f}, {+0.0f, +0.0f, -1.0f}, {0.0f, 0.0f}}, // Bottom-left
    Vertex{{+0.5f, +0.5f, -0.5f}, {+0.0f, +0.0f, -1.0f}, {1.0f, 1.0f}}, // top-right
    Vertex{{+0.5f, -0.5f, -0.5f}, {+0.0f, +0.0f, -1.0f}, {1.0f, 0.0f}}, // bottom-right
    Vertex{{+0.5f, +0.5f, -0.5f}, {+0.0f, +0.0f, -1.0f}, {1.0f, 1.0f}}, // top-right
    Vertex{{-0.5f, -0.5f, -0.5f}, {+0.0f, +0.0f, -1.0f}, {0.0f, 0.0f}}, // bottom-left
    Vertex{{-0.5f, +0.5f, -0.5f}, {+0.0f, +0.0f, -1.0f}, {0.0f, 1.0f}}, // top-left
    // Front face
    Vertex{{-0.5f, -0.5f, +0.5f}, {+0.0f, +0.0f, +1.0f}, {0.0f, 0.0f}}, // bottom-left
    Vertex{{+0.5f, -0.5f, +0.5f}, {+0.0f, +0.0f, +1.0f}, {1.0f, 0.0f}}, // bottom-right
    Vertex{{+0.5f, +0.5f, +0.5f}, {+0.0f, +0.0f, +1.0f}, {1.0f, 1.0f}}, // top-right
    Vertex{{+0.5f, +0.5f, +0.5f}, {+0.0f, +0.0f, +1.0f}, {1.0f, 1.0f}}, // top-right
    Vertex{{-0.5f, +0.5f, +0.5f}, {+0.0f, +0.0f, +1.0f}, {0.0f, 1.0f}}, // top-left
    Vertex{{-0.5f, -0.5f, +0.5f}, {+0.0f, +0.0f, +1.0f}, {0.0f, 0.0f}}, // bottom-left
    // Left face
    Vertex{{-0.5f, +0.5f, +0.5f}, {-1.0f, +0.0f, +0.0f}, {1.0f, 0.0f}}, // top-right
    Vertex{{-0.5f, +0.5f, -0.5f}, {-1.0f, +0.0f, +0.0f}, {1.0f, 1.0f}}, // top-left
    Vertex{{-0.5f, -0.5f, -0.5f}, {-1.0f, +0.0f, +0.0f}, {0.0f, 1.0f}}, // bottom-left
    Vertex{{-0.5f, -0.5f, -0.5f}, {-1.0f, +0.0f, +0.0f}, {0.0f, 1.0f}}, // bottom-left
    Vertex{{-0.5f, -0.5f, +0.5f}, {-1.0f, +0.0f, +0.0f}, {0.0f, 0.0f}}, // bottom-right
    Vertex{{-0.5f, +0.5f, +0.5f}, {-1.0f, +0.0f, +0.0f}, {1.0f, 0.0f}}, // top-right
    // Right face
    Vertex{{+0.5f, +0.5f, +0.5f}, {+1.0f, +0.0f, +0.0f}, {1.0f, 0.0f}}, // top-left
    Vertex{{+0.5f, -0.5f, -0.5f}, {+1.0f, +0.0f, +0.0f}, {0.0f, 1.0f}}, // bottom-right
    Vertex{{+0.5f, +0.5f, -0.5f}, {+1.0f, +0.0f, +0.0f}, {1.0f, 1.0f}}, // top-right
    Vertex{{+0.5f, -0.5f, -0.5f}, {+1.0f, +0.0f, +0.0f}, {0.0f, 1.0f}}, // bottom-right
    Vertex{{+0.5f, +0.5f, +0.5f}, {+1.0f, +0.0f, +0.0f}, {1.0f, 0.0f}}, // top-left
    Vertex{{+0.5f, -0.5f, +0.5f}, {+1.0f, +0.0f, +0.0f}, {0.0f, 0.0f}}, // bottom-left
    // Bottom face
    Vertex{{-0.5f, -0.5f, -0.5f}, {+0.0f, -1.0f, +0.0f}, {0.0f, 1.0f}}, // top-right
    Vertex{{+0.5f, -0.5f, -0.5f}, {+0.0f, -1.0f, +0.0f}, {1.0f, 1.0f}}, // top-left
    Vertex{{+0.5f, -0.5f, +0.5f}, {+0.0f, -1.0f, +0.0f}, {1.0f, 0.0f}}, // bottom-left
    Vertex{{+0.5f, -0.5f, +0.5f}, {+0.0f, -1.0f, +0.0f}, {1.0f, 0.0f}}, // bottom-left
    Vertex{{-0.5f, -0.5f, +0.5f}, {+0.0f, -1.0f, +0.0f}, {0.0f, 0.0f}}, // bottom-right
    Vertex{{-0.5f, -0.5f, -0.5f}, {+0.0f, -1.0f, +0.0f}, {0.0f, 1.0f}}, // top-right
    // Top face
    Vertex{{-0.5f, +0.5f, -0.5f}, {+0.0f, +1.0f, +0.0f}, {0.0f, 1.0f}},  // top-left
    Vertex{{+0.5f, +0.5f, +0.5f}, {+0.0f, +1.0f, +0.0f}, {1.0f, 0.0f}},  // bottom-right
    Vertex{{+0.5f, +0.5f, -0.5f}, {+0.0f, +1.0f, +0.0f}, {1.0f, 1.0f}},  // top-right
    Vertex{{+0.5f, +0.5f, +0.5f}, {+0.0f, +1.0f, +0.0f}, {1.0f, 0.0f}},  // bottom-right
    Vertex{{-0.5f, +0.5f, -0.5f}, {+0.0f, +1.0f, +0.0f}, {0.0f, 1.0f}},  // top-left
    Vertex{{-0.5f, +0.5f, +0.5f}, {+0.0f, +1.0f, +0.0f}, {0.0f, 0.0f}}}; // bottom-left
}

// clang-format off
std::array<Vertex, 24> MakeOctahedron() {
  auto vertices = std::array<Vertex, 24>{
    // Left Top Front face
    Vertex{{-0.5f, +0.0f, +0.0f}, {+0.0f, +0.0f, +0.0f}, {0.0f, 0.0f}},
    Vertex{{+0.0f, +0.0f, +0.5f}, {+0.0f, +0.0f, +0.0f}, {0.0f, 0.0f}},
    Vertex{{+0.0f, +0.5f, +0.0f}, {+0.0f, +0.0f, +0.0f}, {0.0f, 0.0f}},
    // Right Top Front face
    Vertex{{+0.0f, +0.0f, +0.5f}, {+0.0f, +0.0f, +0.0f}, {0.0f, 0.0f}},
    Vertex{{+0.5f, +0.0f, +0.0f}, {+0.0f, +0.0f, +0.0f}, {0.0f, 0.0f}},
    Vertex{{+0.0f, +0.5f, +0.0f}, {+0.0f, +0.0f, +0.0f}, {0.0f, 0.0f}},
    // Right Top Back face
    Vertex{{+0.5f, +0.0f, +0.0f}, {+0.0f, +0.0f, +0.0f}, {0.0f, 0.0f}},
    Vertex{{+0.0f, +0.0f, -0.5f}, {+0.0f, +0.0f, +0.0f}, {0.0f, 0.0f}},
    Vertex{{+0.0f, +0.5f, +0.0f}, {+0.0f, +0.0f, +0.0f}, {0.0f, 0.0f}},
    // Left Top Back face
    Vertex{{+0.0f, +0.0f, -0.5f}, {+0.0f, +0.0f, +0.0f}, {0.0f, 0.0f}},
    Vertex{{-0.5f, +0.0f, +0.0f}, {+0.0f, +0.0f, +0.0f}, {0.0f, 0.0f}},
    Vertex{{+0.0f, +0.5f, +0.0f}, {+0.0f, +0.0f, +0.0f}, {0.0f, 0.0f}},
    // Left Bottom Front face
    Vertex{{-0.5f, +0.0f, +0.0f}, {+0.0f, +0.0f, +0.0f}, {0.0f, 0.0f}},
    Vertex{{+0.0f, -0.5f, +0.0f}, {+0.0f, +0.0f, +0.0f}, {0.0f, 0.0f}},
    Vertex{{+0.0f, +0.0f, +0.5f}, {+0.0f, +0.0f, +0.0f}, {0.0f, 0.0f}},
    // Right Bottom Front face
    Vertex{{+0.0f, +0.0f, +0.5f}, {+0.0f, +0.0f, +0.0f}, {0.0f, 0.0f}},
    Vertex{{+0.0f, -0.5f, +0.0f}, {+0.0f, +0.0f, +0.0f}, {0.0f, 0.0f}},
    Vertex{{+0.5f, +0.0f, +0.0f}, {+0.0f, +0.0f, +0.0f}, {0.0f, 0.0f}},
    // Right Bottom Back face
    Vertex{{+0.5f, +0.0f, +0.0f}, {+0.0f, +0.0f, +0.0f}, {0.0f, 0.0f}},
    Vertex{{+0.0f, -0.5f, +0.0f}, {+0.0f, +0.0f, +0.0f}, {0.0f, 0.0f}},
    Vertex{{+0.0f, +0.0f, -0.5f}, {+0.0f, +0.0f, +0.0f}, {0.0f, 0.0f}},
    // Left Bottom Back face
    Vertex{{+0.0f, +0.0f, -0.5f}, {+0.0f, +0.0f, +0.0f}, {0.0f, 0.0f}},
    Vertex{{+0.0f, -0.5f, +0.0f}, {+0.0f, +0.0f, +0.0f}, {0.0f, 0.0f}},
    Vertex{{-0.5f, +0.0f, +0.0f}, {+0.0f, +0.0f, +0.0f}, {0.0f, 0.0f}}};

  for (uint32_t i = 0; i < vertices.size() - 2; i += 3) {
    auto normal = Types::GetNormal(vertices[i + 0].position_, 
                                   vertices[i + 1].position_,
                                   vertices[i + 2].position_);
    vertices[i + 0].normal_ = normal;
    vertices[i + 1].normal_ = normal;
    vertices[i + 2].normal_ = normal;
  }

  return vertices;
}
// clang-format on

} // namespace Gloom