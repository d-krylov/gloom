#include "vertex_format.h"

namespace Gloom {

VertexFormat::VertexFormat(
    const std::initializer_list<VertexAttribute> &attributes) {
  attributes_.reserve(attributes.size());
  for (auto attribute : attributes) {
    AddAttribute(attribute);
  }
}

void VertexFormat::AddAttribute(const VertexAttribute &attribute) {
  attributes_.emplace_back(attribute);
  attributes_.back().offset_ = stride_;
  stride_ += attribute.GetSize();
}

} // namespace Gloom