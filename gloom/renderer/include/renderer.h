#ifndef GLOOM_RENDERER_H
#define GLOOM_RENDERER_H

#include "graphics/include/graphics.h"
#include "mesh/include/model.h"
#include "scene/include/camera.h"
#include "scene/include/light.h"

namespace Gloom {

class Renderer {
public:
  Renderer();

  void SetCamera(const Camera &camera, GraphicsPipeline &graphics_pipeline);
  void SetPointLights(std::span<const PointLight> points, GraphicsPipeline &graphics_pipeline);

  void Add(Model &model);

protected:
};

} // namespace Gloom

#endif // GLOOM_RENDERER_H