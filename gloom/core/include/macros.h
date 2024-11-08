#ifndef GLOOM_MACROS_H
#define GLOOM_MACROS_H

#include <utility>

namespace Gloom {

#define NO_MOVE_CONSTRUCTOR(TypeName) TypeName(TypeName &&) = delete;
#define NO_MOVE_OPERATOR(TypeName) TypeName &operator=(TypeName &&) = delete;

#define NO_MOVE_SEMANTIC(TypeName)                                                                 \
  NO_MOVE_CONSTRUCTOR(TypeName)                                                                    \
  NO_MOVE_OPERATOR(TypeName)

#define NO_COPY_CONSTRUCTOR(TypeName) TypeName(const TypeName &) = delete;
#define NO_COPY_OPERATOR(TypeName) void operator=(const TypeName &) = delete;

#define NO_COPY_SEMANTIC(TypeName)                                                                 \
  NO_COPY_CONSTRUCTOR(TypeName)                                                                    \
  NO_COPY_OPERATOR(TypeName)

#define UNREACHABLE() __builtin_unreachable()

#define BIND_FUNCTION(function)                                                                    \
  [this](auto &&...args) -> decltype(auto) {                                                       \
    return this->function(std::forward<decltype(args)>(args)...);                                  \
  }

} // namespace Gloom

#endif // GLOOM_MACROS_H