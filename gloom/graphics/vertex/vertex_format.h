#ifndef VERTEX_FORMAT_H
#define VERTEX_FORMAT_H

#include "vertex_attribute.h"
#include <initializer_list>
#include <vector>

namespace Gloom {

class VertexFormat {
public:
  VertexFormat(const std::initializer_list<VertexAttribute> &attributes);

  [[nodiscard]] std::size_t GetStride() const { return stride_; }

  auto begin() { return attributes_.begin(); }
  auto end() { return attributes_.end(); }
  auto begin() const { return attributes_.begin(); }
  auto end() const { return attributes_.end(); }

protected:
  void AddAttribute(const VertexAttribute &attributed);

private:
  std::size_t stride_{0};
  std::vector<VertexAttribute> attributes_;
};

} // namespace Gloom

#endif // VERTEX_FORMAT_H