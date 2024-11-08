#ifndef GLOOM_VERTEX_ATTRIBUTE_H
#define GLOOM_VERTEX_ATTRIBUTE_H

#include "graphics/include/graphics_types.h"

namespace Gloom {

class VertexFormat;

class VertexAttribute {
public:
  VertexAttribute(DataType type, bool normalize = false)
    : data_type_(type), normalize_(normalize) {}

  [[nodiscard]] DataType GetDataType() const { return data_type_; }
  [[nodiscard]] std::size_t GetSize() const { return GetDataTypeSize(data_type_); }
  [[nodiscard]] bool Normalize() const { return normalize_; }
  [[nodiscard]] std::size_t GetOffset() const { return offset_; }

  [[nodiscard]] std::size_t GetComponentCount() const {
    return GetDataTypeComponentCount(data_type_);
  }

  [[nodiscard]] PrimitiveDataType GetComponentType() const {
    return GetDataTypeComponentType(data_type_);
  }

  [[nodiscard]] bool IsFLOAT() const { return (GetComponentType() == PrimitiveDataType::FLOAT); }
  [[nodiscard]] bool IsDOUBLE() const { return (GetComponentType() == PrimitiveDataType::DOUBLE); }
  [[nodiscard]] bool IsRGBA() const { return (GetDataType() == DataType::PACKED_RGBA); }

private:
  DataType data_type_;
  bool normalize_{false};
  std::size_t offset_{0};
  friend class VertexFormat;
};

} // namespace Gloom

#endif // GLOOM_VERTEX_ATTRIBUTE_H