#version 460 core

struct Material {
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

// IN
layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;

// OUT
layout (location = 0) out vec4 out_color;

uniform vec3 u_camera_position = vec3(0.0, 0.0, 0.0);
uniform vec3 u_light_direction = vec3(1.0, 1.0, 1.0);

vec3 GetLight(Material material, vec3 light_direction, vec3 camera_position, vec3 fragment_position) {
  vec3 V_direction = normalize(camera_position - fragment_position);
  vec3 H_direction = normalize(light_direction + V_direction); 
  float NdotL = max(dot(in_normal, light_direction), 0.0);
  float NdotH = max(dot(in_normal, H_direction), 0.0);
  vec3 diffuse  = NdotL * material.diffuse;   
  vec3 specular = pow(NdotH, 32.0) * material.specular;
  return (material.ambient + diffuse + specular);
}

void main() {

  vec3 color = vec3(0.0);

  Material material;

  material.ambient = vec3(0.2, 0.2, 0.2);
  material.diffuse = vec3(0.2, 0.6, 0.2);
  material.specular = vec3(0.2, 0.2, 0.6);

  color += GetLight(material, u_light_direction, u_camera_position, in_position);

  out_color = vec4(color, 1.0);
}