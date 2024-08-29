#version 460 core

// IN
layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec2 in_uv;

// OUT
layout (location = 0) out vec4 out_color;

// UINFORM
struct PointLight {
  vec3 position;
  vec3 color;
  vec3 attenuation;
};

struct Material {
  sampler2D ambient_map;
  sampler2D diffuse_map;
  sampler2D specular_map;
  vec3 ambient_color;
  vec3 diffuse_color;
  vec3 specular_color;
  float shininess;
};

#define POINT_LIGHT_COUNT (1)

uniform PointLight u_point_lights[POINT_LIGHT_COUNT];
uniform Material u_material;

uniform vec3 u_camera_position   = vec3(0.0, 0.0, 0.0);
uniform vec3 has_textures = vec3(1.0, 1.0, 1.0);

vec3 GetPointLight(Material material, PointLight point_light, vec3 camera_position, vec3 fragment_position) {
  vec3 AMBIENT  = texture(material.ambient_map,  in_uv).rgb * has_textures.x;
  vec3 DIFFUSE  = texture(material.diffuse_map,  in_uv).rgb * has_textures.y;
  vec3 SPECULAR = texture(material.specular_map, in_uv).rgb * has_textures.z;
  vec3 L_direction = normalize(point_light.position - fragment_position);
  vec3 V_direction = normalize(camera_position      - fragment_position);
  vec3 H_direction = normalize(L_direction + V_direction);
  float D = distance(point_light.position, fragment_position);
  float attenuation = 1.0 / dot(point_light.attenuation, vec3(D * D, D, 1.0));  
  float NdotL = max(dot(in_normal, L_direction), 0.0);
  float NdotH = max(dot(in_normal, H_direction), 0.0);
  vec3 ambient  = AMBIENT.rgb;
  vec3 diffuse  = point_light.color * NdotL * DIFFUSE.rgb;   
  vec3 specular = point_light.color * pow(NdotH, material.shininess) * SPECULAR.rgb;
  return (ambient + diffuse + specular) * attenuation;
}

void main() {

  vec3 color = vec3(0.0);

  for (int i = 0; i < POINT_LIGHT_COUNT; i++) {
    color += GetPointLight(u_material, u_point_lights[i], u_camera_position, in_position);
  }

  out_color = vec4(color, 1.0);
}