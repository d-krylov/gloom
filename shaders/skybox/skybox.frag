#version 460 core

out vec4 out_color;

// IN
layout (location = 0) in vec3 in_uv;

uniform samplerCube skybox;

void main() {    
  out_color = texture(skybox, in_uv);
}