#include "primitives.h"

namespace Gloom {

std::array<VertexPNT, 36> MakeBox() {
  return std::array<VertexPNT, 36>{
    // Back face
    VertexPNT{{-0.5f, -0.5f, -0.5f}, {+0.0f, +0.0f, -1.0f}, {0.0f, 0.0f}}, // Bottom-left
    VertexPNT{{+0.5f, +0.5f, -0.5f}, {+0.0f, +0.0f, -1.0f}, {1.0f, 1.0f}}, // top-right
    VertexPNT{{+0.5f, -0.5f, -0.5f}, {+0.0f, +0.0f, -1.0f}, {1.0f, 0.0f}}, // bottom-right
    VertexPNT{{+0.5f, +0.5f, -0.5f}, {+0.0f, +0.0f, -1.0f}, {1.0f, 1.0f}}, // top-right
    VertexPNT{{-0.5f, -0.5f, -0.5f}, {+0.0f, +0.0f, -1.0f}, {0.0f, 0.0f}}, // bottom-left
    VertexPNT{{-0.5f, +0.5f, -0.5f}, {+0.0f, +0.0f, -1.0f}, {0.0f, 1.0f}}, // top-left
    // Front face
    VertexPNT{{-0.5f, -0.5f, +0.5f}, {+0.0f, +0.0f, +1.0f}, {0.0f, 0.0f}}, // bottom-left
    VertexPNT{{+0.5f, -0.5f, +0.5f}, {+0.0f, +0.0f, +1.0f}, {1.0f, 0.0f}}, // bottom-right
    VertexPNT{{+0.5f, +0.5f, +0.5f}, {+0.0f, +0.0f, +1.0f}, {1.0f, 1.0f}}, // top-right
    VertexPNT{{+0.5f, +0.5f, +0.5f}, {+0.0f, +0.0f, +1.0f}, {1.0f, 1.0f}}, // top-right
    VertexPNT{{-0.5f, +0.5f, +0.5f}, {+0.0f, +0.0f, +1.0f}, {0.0f, 1.0f}}, // top-left
    VertexPNT{{-0.5f, -0.5f, +0.5f}, {+0.0f, +0.0f, +1.0f}, {0.0f, 0.0f}}, // bottom-left
    // Left face
    VertexPNT{{-0.5f, +0.5f, +0.5f}, {-1.0f, +0.0f, +0.0f}, {1.0f, 0.0f}}, // top-right
    VertexPNT{{-0.5f, +0.5f, -0.5f}, {-1.0f, +0.0f, +0.0f}, {1.0f, 1.0f}}, // top-left
    VertexPNT{{-0.5f, -0.5f, -0.5f}, {-1.0f, +0.0f, +0.0f}, {0.0f, 1.0f}}, // bottom-left
    VertexPNT{{-0.5f, -0.5f, -0.5f}, {-1.0f, +0.0f, +0.0f}, {0.0f, 1.0f}}, // bottom-left
    VertexPNT{{-0.5f, -0.5f, +0.5f}, {-1.0f, +0.0f, +0.0f}, {0.0f, 0.0f}}, // bottom-right
    VertexPNT{{-0.5f, +0.5f, +0.5f}, {-1.0f, +0.0f, +0.0f}, {1.0f, 0.0f}}, // top-right
    // Right face
    VertexPNT{{+0.5f, +0.5f, +0.5f}, {+1.0f, +0.0f, +0.0f}, {1.0f, 0.0f}}, // top-left
    VertexPNT{{+0.5f, -0.5f, -0.5f}, {+1.0f, +0.0f, +0.0f}, {0.0f, 1.0f}}, // bottom-right
    VertexPNT{{+0.5f, +0.5f, -0.5f}, {+1.0f, +0.0f, +0.0f}, {1.0f, 1.0f}}, // top-right
    VertexPNT{{+0.5f, -0.5f, -0.5f}, {+1.0f, +0.0f, +0.0f}, {0.0f, 1.0f}}, // bottom-right
    VertexPNT{{+0.5f, +0.5f, +0.5f}, {+1.0f, +0.0f, +0.0f}, {1.0f, 0.0f}}, // top-left
    VertexPNT{{+0.5f, -0.5f, +0.5f}, {+1.0f, +0.0f, +0.0f}, {0.0f, 0.0f}}, // bottom-left
    // Bottom face
    VertexPNT{{-0.5f, -0.5f, -0.5f}, {+0.0f, -1.0f, +0.0f}, {0.0f, 1.0f}}, // top-right
    VertexPNT{{+0.5f, -0.5f, -0.5f}, {+0.0f, -1.0f, +0.0f}, {1.0f, 1.0f}}, // top-left
    VertexPNT{{+0.5f, -0.5f, +0.5f}, {+0.0f, -1.0f, +0.0f}, {1.0f, 0.0f}}, // bottom-left
    VertexPNT{{+0.5f, -0.5f, +0.5f}, {+0.0f, -1.0f, +0.0f}, {1.0f, 0.0f}}, // bottom-left
    VertexPNT{{-0.5f, -0.5f, +0.5f}, {+0.0f, -1.0f, +0.0f}, {0.0f, 0.0f}}, // bottom-right
    VertexPNT{{-0.5f, -0.5f, -0.5f}, {+0.0f, -1.0f, +0.0f}, {0.0f, 1.0f}}, // top-right
    // Top face
    VertexPNT{{-0.5f, +0.5f, -0.5f}, {+0.0f, +1.0f, +0.0f}, {0.0f, 1.0f}},  // top-left
    VertexPNT{{+0.5f, +0.5f, +0.5f}, {+0.0f, +1.0f, +0.0f}, {1.0f, 0.0f}},  // bottom-right
    VertexPNT{{+0.5f, +0.5f, -0.5f}, {+0.0f, +1.0f, +0.0f}, {1.0f, 1.0f}},  // top-right
    VertexPNT{{+0.5f, +0.5f, +0.5f}, {+0.0f, +1.0f, +0.0f}, {1.0f, 0.0f}},  // bottom-right
    VertexPNT{{-0.5f, +0.5f, -0.5f}, {+0.0f, +1.0f, +0.0f}, {0.0f, 1.0f}},  // top-left
    VertexPNT{{-0.5f, +0.5f, +0.5f}, {+0.0f, +1.0f, +0.0f}, {0.0f, 0.0f}}}; // bottom-left
}

} // namespace Gloom