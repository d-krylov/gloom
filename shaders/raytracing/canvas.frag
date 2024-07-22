#version 460

// IN
layout (location = 0) in vec2 in_uv;

// OUT
layout (location = 0) out vec4 out_color;

// UNIFORM
uniform sampler2D u_texture;

void main() {
  vec3 color = texture(u_texture, in_uv).xyz;

  out_color = vec4(color, 1.0);
}