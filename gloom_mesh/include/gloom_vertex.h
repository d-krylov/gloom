#ifndef GLOOM_VERTEX_H
#define GLOOM_VERTEX_H

#include "graphics_types.h"
#include "vertex_format.h"

namespace Gloom {

struct Vertex {
  Types::Vector3f position_{0.0f};
  Types::Vector3f normal_{0.0f};
  Types::Vector2f uv_{0.0f};
  Types::Vector3f tangent_{0.0f};
  Types::Vector3f bitangent_{0.0f};

  static VertexFormat GetFormat() {
    return VertexFormat(
        {Gloom::Types::DataType::VECTOR3, Gloom::Types::DataType::VECTOR3,
         Gloom::Types::DataType::VECTOR2, Gloom::Types::DataType::VECTOR3,
         Gloom::Types::DataType::VECTOR3});
  }
};

struct VertexPCT {
  Types::Vector3f position_{0.0f};
  Types::Vector3f color_{0.0f};
  Types::Vector2f uv_{0.0f};

  static VertexFormat GetFormat() {
    return VertexFormat({Gloom::Types::DataType::VECTOR3,
                         Gloom::Types::DataType::VECTOR3,
                         Gloom::Types::DataType::VECTOR2});
  }
};

struct VertexPNT {
  Types::Vector3f position_{0.0f};
  Types::Vector3f normal_{0.0f};
  Types::Vector2f uv_{0.0f};

  static VertexFormat GetFormat() {
    return VertexFormat({Gloom::Types::DataType::VECTOR3,
                         Gloom::Types::DataType::VECTOR3,
                         Gloom::Types::DataType::VECTOR2});
  }
};

struct VertexPT {
  Types::Vector3f position_{0.0f};
  Types::Vector2f uv_{0.0f};

  static VertexFormat GetFormat() {
    return VertexFormat(
        {Gloom::Types::DataType::VECTOR3, Gloom::Types::DataType::VECTOR2});
  }
};

} // namespace Gloom

#endif // GLOOM_VERTEX_H