#version 460

layout (location = 0) in vec2 in_fragment_uv;

uniform sampler2D u_texture;

layout (location = 0) out vec4 out_color;

const float offset = 1.0 / 300.0;  

void main() {
  vec2 offsets[9] = vec2[](
    vec2(-offset,  offset),
    vec2( 0.0f,    offset),
    vec2( offset,  offset),
    vec2(-offset,  0.0f),
    vec2( 0.0f,    0.0f),
    vec2( offset,  0.0f),
    vec2(-offset, -offset),
    vec2( 0.0f,   -offset),
    vec2( offset, -offset)    
  );

  float kernel[9] = float[](
    1, 1, 1,
    1, -8, 1,
    1, 1, 1
  );
    
  vec3 sampleTex[9];
  for(int i = 0; i < 9; i++) {
    sampleTex[i] = texture(u_texture, in_fragment_uv.st + offsets[i]).xyz;
  }
  
  vec3 color = vec3(0.0);
  for(int i = 0; i < 9; i++) {
    color += sampleTex[i] * kernel[i];
  }

  out_color = vec4(color, 1.0);
}