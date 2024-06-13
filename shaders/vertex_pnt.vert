#version 460 core

// IN
layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec2 in_uv;

// OUT
layout (location = 0) out vec3 out_normal;
layout (location = 1) out vec2 out_uv;
layout (location = 2) out vec3 out_fragment_position;

// UNIFORM
uniform mat4 u_view_matrix  = mat4(1.0);
uniform mat4 u_projection_matrix = mat4(1.0);
uniform mat4 u_model_matrix = mat4(1.0);

out gl_PerVertex {
  vec4 gl_Position;
};

void main() {
  gl_Position = u_projection_matrix * u_view_matrix * u_model_matrix * vec4(in_position, 1.0);
  out_normal = normalize(mat3(transpose(inverse(u_model_matrix))) * in_normal);
  out_fragment_position = vec3(u_model_matrix * vec4(in_position, 1.0));
  out_uv = in_uv;
}