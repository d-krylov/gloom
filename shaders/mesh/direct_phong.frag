#version 460 core

// IN
layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec2 in_uv;

// OUT
layout (location = 0) out vec4 out_color;

// UINFORM
struct Light {
  vec3 position;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

uniform Light u_light;

uniform vec3 u_view_position = vec3(0.0, 0.0, 0.0);

struct Material {
  sampler2D ambient_map;
  sampler2D diffuse_map;
  sampler2D specular_map;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;
};

uniform Material u_material;

void main() {

  vec3 ambient = u_light.ambient * (u_material.ambient + texture(u_material.ambient_map, in_uv).xyz);

  // diffuse 
  vec3 light_direction = normalize(u_light.position - in_position);
  float NdotL = max(dot(in_normal, light_direction), 0.0);

  vec3 diffuse = u_light.diffuse * NdotL * (u_material.diffuse + texture(u_material.diffuse_map, in_uv).xyz);  

  // specular
  vec3 view_direction = normalize(u_view_position - in_position);
  vec3 reflect_direction = reflect(-light_direction, in_normal);  
  float ks = pow(max(dot(view_direction, reflect_direction), 0.0), u_material.shininess);
  vec3 specular = u_light.specular * ks * texture(u_material.specular_map, in_uv).xyz;  

  vec3 color = ambient + diffuse + specular;

  out_color = vec4(color, 1.0);
}