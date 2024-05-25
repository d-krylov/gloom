#ifndef TOOLS_H
#define TOOLS_H

#include <filesystem>
#include <string>

namespace Gloom {

[[nodiscard]] double GetTime();
[[nodiscard]] std::filesystem::path GetRoot();
[[nodiscard]] std::string ReadFile(const std::filesystem::path &path);

} // namespace Gloom

#endif // TOOLS_H