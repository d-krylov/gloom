#include "vertex_array.h"
#include "gloom_assert.h"

namespace Gloom {

VertexArray::VertexArray() { glCreateVertexArrays(1, &vertex_array_); }

VertexArray::~VertexArray() { glDeleteVertexArrays(1, &vertex_array_); }

void VertexArray::Bind() { glBindVertexArray(vertex_array_); }

void VertexArray::SetIndexBuffer(const Buffer &buffer) {
  CORE_VERIFY(buffer.GetTarget() == Types::BufferTarget::ELEMENT_ARRAY_BUFFER);
  glVertexArrayElementBuffer(vertex_array_, buffer);
}

void VertexArray::AddVertexBuffer(const VertexBuffer &vbo) {
  AddVertexBufferAndFormat(vbo, vbo.GetFormat());
}

void VertexArray::AddVertexBufferAndFormat(const Buffer &buffer,
                                           const VertexFormat &vertex_format) {
  CORE_VERIFY(buffer.GetTarget() == Types::BufferTarget::ARRAY_BUFFER);
  glVertexArrayVertexBuffer(vertex_array_, current_binding_, buffer, 0,
                            vertex_format.GetStride());
  SetVertexFormat(vertex_format);
  UpdateBinding();
}

void VertexArray::SetVertexFormat(const VertexFormat &vertex_format) {
  const auto &attributes = vertex_format.GetAttributes();
  for (uint32_t i = 0; i < attributes.size(); i++) {
    auto attribute = attributes[i];
    auto binding = GetBinding();
    if (attribute.IsFloat()) {
      glVertexArrayAttribFormat(vertex_array_, i + binding, attribute.GetComponentCount(),
                                static_cast<uint32_t>(attribute.GetComponentType()),
                                attribute.Normalize(), attribute.GetOffset());
    } else if (attribute.IsDouble()) {
      glVertexArrayAttribLFormat(vertex_array_, i + binding, attribute.GetComponentCount(),
                                 static_cast<uint32_t>(attribute.GetComponentType()),
                                 attribute.GetOffset());
    } else {
      glVertexArrayAttribIFormat(vertex_array_, i + binding, attribute.GetComponentCount(),
                                 static_cast<uint32_t>(attribute.GetComponentType()),
                                 attribute.GetOffset());
    }
    glEnableVertexArrayAttrib(vertex_array_, i + binding);
    glVertexArrayAttribBinding(vertex_array_, i + binding, binding);
    glVertexArrayBindingDivisor(vertex_array_, i + binding, 0);
  }
}

} // namespace Gloom