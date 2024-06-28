#version 460 core

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec2 in_uv;

layout (location = 0) out vec3 out_uv;

uniform mat4 u_view_matrix  = mat4(1.0);
uniform mat4 u_projection_matrix = mat4(1.0);

out gl_PerVertex {
  vec4 gl_Position;
};

void main() {
  out_uv = in_position;
  vec4 position = u_projection_matrix * u_view_matrix * vec4(in_position, 1.0);
  gl_Position = position.xyww;
}  