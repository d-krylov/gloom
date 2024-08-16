#include "renderer/include/direct_renderer.h"

namespace Gloom {

Renderer::Renderer()
  : vertex_array_(), vertex_buffer_(10_MiB, Vertex::GetFormat()),
    index_buffer_(BufferTarget::ELEMENT_ARRAY_BUFFER, 10_MiB) {}

void Renderer::Draw(const Mesh &mesh) {}

} // namespace Gloom