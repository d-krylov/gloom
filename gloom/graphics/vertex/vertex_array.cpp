#include "vertex_array.h"
#include "gloom/graphics/buffer/index_buffer.h"
#include "gloom/graphics/buffer/vertex_buffer.h"

namespace Gloom {

VertexArray::VertexArray() { glCreateVertexArrays(1, &vertex_array_); }

VertexArray::~VertexArray() { glDeleteVertexArrays(1, &vertex_array_); }

VertexArray::VertexArray(const VertexBuffer &vbo, const IndexBuffer &ebo) : VertexArray(vbo) {
  glVertexArrayElementBuffer(vertex_array_, ebo);
}

VertexArray::VertexArray(const VertexBuffer &vbo) : VertexArray() {
  auto binding = vbo.GetBinding();
  auto &format = vbo.GetFormat();
  SetVertexFormat(format, binding);
  glVertexArrayVertexBuffer(vertex_array_, binding, vbo, 0, format.GetStride());
}

void VertexArray::SetVertexFormat(const VertexFormat &vertex_format, uint32_t binding) {
  for (auto it = vertex_format.begin(); it != vertex_format.end(); it++) {
    auto index = std::distance(vertex_format.begin(), it);
    auto count = it->GetComponentCount();
    auto type = uint16_t(it->GetComponentType());
    auto offset = it->GetOffset();
    if (it->IsFLOAT() || it->IsRGBA()) {
      bool normalize = it->Normalize();
      glVertexArrayAttribFormat(vertex_array_, index + binding, count, type, normalize, offset);
    } else if (it->IsDOUBLE()) {
      glVertexArrayAttribLFormat(vertex_array_, index + binding, count, type, offset);
    } else {
      glVertexArrayAttribIFormat(vertex_array_, index + binding, count, type, offset);
    }
    glEnableVertexArrayAttrib(vertex_array_, index + binding);
    glVertexArrayAttribBinding(vertex_array_, index + binding, binding);
    glVertexArrayBindingDivisor(vertex_array_, index + binding, 0);
  }
}

void VertexArray::Bind() { glBindVertexArray(vertex_array_); }

} // namespace Gloom