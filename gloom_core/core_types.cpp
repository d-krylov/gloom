#include "gloom_core/include/core_types.h"

namespace Gloom {

float Radians(float degrees) { return PI * degrees / 180.0f; }
float Degrees(float radians) { return radians * 180.0f / PI; }

Matrix4f Translate(const Vector3f &v) { return linalg::translation_matrix(v); }

Matrix4f RotateX(float degrees) {
  return linalg::rotation_matrix(linalg::rotation_quat(X, Radians(degrees)));
}

Matrix4f RotateY(float degrees) {
  return linalg::rotation_matrix(linalg::rotation_quat(Y, Radians(degrees)));
}

Matrix4f RotateZ(float degrees) {
  return linalg::rotation_matrix(linalg::rotation_quat(Z, Radians(degrees)));
}

Vector3f GetNormal(const Vector3f &a, const Vector3f &b, const Vector3f &c) {
  return linalg::normalize(linalg::cross(b - a, c - a));
}

Matrix4f GetOrthographic(float L, float R, float B, float T, float N, float F) {
  float PM00 = 2.0f / (R - L);
  float PM11 = 2.0f / (T - B);
  float PM22 = 2.0f / (N - F);
  float PM30 = (R + L) / (L - R);
  float PM31 = (T + B) / (B - T);
  float PM32 = (F + N) / (N - F);
  return Matrix4f{{PM00, 0.0f, +0.0f, 0.0f},
                  {0.0f, PM11, +0.0f, 0.0f},
                  {0.0f, 0.0f, -1.0f, 0.0f},
                  {PM30, PM31, PM32, 1.0f}};
}

int32_t GetLog(int32_t value) {
  int32_t ret{0};
  while (value > 1) {
    value >>= 1;
    ret++;
  }
  return ret;
}

} // namespace Gloom