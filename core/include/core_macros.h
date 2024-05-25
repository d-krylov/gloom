#ifndef CORE_MACROS_H
#define CORE_MACROS_H

namespace Gloom {

#define NO_MOVE_CONSTRUCTOR(TypeName) TypeName(TypeName &&) = delete;
#define NO_MOVE_OPERATOR(TypeName) TypeName &operator=(TypeName &&) = delete;

#define NO_MOVE_SEMANTIC(TypeName)                                                            \
  NO_MOVE_CONSTRUCTOR(TypeName)                                                               \
  NO_MOVE_OPERATOR(TypeName)

#define NO_COPY_CONSTRUCTOR(TypeName) TypeName(const TypeName &) = delete;
#define NO_COPY_OPERATOR(TypeName) void operator=(const TypeName &) = delete;

#define NO_COPY_SEMANTIC(TypeName)                                                            \
  NO_COPY_CONSTRUCTOR(TypeName)                                                               \
  NO_COPY_OPERATOR(TypeName)

} // namespace Gloom

#endif // CORE_MACROS_H