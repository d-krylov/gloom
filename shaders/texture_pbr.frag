#version 460 core
  
layout (location = 0) in vec3 in_normal;
layout (location = 1) in vec2 in_uv;
layout (location = 2) in vec3 in_fragment_position;

uniform sampler2D u_albedo;
uniform sampler2D u_normal;
uniform sampler2D u_metallic;
uniform sampler2D u_roughness;
uniform sampler2D u_ao;

uniform vec3 u_light_color = vec3(1.0);
uniform vec3 u_light_position = vec3(0.0, 3.0, 4.0);
uniform vec3 u_view_position = vec3(0.0, 0.0, 0.0);

vec3 getNormalFromMap() {
  vec3 tangent_normal = texture(u_normal, in_uv).xyz * 2.0 - 1.0;

  vec3 q1  = dFdx(in_fragment_position);
  vec3 q2  = dFdy(in_fragment_position);
  vec2 st1 = dFdx(in_uv);
  vec2 st2 = dFdy(in_uv);

  vec3 N =  normalize(in_normal);
  vec3 T =  normalize(q1 * st2.t - q2 * st1.t);
  vec3 B = -normalize(cross(N, T));
  
  mat3 TBN = mat3(T, B, N);

  return normalize(TBN * tangent_normal);
}

const float PI = 3.141592653589793;

float DistributionGGX(float NdotH, float a) {
  float a2 = a * a;
  float f = (NdotH * a2 - NdotH) * NdotH + 1.0;
  return a2 / (PI * f * f);
}

vec3 FresnelSchlick(float cosTheta, vec3 F0) {
  return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}

float SmithGGXCorrelated(float NdotV, float NdotL, float a) {
  float a2 = a * a;
  float GGXL = NdotV * sqrt((-NdotL * a2 + NdotL) * NdotL + a2);
  float GGXV = NdotL * sqrt((-NdotV * a2 + NdotV) * NdotV + a2);
  return 0.5 / (GGXV + GGXL);
}

float FresnelSchlick(float u, float f0, float f90) {
  return f0 + (f90 - f0) * pow(1.0 - u, 5.0);
}

float Burley(float NdotV, float NdotL, float LdotH, float roughness) {
  float f90 = 0.5 + 2.0 * roughness * LdotH * LdotH;
  float lightScatter = FresnelSchlick(NdotL, 1.0, f90);
  float viewScatter = FresnelSchlick(NdotV, 1.0, f90);
  return lightScatter * viewScatter * (1.0 / PI);
}

vec3 BRDF(vec3 normal, vec3 albedo, float metallic, float roughness) {
  vec3 view_direction = normalize(u_view_position - in_fragment_position);
  vec3 light_direction = normalize(u_light_position - in_fragment_position);
  vec3 halfway_direction = normalize(light_direction + view_direction);  

  float NdotV = abs(dot(normal, view_direction)) + 1e-5;
  float NdotL = clamp(dot(normal, light_direction), 0.0, 1.0);
  float NdotH = clamp(dot(normal, halfway_direction), 0.0, 1.0);
  float LdotH = clamp(dot(light_direction, halfway_direction), 0.0, 1.0);
  vec3 F0 = mix(vec3(0.4), albedo, metallic);
  float square_roughness = roughness * roughness;
  float D = DistributionGGX(NdotH, roughness);
  vec3  F = FresnelSchlick(LdotH, F0);
  float V = SmithGGXCorrelated(NdotV, NdotL, roughness);
  vec3 Fr = (D * V) * F;  
  vec3 Fd = albedo * Burley(NdotV, NdotL, LdotH, roughness);
  vec3 kD = (vec3(1.0) - F) * (1.0 - metallic);
  return (Fd * kD + Fr) * 4.0 * u_light_color * NdotL; 
}

layout (location = 0) out vec4 fragColor;

void main() {
  vec3  albedo    = 2.0 * pow(texture(u_albedo, in_uv).rgb, vec3(1.2));
  float metallic  = texture(u_metallic, in_uv).r;
  float roughness = texture(u_roughness, in_uv).r;

  vec3 N = getNormalFromMap();

  vec3 color = BRDF(N, albedo, metallic, roughness);

  fragColor = vec4(color, 0.0);
}