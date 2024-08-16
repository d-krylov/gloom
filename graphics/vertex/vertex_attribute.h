#ifndef VERTEX_ATTRIBUTE_H
#define VERTEX_ATTRIBUTE_H

#include "graphics/include/graphics_types.h"

namespace Gloom {

class VertexFormat;

class VertexAttribute {
public:
  VertexAttribute(DataType type, bool normalize = false,
                  AttributeUsage usage = AttributeUsage::NONE)
    : data_type_(type), normalize_(normalize), attribute_usage_(usage) {}

  [[nodiscard]] DataType GetDataType() const { return data_type_; }
  [[nodiscard]] AttributeUsage GetUsage() const { return attribute_usage_; }
  [[nodiscard]] std::size_t GetSize() const { return Gloom::GetSize(data_type_); }
  [[nodiscard]] bool IsFloat() const { return (GetComponentType() == CoreType::FLOAT); }
  [[nodiscard]] bool IsRGBA() const { return (GetDataType() == DataType::BVECTOR4); }

  [[nodiscard]] std::size_t GetComponentCount() const {
    return Gloom::GetComponentCount(data_type_);
  }

  [[nodiscard]] CoreType GetComponentType() const {
    return Gloom::GetComponentType(data_type_);
  }

  [[nodiscard]] bool IsDouble() const { return (GetComponentType() == CoreType::DOUBLE); }

  [[nodiscard]] bool Normalize() const { return normalize_; }
  [[nodiscard]] std::size_t GetOffset() const { return offset_; }

private:
  DataType data_type_;
  AttributeUsage attribute_usage_;
  bool normalize_{false};
  std::size_t offset_{0};
  friend class VertexFormat;
};

} // namespace Gloom

#endif // VERTEX_ATTRIBUTE_H