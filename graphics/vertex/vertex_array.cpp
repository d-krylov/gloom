#include "vertex_array.h"

namespace Gloom {

VertexArray::VertexArray() { glCreateVertexArrays(1, &vertex_array_); }

VertexArray::~VertexArray() { glDeleteVertexArrays(1, &vertex_array_); }

void VertexArray::Bind() { glBindVertexArray(vertex_array_); }

void VertexArray::SetIndexBuffer(const Buffer &buffer) {
  CORE_VERIFY(buffer.GetTarget() == Types::BufferTarget::ELEMENT_ARRAY_BUFFER);
  glVertexArrayElementBuffer(vertex_array_, buffer);
}

void VertexArray::AddVertexBuffer(const VertexBuffer &vbo) {
  auto binding = vbo.GetBinding();
  glVertexArrayVertexBuffer(vertex_array_, binding, vbo, 0, vbo.GetFormat().GetStride());
  SetVertexFormat(vbo.GetFormat(), binding);
}

void VertexArray::SetVertexFormat(const VertexFormat &vertex_format, uint32_t binding) {
  const auto &attributes = vertex_format.GetAttributes();
  for (uint32_t i = 0; i < attributes.size(); i++) {
    auto attribute = attributes[i];
    auto count = attribute.GetComponentCount();
    auto type = static_cast<uint32_t>(attribute.GetComponentType());
    auto offset = attribute.GetOffset();
    if (attribute.IsFloat() || attribute.IsRGBA()) {
      bool normalize = attribute.Normalize();
      glVertexArrayAttribFormat(vertex_array_, i + binding, count, type, normalize, offset);
    } else if (attribute.IsDouble()) {
      glVertexArrayAttribLFormat(vertex_array_, i + binding, count, type, offset);
    } else {
      glVertexArrayAttribIFormat(vertex_array_, i + binding, count, type, offset);
    }
    glEnableVertexArrayAttrib(vertex_array_, i + binding);
    glVertexArrayAttribBinding(vertex_array_, i + binding, binding);
    glVertexArrayBindingDivisor(vertex_array_, i + binding, 0);
  }
}

} // namespace Gloom