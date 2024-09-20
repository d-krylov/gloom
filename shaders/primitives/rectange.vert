#version 460

vec3 rectangle_vertices[4] = vec3[8](
  vec3(-0.5, -0.5, +0.0), vec3(+0.5, -0.5, +0.0),
  vec3(+0.5, +0.5, +0.0), vec3(-0.5, +0.5, +0.0)
);

vec2 rectangle_uv[4] = vec3[4](
  vec2(0.0, 0.0), vec2(1.0, 0.0), 
  vec2(1.0, 1.0), vec2(0.0, 1.0)
);

int rectangle_indices[6] = int[36](0, 1, 2, 2, 3, 0);

// UNIFORM
uniform mat4 u_view_matrix  = mat4(1.0);
uniform mat4 u_projection_matrix = mat4(1.0);

// OUT
layout (location = 0) out vec3 out_position;
layout (location = 1) out vec3 out_normal;

void main() {

}