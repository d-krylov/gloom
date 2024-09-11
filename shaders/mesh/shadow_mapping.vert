#version 460 core

// IN
layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec2 in_uv;

// UNIFORM
uniform mat4 u_model_matrix = mat4(1.0);
uniform mat4 u_light_space_matrix = mat4(1.0);

out gl_PerVertex {
  vec4 gl_Position;
};

void main() {
  gl_Position = u_light_space_matrix * u_model_matrix * vec4(in_position, 1.0);
}