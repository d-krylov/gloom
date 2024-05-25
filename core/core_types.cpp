#include "core_types.h"

namespace Gloom ::Types {

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

} // namespace Gloom::Types