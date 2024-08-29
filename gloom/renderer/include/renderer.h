#ifndef GLOOM_RENDERER_H
#define GLOOM_RENDERER_H

#include "gloom/graphics/include/graphics.h"
#include <unordered_map>

namespace Gloom {

class Model;
class Camera;
class Transform;
class PointLight;

class Renderer {
public:
  Renderer();

  void Begin();

  void SetLights(const std::vector<PointLight> &point);
  void SetCamera(const Camera &camera);
  void Draw(Model &model, const Transform &transform);
  void Add(Model &model);

private:
  VertexBuffer vertex_buffer_;
  VertexArray vertex_array_;
  GraphicsPipeline graphics_pipeline_;
  std::unordered_map<std::string, std::size_t> offsets_;
};

} // namespace Gloom

#endif // GLOOM_RENDERER_H