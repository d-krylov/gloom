#version 460 core

layout (vertices = 4) out;

// IN
layout (location = 0) in vec2 in_uv[];

// OUT
layout (location = 0) out vec2 out_uv[];

void main() {

  gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;

  out_uv[gl_InvocationID] = in_uv[gl_InvocationID];

  if (gl_InvocationID == 0) {
    gl_TessLevelOuter[0] = 64;
    gl_TessLevelOuter[1] = 64;
    gl_TessLevelOuter[2] = 64;
    gl_TessLevelOuter[3] = 64;

    gl_TessLevelInner[0] = 64;
    gl_TessLevelInner[1] = 64;
  }
}