#version 460 core

#extension GL_ARB_bindless_texture : require

// IN
layout (location = 0) in vec3 in_normal;
layout (location = 1) in vec2 in_uv;
layout (location = 2) in vec3 in_fragment_position;
layout (location = 3) in flat int in_draw_id;

// OUT
layout (location = 0) out vec4 out_color;

// UINFORM
struct Light {
  vec3 position;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

uniform Light u_light;

uniform vec3 u_view_position = vec3(0.0, 0.0, 0.0);

// SSBOs
struct Material {
  sampler2D ambient_texture;
  sampler2D diffuse_texture;
  sampler2D specular_texture;
  float shininess;
};

layout(binding = 0, std430) readonly buffer ssbo {
  Material textures[];
};

void main() {
  Material material = textures[in_draw_id];

  vec3 ambient = light.ambient * texture(material.diffuse, in_uv).rgb;
  	
  // diffuse 
  vec3 light_direction = normalize(u_light.position - in_fragment_position);
  float NdotL = max(dot(in_normal, light_direction), 0.0);
  vec3 diffuse = u_light.diffuse * NdotL * texture(material.diffuse_texture, in_uv).rgb;  
    
  // specular
  vec3 view_direction = normalize(u_view_position - in_fragment_position);
  vec3 reflect_direction = reflect(-light_direction, in_normal);  
  float ks = pow(max(dot(view_direction, reflect_direction), 0.0), material.shininess);
  vec3 specular = light.specular * ks * texture(material.specular, in_uv).rgb;  
        
  vec3 color = ambient + diffuse + specular;
  out_color = vec4(color, 1.0);
}