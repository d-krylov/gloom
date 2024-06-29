#version 460 core

layout (quads, fractional_odd_spacing, ccw) in;

// UNIFORM
uniform mat4 u_view_matrix  = mat4(1.0);
uniform mat4 u_projection_matrix = mat4(1.0);
uniform mat4 u_model_matrix = mat4(1.0);
uniform sampler2D u_height_map;

// IN
layout (location = 0) in vec2 in_uv[];

// OUT
layout (location = 0) out float out_height;
layout (location = 1) out vec3  out_normal;

void main() {  
  float u = gl_TessCoord.x;
  float v = gl_TessCoord.y;

  vec2 t00 = in_uv[0];
  vec2 t01 = in_uv[1];
  vec2 t10 = in_uv[2];
  vec2 t11 = in_uv[3];

  vec2 t0 = mix(t00, t01, v);
  vec2 t1 = mix(t11, t10, v);
  vec2 uv = mix(t0, t1, u);

  out_height = texture(u_height_map, uv).y * 64.0 - 16.0;

  vec4 p00 = gl_in[0].gl_Position;
  vec4 p01 = gl_in[1].gl_Position;
  vec4 p10 = gl_in[2].gl_Position;
  vec4 p11 = gl_in[3].gl_Position;

  vec4 v1 = p01 - p00;
  vec4 v2 = p11 - p00;
  
  vec4 normal = normalize(vec4(cross(v1.xyz, v2.xyz), 0));
  
  out_normal = normal.xyz;

  vec4 p0 = mix(p00, p01, v);
  vec4 p1 = mix(p11, p10, v);
  vec4 p =  mix(p0, p1, u);

  p += normal * out_height;

  gl_Position = u_projection_matrix * u_view_matrix * u_model_matrix * p;
}