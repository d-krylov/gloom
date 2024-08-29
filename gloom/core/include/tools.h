#ifndef GLOOM_TOOLS_H
#define GLOOM_TOOLS_H

#include <filesystem>
#include <string>

namespace Gloom {

[[nodiscard]] double GetTime();
[[nodiscard]] std::string ReadFile(const std::filesystem::path &path);

inline const std::filesystem::path ROOT = PROJECT_SOURCE_DIR;
inline const std::filesystem::path SHADERS_DIR = ROOT / "shaders";

} // namespace Gloom

#endif // GLOOM_TOOLS_H