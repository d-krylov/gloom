#ifndef GLOOM_MATERIAL_H
#define GLOOM_MATERIAL_H

#include "graphics/texture/texture.h"
#include <memory>

namespace Gloom {

struct MaterialProperties {
  Vector3f ambient_;
  Vector3f diffuse_;
  Vector3f specular_;
  Vector3f transmittance_;
  Vector3f emission_;
  float shininess_;
  float ior_;
  float dissolve_;
};

class Material {
public:
public:
  std::shared_ptr<MaterialProperties> properties_;
  std::shared_ptr<Texture> ambient_texture_;
  std::shared_ptr<Texture> diffuse_texture_;
  std::shared_ptr<Texture> specular_texture_;
};

struct PBRMaterialProperties {
  float roughness_;
  float metallic_;
  float sheen_;
  float clearcoat_thickness_;
  float clearcoat_roughness_;
  float anisotropy_;
  float anisotropy_rotation_;
};

class PBRMaterial {
public:
  std::shared_ptr<Texture> roughness_texture_;
  std::shared_ptr<Texture> metallic_texture_;
  std::shared_ptr<Texture> normal_texture_;
};

} // namespace Gloom

#endif // GLOOM_MATERIAL_H