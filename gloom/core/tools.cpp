#include "core/include/tools.h"
#include <chrono>
#include <fstream>

namespace Gloom {

auto start_time = std::chrono::high_resolution_clock::now();

double GetTime() {
  auto current_time = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = current_time - start_time;
  return elapsed.count();
}

std::string ReadFile(const std::filesystem::path &path) {
  std::ifstream file(path.c_str());
  std::string ret{std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};
  return ret;
}

} // namespace Gloom