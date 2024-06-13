#include "gloom_core/include/cubemap.h"
#include "stb/stb_image.h"
#include "tools.h"

namespace Gloom {

CubeMap::CubeMap(const std::initializer_list<std::filesystem::path> &pathes) {
  uint32_t i{0};
  for (const auto &path : pathes) {
    auto data = ToBytePointer(stbi_load(path.c_str(), &size_.x, &size_.y, &channels_, 0));
    data_[i++] = data;
  }
}

CubeMap::~CubeMap() {
  for (auto &image : data_) {
    stbi_image_free(image);
  }
}

std::span<const std::byte> CubeMap::GetData(uint32_t i) const {
  return std::span(data_[i], size_.x * size_.y * channels_);
}

} // namespace Gloom