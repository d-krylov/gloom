#ifndef VERTEX_ATTRIBUTE_H
#define VERTEX_ATTRIBUTE_H

#include "graphics_types.h"

namespace Gloom {

class VertexFormat;

class VertexAttribute {
public:
  VertexAttribute(Types::DataType type, bool normalize = false,
                  Types::AttributeUsage usage = Types::AttributeUsage::NONE)
    : data_type_(type), normalize_(normalize), attribute_usage_(usage) {}

  [[nodiscard]] Types::DataType GetDataType() const { return data_type_; }
  [[nodiscard]] Types::AttributeUsage GetUsage() const { return attribute_usage_; }
  [[nodiscard]] std::size_t GetSize() const { return Types::GetSize(data_type_); }
  [[nodiscard]] bool IsFloat() const { return (GetComponentType() == Types::CoreType::FLOAT); }
  [[nodiscard]] bool IsRGBA() const { return (GetDataType() == Types::DataType::BVECTOR4); }

  [[nodiscard]] std::size_t GetComponentCount() const {
    return Types::GetComponentCount(data_type_);
  }

  [[nodiscard]] Types::CoreType GetComponentType() const {
    return Types::GetComponentType(data_type_);
  }

  [[nodiscard]] bool IsDouble() const {
    return (GetComponentType() == Types::CoreType::DOUBLE);
  }

  [[nodiscard]] bool Normalize() const { return normalize_; }
  [[nodiscard]] std::size_t GetOffset() const { return offset_; }

private:
  Types::DataType data_type_;
  Types::AttributeUsage attribute_usage_;
  bool normalize_{false};
  std::size_t offset_{0};
  friend class VertexFormat;
};

} // namespace Gloom

#endif // VERTEX_ATTRIBUTE_H