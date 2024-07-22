#include "gloom/include/application.h"
#include "gloom_mesh/include/mesh_loader.h"
#include <array>
#include <iostream>

using Gloom::operator""_KiB;
using Gloom::operator""_MiB;

int main() {

  Gloom::LoadGLTF(Gloom::GetRoot() / "assets" / "khronos" / "Box.gltf");

  return 0;
}