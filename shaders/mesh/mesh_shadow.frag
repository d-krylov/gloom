#version 460 core

// IN
layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec2 in_uv;
layout (location = 3) in vec4 in_position_light_space;

// OUT
layout (location = 0) out vec4 out_color;

// UNIFORM



float getShadow(vec4 position_light_space) {  
  vec3 projection_xyz = position_light_space.xyz / position_light_space.w;
  projection_xyz = projection_xyz * 0.5 + 0.5;
  
  float closestDepth = texture(shadowMap, projCoords.xy).r; 
  float currentDepth = projCoords.z;
  vec3 normal = normalize(fs_in.Normal);
  vec3 lightDir = normalize(lightPos - fs_in.FragPos);
  float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);

  float shadow = 0.0;
  vec2 texelSize = 1.0 / textureSize(shadowMap, 0);

  for(int x = -1; x <= 1; ++x) {
    for(int y = -1; y <= 1; ++y) {
      float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;        
    }    
  }
  shadow /= 9.0;
    
  if(projCoords.z > 1.0)
    shadow = 0.0;
        
  return shadow;
}

void main() {


  out_color = vec4(color, 1.0);
}