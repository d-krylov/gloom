# Uniforms

## Vertex Shader

```
uniform mat4 u_view_matrix;
uniform mat4 u_projection_matrix;
uniform mat4 u_model_matrix;
```

## Fragment Shader

```
struct PointLight {
  vec3 position;
  vec3 color;
  vec3 attenuation;
};

uniform PointLight u_point_lights[];
```

```
uniform sampler2D u_ambient_map;
uniform sampler2D u_diffuse_map;
uniform sampler2D u_specular_map;
```

```
struct Material {
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;
};

Material u_material;
```
