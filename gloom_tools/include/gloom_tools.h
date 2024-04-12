#ifndef GLOOM_TOOLS_H
#define GLOOM_TOOLS_H

#include <filesystem>
#include <string>

namespace Gloom ::Tools {

[[nodiscard]] std::filesystem::path GetRoot();
[[nodiscard]] std::string ReadFile(const std::filesystem::path &path);

} // namespace Gloom::Tools

#endif // FILE_TOOLS_H