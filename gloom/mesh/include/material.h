#ifndef GLOOM_MATERIAL_H
#define GLOOM_MATERIAL_H

#include <array>
#include <string>

namespace Gloom {

enum TextureType { AMBIENT = 0, DIFFUSE, SPECULAR, BUMP, COUNT };

struct Material {

  [[nodiscard]] bool HasTexture(TextureType type) const { return textures_[type].empty() == false; }
  [[nodiscard]] const std::string &GetName(TextureType type) const { return textures_[type]; }

  float shininess;
  std::array<std::string, TextureType::COUNT> textures_;
};

} // namespace Gloom

#endif // GLOOM_MATERIAL_H