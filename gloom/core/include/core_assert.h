#ifndef GLOOM_CORE_ASSERT_H
#define GLOOM_CORE_ASSERT_H

#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <signal.h>

namespace Gloom {

#define DEBUG_BREAK() raise(SIGTRAP)

#define GLOOM_ASSERT_FATAL(format, ...)                                                            \
  do {                                                                                             \
    printf("%s:%u " format "\n", std::filesystem::path(__FILE__).filename().string().c_str(),      \
           __LINE__, ##__VA_ARGS__);                                                               \
    DEBUG_BREAK();                                                                                 \
    abort();                                                                                       \
  } while (1)

#define CORE_VERIFY(expression)                                                                    \
  do {                                                                                             \
    if (!(expression)) {                                                                           \
      GLOOM_ASSERT_FATAL("assert %s failed in %s", #expression, __func__);                         \
    }                                                                                              \
  } while (0)

} // namespace Gloom

#endif // GLOOM_CORE_ASSERT_H