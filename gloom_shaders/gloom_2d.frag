#version 460 core

layout (location = 0) out vec4 FragColor;
  
layout (location = 0) in vec3 color;
layout (location = 1) in vec2 uv;

uniform sampler2D Texture;

void main() {
  FragColor = vec4(color, 0.0) * texture(Texture, uv);
}