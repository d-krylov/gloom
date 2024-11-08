#version 460

vec3 box_vertices[8] = vec3[8](
  vec3(-0.5, -0.5, +0.5),
  vec3(+0.5, -0.5, +0.5),
  vec3(+0.5, +0.5, +0.5),
  vec3(-0.5, +0.5, +0.5),
  vec3(-0.5, -0.5, -0.5),
  vec3(+0.5, -0.5, -0.5),
  vec3(+0.5, +0.5, -0.5),
  vec3(-0.5, +0.5, -0.5)
);

vec3 box_normals[6] = vec3[6](
  vec3(+0.0, +0.0, +1.0),
  vec3(+1.0, +0.0, +0.0),
  vec3(+0.0, +0.0, +1.0),
  vec3(-1.0, +0.0, +0.0),
  vec3(+0.0, +1.0, +0.0),
  vec3(+0.0, -1.0, +0.0)
);

int box_indices[36] = int[36](
  0, 1, 2, 2, 3, 0,
  1, 5, 6, 6, 2, 1,
  5, 4, 7, 7, 6, 5,
  4, 0, 3, 3, 7, 4,
  3, 2, 6, 6, 7, 3,
  4, 5, 1, 1, 0, 4
);

// UNIFORM
uniform mat4 u_view_matrix  = mat4(1.0);
uniform mat4 u_projection_matrix = mat4(1.0);

layout(std430, binding = 0) buffer Model {
  mat4 model[];
};

// OUT
layout (location = 0) out vec3 out_position;
layout (location = 1) out vec3 out_normal;

out gl_PerVertex {
  vec4 gl_Position;
};

void main() {
  vec3 position = box_vertices[box_indices[gl_VertexID]];
  vec3 normal = box_normals[gl_VertexID / 6];
  mat4 model_matrix = model[gl_InstanceID];
  out_normal = normalize(mat3(transpose(inverse(model_matrix))) * normal);
  out_position = vec3(model_matrix * vec4(position, 1.0));
  gl_Position = u_projection_matrix * u_view_matrix * model_matrix * vec4(position, 1.0);
}