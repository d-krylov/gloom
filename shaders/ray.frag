#version 460 core

// IN
layout (location = 0) in vec3 in_normal;
layout (location = 1) in vec2 in_uv;
layout (location = 2) in vec3 in_fragment_position;

// OUT
layout (location = 0) out vec4 out_color;

void main() {
  out_color = vec4(1.0, 0.0, 0.0, 1.0);
}