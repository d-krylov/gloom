#version 460

layout (location = 0) in vec2 in_position;
layout (location = 1) in vec2 in_uv;
layout (location = 2) in vec4 in_color;

uniform mat4 u_projection_matrix;

layout (location = 0) out vec2 out_fragment_uv;
layout (location = 1) out vec4 out_fragment_color;

void main() {
  out_fragment_uv = in_uv;
  out_fragment_color = in_color; 
  gl_Position = u_projection_matrix * vec4(in_position.xy, 0, 1);
}