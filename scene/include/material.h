#ifndef GLOOM_MATERIAL_H
#define GLOOM_MATERIAL_H

#include "texture.h"
#include <memory>

namespace Gloom {

class Material {
public:
public:
  Types::Vector3f ambient_;
  Types::Vector3f diffuse_;
  Types::Vector3f specular_;
  Types::Vector3f transmittance_;
  Types::Vector3f emission_;
  float shininess_;
  float ior_;
  float dissolve_;

  float roughness_;
  float metallic_;
  float sheen_;
  float clearcoat_thickness_;
  float clearcoat_roughness_;
  float anisotropy_;
  float anisotropy_rotation_;

  std::shared_ptr<Texture> ambient_texture_;
  std::shared_ptr<Texture> diffuse_texture_;
  std::shared_ptr<Texture> specular_texture_;

  std::shared_ptr<Texture> roughness_texture_;
  std::shared_ptr<Texture> metallic_texture_;
  std::shared_ptr<Texture> normal_texture_;
};

} // namespace Gloom

#endif // GLOOM_MATERIAL_H