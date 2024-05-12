#version 460

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;

layout (location = 0) out vec3 v_normal;
layout (location = 1) out vec3 v_fragment_position;

uniform mat4 ViewMatrix  = mat4(1.0);
uniform mat4 ProjectionMatrix = mat4(1.0);
uniform mat4 ModelMatrix = mat4(1.0);

void main() {
  gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(in_position, 1.0);
  v_normal = mat3(transpose(inverse(ModelMatrix))) * in_normal;
  v_fragment_position = vec3(ModelMatrix * vec4(in_position, 1.0));
}