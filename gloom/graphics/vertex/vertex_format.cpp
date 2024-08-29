#include "vertex_format.h"

namespace Gloom {

VertexFormat::VertexFormat(const std::initializer_list<VertexAttribute> &attributes) {
  attributes_.reserve(attributes.size());
  for (auto attribute : attributes) {
    AddAttribute(attribute);
  }
}

void VertexFormat::AddAttribute(const VertexAttribute &attribute) {
  auto &new_attribute = attributes_.emplace_back(attribute);
  new_attribute.offset_ = stride_;
  stride_ += new_attribute.GetSize();
}

} // namespace Gloom