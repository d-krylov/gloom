#ifndef GLOOM_TOOLS_H
#define GLOOM_TOOLS_H

#include <filesystem>
#include <signal.h>
#include <source_location>
#include <string>

namespace Gloom {

[[nodiscard]] double GetTime();
[[nodiscard]] std::string ReadFile(const std::filesystem::path &path);

inline const std::filesystem::path ROOT = GLOOM_PROJECT_SOURCE_DIR;
inline const std::filesystem::path SHADERS_DIR = ROOT / "shaders";

inline void DebugBreak() { raise(SIGTRAP); }

inline void ASSERT_FATAL(std::string_view format,
                         const std::source_location location = std::source_location::current()) {
  std::string f = std::string("%s : %u ") + format.data() + "\n";
  std::printf(f.c_str(), location.file_name(), location.line());
  DebugBreak();
  std::abort();
}

inline void CORE_VERIFY(bool expression,
                        const std::source_location location = std::source_location::current()) {
  if (!expression) {
    ASSERT_FATAL("assert %s failed in %s", location);
  }
}

} // namespace Gloom

#endif // GLOOM_TOOLS_H