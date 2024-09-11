#ifndef GLOOM_RENDERER_H
#define GLOOM_RENDERER_H

#include "gloom/graphics/include/graphics.h"
#include <memory>
#include <unordered_map>

namespace Gloom {

class Model;
class Camera;
class Transform;
class PointLight;

class Renderer {
public:
  Renderer(uint32_t width, uint32_t height);

  void Begin();

  void SetLights(const std::vector<PointLight> &point);
  void SetCamera(const Camera &camera);

  void Add(Model &model);
  void OnWindowSize(uint32_t width, uint32_t height);

  void Draw(Model &model, const Transform &transform, const PointLight &light,
            const Camera &camera);
  void DrawWithPasses(Model &model, const Transform &transform, const PointLight &light,
                      const Camera &camera);

protected:
  void DrawDepth(Model &model, const Transform &transform, const PointLight &light);

private:
  VertexBuffer vertex_buffer_;
  VertexArray vertex_array_;
  VertexArray dummy_vao_;
  std::unique_ptr<Framebuffer> framebuffer_;
  std::unique_ptr<Texture2D> color_texture_;
  std::unique_ptr<TextureDepth> depth_texture_;
  std::unique_ptr<Renderbuffer> renderbuffer_;
  std::unordered_map<std::string, std::size_t> offsets_;
};

} // namespace Gloom

#endif // GLOOM_RENDERER_H