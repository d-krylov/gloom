#version 460 core

layout (location = 0) out vec4 FragColor;
layout (location = 0) in vec2 uv;

uniform sampler2D Texture;

void main() {
  FragColor = texture(Texture, uv);
}