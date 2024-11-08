#ifndef GLOOM_TEXTURE_CUBEMAP_H
#define GLOOM_TEXTURE_CUBEMAP_H

#include "core/include/cubemap.h"
#include "texture.h"

namespace Gloom {

class TextureCubemap : public Texture {
public:
  TextureCubemap(const CubeMap &cubemap)
    : Texture(cubemap.GetWidth(), cubemap.GetHeight(), 1, TextureTarget::TEXTURE_CUBE_MAP,
              cubemap.GetFormat(), false, MinFilter::LINEAR, MagFilter::LINEAR,
              WrapMode::CLAMP_TO_EDGE, WrapMode::CLAMP_TO_EDGE, WrapMode::CLAMP_TO_EDGE) {
    for (int32_t i = 0; i < 6; ++i) {
      auto data = cubemap.GetData(i);
      SetData(data, 0, 0, i);
    }
  }
};

} // namespace Gloom

#endif // GLOOM_TEXTURE_CUBEMAP_H