#version 410 core

// IN
layout (location = 0) in float in_height;
layout (location = 1) in vec3  in_normal;

// OUT
layout (location = 0) out vec4 out_color;

uniform vec3 u_light_direction = vec3(0.0, 1.0, 0.0);

void main() {
  float h = (in_height + 16) / 64.0f;

  vec3 ambient = mix(vec3(h), vec3(0.1, 1.0, 1.0), h);

  vec3 light_direction = normalize(u_light_direction);

  // diffuse 
  float NdotL = max(dot(in_normal, light_direction), 0.0);

  vec3 diffuse = NdotL * vec3(1.0, 1.0, 0.1);
    
  vec3 color = ambient + diffuse;




  out_color = vec4(color, 1.0);
}