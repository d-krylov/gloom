#include "graphics_types.h"

namespace Gloom {

ShaderKind GetShaderKind(ShaderIndex index) {
  switch (index) {
  case ShaderIndex::VERTEX:
    return ShaderKind::VERTEX;
  case ShaderIndex::TESSELATION_CONTROL:
    return ShaderKind::TESSELATION_CONTROL;
  case ShaderIndex::TESSELATION_EVALUATION:
    return ShaderKind::TESSELATION_EVALUATION;
  case ShaderIndex::GEOMETRY:
    return ShaderKind::GEOMETRY;
  case ShaderIndex::FRAGMENT:
    return ShaderKind::FRAGMENT;
  case ShaderIndex::COMPUTE:
    return ShaderKind::COMPUTE;
  default:
    break;
  }
  CORE_UNREACHABLE();
}

ShaderBit GetShaderBit(ShaderIndex index) {
  switch (index) {
  case ShaderIndex::VERTEX:
    return ShaderBit::VERTEX;
  case ShaderIndex::TESSELATION_CONTROL:
    return ShaderBit::TESSELATION_CONTROL;
  case ShaderIndex::TESSELATION_EVALUATION:
    return ShaderBit::TESSELATION_EVALUATION;
  case ShaderIndex::GEOMETRY:
    return ShaderBit::GEOMETRY;
  case ShaderIndex::FRAGMENT:
    return ShaderBit::FRAGMENT;
  case ShaderIndex::COMPUTE:
    return ShaderBit::COMPUTE;
  default:
    break;
  }
  CORE_UNREACHABLE();
}

std::size_t GetTextureDimensions(TextureTarget target) {
  switch (target) {
#define TEXTURE_TARGET(X, D, L)                                                               \
  case TextureTarget::X:                                                                      \
    return D;
#include "graphics_types.def"
  default:
    break;
  }
  CORE_UNREACHABLE();
}

bool IsTextureLayered(TextureTarget target) {
  switch (target) {
#define TEXTURE_TARGET(X, D, L)                                                               \
  case TextureTarget::X:                                                                      \
    return L;
#include "graphics_types.def"
  default:
    break;
  }
  CORE_UNREACHABLE();
}

CoreType GetPixelDataType(TextureInternalFormat format) {
  switch (format) {
#define TEXTURE_INTERNAL_FORMAT(X, Y, Z)                                                      \
  case TextureInternalFormat::X:                                                              \
    return CoreType::Z;
#include "graphics_types.def"
  default:
    break;
  }
  CORE_UNREACHABLE();
}

PixelFormat GetPixelDataFormat(TextureInternalFormat format) {
  switch (format) {
#define TEXTURE_INTERNAL_FORMAT(X, Y, Z)                                                      \
  case TextureInternalFormat::X:                                                              \
    return PixelFormat::Y;
#include "graphics_types.def"
  default:
    break;
  }
  CORE_UNREACHABLE();
}

std::pair<PixelFormat, CoreType> GetPixelFormatAndType(TextureInternalFormat format) {
  switch (format) {
#define TEXTURE_INTERNAL_FORMAT(X, Y, Z)                                                      \
  case TextureInternalFormat::X:                                                              \
    return std::make_pair(PixelFormat::Y, CoreType::Z);
#include "graphics_types.def"
  default:
    break;
  }
  CORE_UNREACHABLE();
}

std::size_t GetComponentCount(DataType type) {
  switch (type) {
#define GLSL_DATA_TYPE(X, Y, Z, W, V)                                                         \
  case DataType::X:                                                                           \
    return Y;
#include "graphics_types.def"
  default:
    break;
  }
  CORE_UNREACHABLE();
}

std::size_t GetComponentSize(DataType type) {
  switch (type) {
#define GLSL_DATA_TYPE(X, Y, Z, W, V)                                                         \
  case DataType::X:                                                                           \
    return Z;
#include "graphics_types.def"
  default:
    break;
  }
  CORE_UNREACHABLE();
}

CoreType GetComponentType(DataType type) {
  switch (type) {
#define GLSL_DATA_TYPE(X, Y, Z, W, V)                                                         \
  case DataType::X:                                                                           \
    return CoreType::W;
#include "graphics_types.def"
  default:
    break;
  }
  CORE_UNREACHABLE();
}

std::size_t GetSize(DataType type) {
  auto component_count = GetComponentCount(type);
  auto component_size = GetComponentSize(type);
  return component_count * component_size;
}

int32_t GetLevelCount(int32_t width, int32_t height, int32_t depth) {
  auto max_dimension = std::max(depth, std::max(width, height));
  return GetLog(max_dimension) + (max_dimension > 0);
}

// clang-format off
std::optional<ShaderIndex> GetShaderIndex(const std::filesystem::path &path) {
  auto extension = path.extension().string();
  if (extension == ".vert") { return ShaderIndex::VERTEX; }
  if (extension == ".geom") { return ShaderIndex::GEOMETRY; }
  if (extension == ".tesc") { return ShaderIndex::TESSELATION_CONTROL; }
  if (extension == ".tese") { return ShaderIndex::TESSELATION_EVALUATION; }
  if (extension == ".frag") { return ShaderIndex::FRAGMENT; }
  if (extension == ".comp") { return ShaderIndex::COMPUTE; }
  return {};
}
// clang-format on

} // namespace Gloom