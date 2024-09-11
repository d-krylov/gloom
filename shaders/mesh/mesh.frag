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
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;
};

#define POINT_LIGHT_COUNT (1)

uniform PointLight u_point_lights[POINT_LIGHT_COUNT];

uniform Material u_material;

uniform sampler2D u_ambient_map;
uniform sampler2D u_diffuse_map;
uniform sampler2D u_specular_map;

uniform vec3 u_camera_position   = vec3(0.0, 0.0, 0.0);

vec3 GetPointLight(Material material, PointLight point_light, vec3 camera_position, vec3 fragment_position) {
  vec3 L_direction = normalize(point_light.position - fragment_position);
  vec3 V_direction = normalize(camera_position      - fragment_position);
  vec3 H_direction = normalize(L_direction + V_direction);
  float D = distance(point_light.position, fragment_position);
  float attenuation = 1.0 / dot(point_light.attenuation, vec3(D * D, D, 1.0));  
  float NdotL = max(dot(in_normal, L_direction), 0.0);
  float NdotH = max(dot(in_normal, H_direction), 0.0);
  vec3 diffuse  = point_light.color * NdotL * material.diffuse;   
  vec3 specular = point_light.color * pow(NdotH, material.shininess) * material.specular;
  return (material.ambient + diffuse + specular) * attenuation;
}

void main() {

  vec3 color = vec3(0.0);

  Material material = u_material;

  material.ambient  += texture(u_ambient_map,  in_uv).rgb;
  material.diffuse  += texture(u_diffuse_map,  in_uv).rgb;
  material.specular += texture(u_specular_map, in_uv).rgb;

  for (int i = 0; i < POINT_LIGHT_COUNT; i++) {
    color += GetPointLight(material, u_point_lights[i], u_camera_position, in_position);
  }

  out_color = vec4(color, 1.0);
}