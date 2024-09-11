#version 460 core

struct Material {
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;
};

struct PointLight {
  vec3 position;
  vec3 color;
  vec3 attenuation;
};

// IN
layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec2 in_uv;
layout (location = 3) in vec4 in_position_light_space;

// OUT
layout (location = 0) out vec4 out_color;

// UNIFORM
uniform sampler2D u_ambient_map;
uniform sampler2D u_diffuse_map;
uniform sampler2D u_specular_map;
uniform sampler2D u_shadow_map;

uniform vec3 u_camera_position;

#define POINT_LIGHT_COUNT (1)

uniform Material   u_material;
uniform PointLight u_point_lights[POINT_LIGHT_COUNT];

// SOURCE
float getShadow(vec4 position_light_space, PointLight light, vec3 fragment_position) {  
  vec3 projection_xyz = position_light_space.xyz / position_light_space.w;
  projection_xyz = projection_xyz * 0.5 + 0.5;
  
  float closest_depth = texture(u_shadow_map, projection_xyz.xy).r; 
  float current_depth = projection_xyz.z;

  vec3 light_direction = normalize(light.position - fragment_position);
  float bias = max(0.05 * (1.0 - dot(in_normal, light_direction)), 0.005);

  float shadow = 0.0;
  vec2 texel_size = 1.0 / textureSize(u_shadow_map, 0);

  for (int x = -1; x <= 1; ++x) {
    for (int y = -1; y <= 1; ++y) {
      float pcf_depth = texture(u_shadow_map, projection_xyz.xy + vec2(x, y) * texel_size).r; 
      shadow += current_depth - bias > pcf_depth  ? 1.0 : 0.0;        
    }    
  }

  shadow /= 9.0;
    
  if(projection_xyz.z > 1.0) {
    shadow = 0.0;
  }
        
  return shadow;
}

vec3 GetLight(Material material, PointLight point_light, vec3 camera_position, vec3 fragment_position) {
  vec3 L_direction = normalize(point_light.position - fragment_position);
  vec3 V_direction = normalize(camera_position      - fragment_position);
  vec3 H_direction = normalize(L_direction + V_direction);
  float NdotL = max(dot(in_normal, L_direction), 0.0);
  float NdotH = max(dot(in_normal, H_direction), 0.0);
  float D = distance(point_light.position, fragment_position);
  float attenuation = 1.0 / dot(point_light.attenuation, vec3(D * D, D, 1.0));  
  vec3 diffuse  = point_light.color * NdotL * material.diffuse;   
  vec3 specular = point_light.color * pow(NdotH, material.shininess) * material.specular;
  float shadow = getShadow(in_position_light_space, point_light, fragment_position);
  return (material.ambient + (1.0 - shadow) * (diffuse + specular)) * attenuation;
}

void main() {
  Material material = u_material;
  material.ambient  += texture(u_ambient_map,  in_uv).rgb;
  material.diffuse  += texture(u_diffuse_map,  in_uv).rgb;
  material.specular += texture(u_specular_map, in_uv).rgb;

  vec3 color = vec3(0.0);

  for (int i = 0; i < POINT_LIGHT_COUNT; i++) {
    color += GetLight(material, u_point_lights[i], u_camera_position, in_position);
  }

  out_color = vec4(color, 1.0);
}