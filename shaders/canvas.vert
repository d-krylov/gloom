#version 460

layout (location = 0) out vec2 out_fragment_uv;

void main() {
  vec2 position = vec2(gl_VertexID % 2, gl_VertexID / 2) * 4.0 - 1;
  out_fragment_uv = vec2((gl_VertexID << 1) & 2, gl_VertexID & 2);
  gl_Position = vec4(position, 0.0, 1.0);
}