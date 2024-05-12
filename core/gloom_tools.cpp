#include "gloom_tools.h"
#include <fstream>

namespace Gloom ::Tools {

std::string ReadFile(const std::filesystem::path &path) {
  std::ifstream file(path.c_str());
  std::string ret{std::istreambuf_iterator<char>(file),
                  std::istreambuf_iterator<char>()};
  return ret;
}

std::filesystem::path GetRoot() {
  return std::filesystem::path(PROJECT_SOURCE_DIR);
}

} // namespace Gloom::Tools