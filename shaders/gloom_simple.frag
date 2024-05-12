#version 460

layout (location = 0) in vec3 v_normal;
layout (location = 1) in vec3 v_fragment_position;

layout (location = 0) out vec4 fragColor;

uniform vec3 ViewPosition = vec3(0.0, 5.0, 11.0);

void main() {
  vec3 LightColor = vec3(0.9, 0.8, 0.8);
  vec3 LightPosition = vec3(5000.0, 5000.0, 5000.0);
  vec3 ObjectColor = vec3(0.2, 0.8, 0.4);

  float AmbientStrength = 0.3;
  vec3 ambient = AmbientStrength * LightColor;

  vec3 n = normalize(v_normal);
  vec3 LightDirection = normalize(LightPosition - v_fragment_position);
  float d = max(dot(n, LightDirection), 0.0);
  vec3 diffuse = d * LightColor;

  vec3 ViewDirection = normalize(ViewPosition - v_fragment_position);

  vec3 HalfwayDirection = normalize(LightDirection + ViewDirection);  
  float specular = pow(max(dot(n, HalfwayDirection), 0.0), 32.0);

  vec3 color = (ambient + diffuse + specular) * ObjectColor;

  fragColor = vec4(color, 1.0);
}