#ifndef GLOOM_KEY_H
#define GLOOM_KEY_H

#include <GLFW/glfw3.h>

namespace Gloom {

enum class Key {
#define KEY(X, Y) K_##X = GLFW_KEY_##X,
#include "key.def"
};

enum class Action {
#define ACTION(X) X = GLFW_##X,
#include "key.def"
};

enum class MouseButton {
#define MOUSE_BUTTON(X) X = GLFW_MOUSE_##X,
#include "key.def"
};

} // namespace Gloom

#endif // GLOOM_KEY_H