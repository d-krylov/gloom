#version 460

// IN
layout (location = 0) in vec2 in_uv;

// OUT
layout (location = 0) out vec4 out_color;

// UNIFORM
uniform sampler2D u_texture;

vec3 ACES(const vec3 x) {
  const float a = 2.51;
  const float b = 0.03;
  const float c = 2.43;
  const float d = 0.59;
  const float e = 0.14;
  return clamp((x * (a * x + b)) / (x * (c * x + d) + e), 0.0, 1.0);
}

void main() {
  vec3 color = texture(u_texture, in_uv).xyz;

  color = ACES(color);

  out_color = vec4(color, 1.0);
}