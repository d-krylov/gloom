#version 460 core

// IN
layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec2 in_uv;

// OUT
layout (location = 0) out vec4 out_color;

// UNIFORM
uniform vec3 u_camera_position = vec3(0.0, 0.0, 0.0);
uniform vec3 u_light_direction = vec3(1.0, 1.0, 1.0);
uniform vec3 u_material_albedo = vec3(1.0, 1.0, 1.0);

void main() {

  vec3 color = vec3(0.0);



  out_color = vec4(color, 1.0);
}