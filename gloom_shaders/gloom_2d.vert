#version 460 core

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_color;
layout (location = 2) in vec2 in_uv;

layout (location = 0) out vec3 color;
layout (location = 1) out vec2 uv;

void main() {
  gl_Position = vec4(in_position, 1.0);
  color = in_color;
  uv = in_uv;
}