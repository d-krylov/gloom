#ifndef GLOOM_MATERIAL_H
#define GLOOM_MATERIAL_H

#include <array>
#include <string>

namespace Gloom {

struct TextureNames {
  std::string ambient_;
  std::string diffuse_;
  std::string specular_;
  std::string bump_;
};

struct Material {
  float shininess;
  TextureNames names_;
};

} // namespace Gloom

#endif // GLOOM_MATERIAL_H