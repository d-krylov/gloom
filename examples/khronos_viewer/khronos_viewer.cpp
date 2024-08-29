#include "gloom/application/include/gloom.h"
#include <array>
#include <iostream>

using namespace Gloom;

int main() {

  Model model;

  model.LoadAssimp(ROOT / "assets" / "sponza1" / "sponza.obj");

  return 0;
}