#version 460 core

#define STEP_SIZE        0.5
#define EPSILON          0.001
#define MAXIMUM_STEPS    5000
#define FAR              1000.0
#define PI               3.141592653

struct Ray { vec3 origin; vec3 direction; };
struct Hit { float id; vec3 normal; vec3 position; };

struct PointLight { 
  vec3 position;
  vec3 color;
  vec3 attenuation;
};

struct Material {
  vec3 albedo;
  float metallic;
  float roughness;
};

struct Object {
  vec3 position;
  vec3 size;
  vec3 rotation;
  float material;
  float visible;
};

// IN
layout (location = 0) in vec3 in_fragment_uv;

// OUT
layout (location = 0) out vec4 out_color;

// SSBO
layout(binding = 0, std430) readonly buffer LightSSBO {
  PointLight v[];
} Lights;

layout(binding = 1, std430) readonly buffer ObjectSSBO {
  Object objects[];
} Objects;

layout(binding = 2, std430) readonly buffer MaterialSSBO {
  Material v[];
} Materials;

// UNIFORMS
uniform int material_count = 0;
const int N = 1;
uniform vec2 i_resolution = vec2(800.0, 600.0);

float sdSphere(vec3 p, float s) {
  return length(p) - s;
}

vec2 scene(in vec3 p) {
  vec2 ret = vec2(p.y, 0.0);

  for (int i = 0; i < N; i++) {
    Object object = Objects.objects[i];
    if (object.visible == 1.0) {
      ret = min(ret, sdSphere(p - object.position, object.size.x));
    }
  }

  return ret;
}

vec3 getNormal(in vec3 p) {
  const float h = 0.001; 
  const vec2 k = vec2(1.0, -1.0);
  vec3 n = vec3(0.0);
  return normalize(k.xyy * scene(p + k.xyy * h).x + 
                   k.yyx * scene(p + k.yyx * h).x + 
                   k.yxy * scene(p + k.yxy * h).x + 
                   k.xxx * scene(p + k.xxx * h).x);
}

Hit rayMarch(in Ray ray, float near) {
  Hit hit;
  hit.id = -1.0;
  float t = near;
  for (int i = 0; i < MAXIMUM_STEPS; i++) {
    vec3 p = ray.origin + ray.direction * t;
    vec2 d = scene(p);
    if (d.x < EPSILON) {
      hit.id = d.y;
      hit.position = p; hit.normal = getNormal(hit.position);
      break;
    }
    t += STEP_SIZE * d.x;
    if (t > FAR) { break; }
  }
  return hit;
}

// LIGHT CALCULATION

vec3 fresnelSchlick(float cosTheta, vec3 F0) {
  return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}

float distributionGGX(vec3 N, vec3 H, float roughness) {
  float a = pow(roughness, 4.0);
  float NdotH = max(dot(N, H), 0.0);
  float denom = (NdotH * NdotH * (a - 1.0) + 1.0);
  return a / (PI * denom * denom);
}

float geometrySchlickGGX(float NdotV, float roughness) {
  float k = 0.125 * (roughness + 1.0) * (roughness + 1.0);
  return NdotV / (NdotV * (1.0 - k) + k);
}

float geometrySmith(float NdotV, float NdotL, float roughness) {
  float ggx2 = geometrySchlickGGX(NdotV, roughness);
  float ggx1 = geometrySchlickGGX(NdotL, roughness);
  return ggx1 * ggx2;
}

vec3 GetLight(vec3 normal, Ray ray, vec3 light_direction, vec3 light_color, Material material) {
  float NdotL = max(dot(normal, light_direction), 0.0);
  float NdotV = max(dot(normal, -ray.direction), 0.0);
  vec3 halfway_direction = normalize(light_direction - ray.direction);
  vec3 F0 = mix(vec3(0.04), material.albedo, material.metallic);
  float NDF = distributionGGX(normal, halfway_direction, material.roughness); 
  float G = geometrySmith(NdotV, NdotL, material.roughness);  
  vec3  F = fresnelSchlick(max(dot(halfway_direction, -ray.direction), 0.0), F0);
  vec3 specular = NDF * G * F / (4.0 * NdotV * NdotL + 0.0001);
  vec3 kD = (vec3(1.0) - F) * (1.0 - material.metallic);
  vec3 Lo = (kD * material.albedo / PI + specular) * light_color * NdotL;
  return Lo;
}

void main() {
  vec2 uv = (2.0 * gl_FragCoord.xy - i_resolution.xy) / i_resolution.xy;
  
  uv.y *= i_resolution.y / i_resolution.x;
  
  vec3 color = vec3(0.0);

  Ray ray;
  ray.origin = vec3(0.0, 5.0, 2.0);
  ray.direction = normalize(vec3(uv, -1.0));

  Hit hit = rayMarch(ray, 0.0);
  
  if (hit.id != -1.0) {
    color.x = 1.0;
  }


  out_color = vec4(color, 1.0);
}

/*
    for (int i = 0; i < int(light_count); i++) {

      PointLight pL = Lights.v[i];
      Material material = Materials.v[int(hit.id) + 1];

      vec3 light_direction = normalize(pL.position - hit.position);

      color = 0.4 * material.albedo;

      color += GetLight(hit.normal, ray, light_direction, pL.color, material);
    }
*/