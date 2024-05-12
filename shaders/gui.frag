#version 460

layout (location = 0) in vec2 in_fragment_uv;
layout (location = 1) in vec4 in_fragment_color;

uniform sampler2D u_texture;

layout (location = 0) out vec4 out_color;

void main() {
  out_color = in_fragment_color * texture(u_texture, in_fragment_uv.st);
}