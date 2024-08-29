#ifndef VERTEX_H
#define VERTEX_H

#include "gloom/graphics/include/graphics_types.h"
#include "gloom/graphics/vertex/vertex_format.h"

namespace Gloom {

struct Vertex {
  Vector3f position_{0.0f};
  Vector3f normal_{0.0f};
  Vector2f uv_{0.0f};

  static VertexFormat GetFormat() {
    return VertexFormat(
      {Gloom::DataType::VECTOR3, Gloom::DataType::VECTOR3, Gloom::DataType::VECTOR2});
  }
};

struct ExtendedVertex {
  Vector3f position_{0.0f};
  Vector3f normal_{0.0f};
  Vector2f uv_{0.0f};
  Vector3f tangent_{0.0f};
  Vector3f bitangent_{0.0f};

  static VertexFormat GetFormat() {
    return VertexFormat({Gloom::DataType::VECTOR3, Gloom::DataType::VECTOR3,
                         Gloom::DataType::VECTOR2, Gloom::DataType::VECTOR3,
                         Gloom::DataType::VECTOR3});
  }
};

} // namespace Gloom

#endif // VERTEX_H