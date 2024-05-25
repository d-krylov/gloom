#version 460 core

layout (location = 0) out vec4 FragColor;

layout (location = 0) in vec3 in_normal;
layout (location = 1) in vec2 in_uv;
layout (location = 2) in vec3 in_fragment_position;

uniform sampler2D u_texture;
uniform vec3 u_light_color = vec3(1.0);
uniform vec3 u_light_position = vec3(0.0, 3.0, 4.0);
uniform vec3 u_view_position = vec3(0.0, 0.0, 0.0);

float getDiffuse(vec3 light_direction) {
  return max(dot(light_direction, in_normal), 0.0);
}

float getSpecular(vec3 light_direction) {
  vec3 view_direction = normalize(u_view_position - in_fragment_position);
  vec3 halfway_direction = normalize(light_direction + view_direction);  
  return pow(max(dot(in_normal, halfway_direction), 0.0), 32.0);
}

void main() {
  vec3 color = vec3(0.0);
  if (textureQueryLevels(u_texture) != 0) {
    color = texture(u_texture, in_uv).xyz;
  } else {
    color = vec3(1.0, 1.0, 1.0);
  }
  float ambient = 0.1;
  vec3 light_direction = normalize(u_light_position - in_fragment_position);
  float diffuse = getDiffuse(light_direction);
  float specular = 0.5 * getSpecular(light_direction);
  color *= (ambient + diffuse + specular) * u_light_color;
  FragColor = vec4(color, 1.0);
}