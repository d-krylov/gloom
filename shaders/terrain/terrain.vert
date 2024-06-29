#version 460 core

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec2 in_uv;

layout (location = 0) out vec2 out_uv;

out gl_PerVertex {
  vec4 gl_Position;
};

void main() {
  gl_Position = vec4(in_position, 1.0);
  out_uv = in_uv;
}