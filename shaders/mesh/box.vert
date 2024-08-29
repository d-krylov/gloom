#version 460

struct Vertex {
  vec3 position;
  vec3 normal;
  vec2 uv;
};

Vertex box_vertices[36] = Vertex[36](
  Vertex(vec3(+0.5, +0.5, +0.5), vec3(+1.0, +0.0, +0.0), vec2(1.0, 0.0)), // top-left
  Vertex(vec3(+0.5, -0.5, -0.5), vec3(+1.0, +0.0, +0.0), vec2(0.0, 1.0)), // bottom-right
  Vertex(vec3(+0.5, +0.5, -0.5), vec3(+1.0, +0.0, +0.0), vec2(1.0, 1.0)), // top-right
  Vertex(vec3(+0.5, -0.5, -0.5), vec3(+1.0, +0.0, +0.0), vec2(0.0, 1.0)), // bottom-right
  Vertex(vec3(+0.5, +0.5, +0.5), vec3(+1.0, +0.0, +0.0), vec2(1.0, 0.0)), // top-left
  Vertex(vec3(+0.5, -0.5, +0.5), vec3(+1.0, +0.0, +0.0), vec2(0.0, 0.0)), // bottom-left
  // Left face
  Vertex(vec3(-0.5, +0.5, +0.5), vec3(-1.0, +0.0, +0.0), vec2(1.0, 0.0)), // top-right
  Vertex(vec3(-0.5, +0.5, -0.5), vec3(-1.0, +0.0, +0.0), vec2(1.0, 1.0)), // top-left
  Vertex(vec3(-0.5, -0.5, -0.5), vec3(-1.0, +0.0, +0.0), vec2(0.0, 1.0)), // bottom-left
  Vertex(vec3(-0.5, -0.5, -0.5), vec3(-1.0, +0.0, +0.0), vec2(0.0, 1.0)), // bottom-left
  Vertex(vec3(-0.5, -0.5, +0.5), vec3(-1.0, +0.0, +0.0), vec2(0.0, 0.0)), // bottom-right
  Vertex(vec3(-0.5, +0.5, +0.5), vec3(-1.0, +0.0, +0.0), vec2(1.0, 0.0)), // top-right
  // Top face
  Vertex(vec3(-0.5, +0.5, -0.5), vec3(+0.0, +1.0, +0.0), vec2(0.0, 1.0)), // top-left
  Vertex(vec3(+0.5, +0.5, +0.5), vec3(+0.0, +1.0, +0.0), vec2(1.0, 0.0)), // bottom-right
  Vertex(vec3(+0.5, +0.5, -0.5), vec3(+0.0, +1.0, +0.0), vec2(1.0, 1.0)), // top-right
  Vertex(vec3(+0.5, +0.5, +0.5), vec3(+0.0, +1.0, +0.0), vec2(1.0, 0.0)), // bottom-right
  Vertex(vec3(-0.5, +0.5, -0.5), vec3(+0.0, +1.0, +0.0), vec2(0.0, 1.0)), // top-left
  Vertex(vec3(-0.5, +0.5, +0.5), vec3(+0.0, +1.0, +0.0), vec2(0.0, 0.0)), // bottom-left
  // Bottom face
  Vertex(vec3(-0.5, -0.5, -0.5), vec3(+0.0, -1.0, +0.0), vec2(0.0, 1.0)), // top-right
  Vertex(vec3(+0.5, -0.5, -0.5), vec3(+0.0, -1.0, +0.0), vec2(1.0, 1.0)), // top-left
  Vertex(vec3(+0.5, -0.5, +0.5), vec3(+0.0, -1.0, +0.0), vec2(1.0, 0.0)), // bottom-left
  Vertex(vec3(+0.5, -0.5, +0.5), vec3(+0.0, -1.0, +0.0), vec2(1.0, 0.0)), // bottom-left
  Vertex(vec3(-0.5, -0.5, +0.5), vec3(+0.0, -1.0, +0.0), vec2(0.0, 0.0)), // bottom-right
  Vertex(vec3(-0.5, -0.5, -0.5), vec3(+0.0, -1.0, +0.0), vec2(0.0, 1.0)), // top-right
  // Front face
  Vertex(vec3(-0.5, -0.5, +0.5), vec3(+0.0, +0.0, +1.0), vec2(0.0, 0.0)), // bottom-left
  Vertex(vec3(+0.5, -0.5, +0.5), vec3(+0.0, +0.0, +1.0), vec2(1.0, 0.0)), // bottom-right
  Vertex(vec3(+0.5, +0.5, +0.5), vec3(+0.0, +0.0, +1.0), vec2(1.0, 1.0)), // top-right
  Vertex(vec3(+0.5, +0.5, +0.5), vec3(+0.0, +0.0, +1.0), vec2(1.0, 1.0)), // top-right
  Vertex(vec3(-0.5, +0.5, +0.5), vec3(+0.0, +0.0, +1.0), vec2(0.0, 1.0)), // top-left
  Vertex(vec3(-0.5, -0.5, +0.5), vec3(+0.0, +0.0, +1.0), vec2(0.0, 0.0)), // bottom-left
  // Back face
  Vertex(vec3(-0.5, -0.5, -0.5), vec3(+0.0, +0.0, -1.0), vec2(0.0, 0.0)), // Bottom-left
  Vertex(vec3(+0.5, +0.5, -0.5), vec3(+0.0, +0.0, -1.0), vec2(1.0, 1.0)), // top-right
  Vertex(vec3(+0.5, -0.5, -0.5), vec3(+0.0, +0.0, -1.0), vec2(1.0, 0.0)), // bottom-right
  Vertex(vec3(+0.5, +0.5, -0.5), vec3(+0.0, +0.0, -1.0), vec2(1.0, 1.0)), // top-right
  Vertex(vec3(-0.5, -0.5, -0.5), vec3(+0.0, +0.0, -1.0), vec2(0.0, 0.0)), // bottom-left
  Vertex(vec3(-0.5, +0.5, -0.5), vec3(+0.0, +0.0, -1.0), vec2(0.0, 1.0))  // top-left
);

// UNIFORM
uniform mat4 u_view_matrix  = mat4(1.0);
uniform mat4 u_projection_matrix = mat4(1.0);
uniform mat4 u_model_matrix = mat4(1.0);

layout (location = 0) out vec3 out_position;
layout (location = 1) out vec3 out_normal;
layout (location = 2) out vec2 out_uv;

out gl_PerVertex {
  vec4 gl_Position;
};

void main() {
  Vertex v = box_vertices[gl_VertexID];
  out_normal = normalize(mat3(transpose(inverse(u_model_matrix))) * v.normal);
  out_position = vec3(u_model_matrix * vec4(v.position, 1.0));
  out_uv = v.uv;
  gl_Position = u_projection_matrix * u_view_matrix * u_model_matrix * vec4(v.position, 1.0);
}