#include "gloom/graphics/include/graphics_types.h"

namespace Gloom {

std::size_t GetDataTypeComponentCount(DataType type) {
  switch (type) {
#define GLSL_DATA_TYPE(X, Y, Z, W, V)                                                              \
  case DataType::X:                                                                                \
    return Y;
#include "gloom/graphics/include/graphics_types.def"
  default:
    UNREACHABLE();
    break;
  }
}

std::size_t GetDataTypeComponentSize(DataType type) {
  switch (type) {
#define GLSL_DATA_TYPE(X, Y, Z, W, V)                                                              \
  case DataType::X:                                                                                \
    return Z;
#include "gloom/graphics/include/graphics_types.def"
  default:
    UNREACHABLE();
    break;
  }
}

PrimitiveDataType GetDataTypeComponentType(DataType type) {
  switch (type) {
#define GLSL_DATA_TYPE(X, Y, Z, W, V)                                                              \
  case DataType::X:                                                                                \
    return PrimitiveDataType::W;
#include "gloom/graphics/include/graphics_types.def"
  default:
    UNREACHABLE();
    break;
  }
}

std::size_t GetDataTypeSize(DataType type) {
  auto component_count = GetDataTypeComponentCount(type);
  auto component_size = GetDataTypeComponentSize(type);
  return component_count * component_size;
}

uint32_t GetShaderIndex(ShaderKind kind) {
  switch (kind) {
#define SHADER_KIND(X, Y)                                                                          \
  case ShaderKind::X:                                                                              \
    return Y;
#include "gloom/graphics/include/graphics_types.def"
  default:
    UNREACHABLE();
    break;
  }
}

bool IsTextureLayered(TextureTarget target) {
  switch (target) {
#define TEXTURE_TARGET(X, D, L)                                                                    \
  case TextureTarget::X:                                                                           \
    return L;
#include "gloom/graphics/include/graphics_types.def"
  default:
    UNREACHABLE();
    break;
  }
}

uint32_t GetTextureDimensions(TextureTarget target) {
  switch (target) {
#define TEXTURE_TARGET(X, D, L)                                                                    \
  case TextureTarget::X:                                                                           \
    return D;
#include "gloom/graphics/include/graphics_types.def"
  default:
    UNREACHABLE();
    break;
  }
}

std::pair<PixelFormat, PixelType> GetPixelFormatAndType(InternalFormat format) {
  switch (format) {
#define TEXTURE_FORMAT(X, Y, Z)                                                                    \
  case InternalFormat::X:                                                                          \
    return std::make_pair(PixelFormat::Y, PixelType::Z);
#include "gloom/graphics/include/graphics_types.def"
  default:
    UNREACHABLE();
    break;
  }
}

InternalFormat GetInternalFormat(uint32_t channels) {
  switch (channels) {
  case 3:
    return InternalFormat::RGB8;
    break;
  case 4:
    return InternalFormat::RGBA8;
  default:
    UNREACHABLE();
    break;
  }
}

// clang-format off
std::optional<ShaderKind> GetShaderKind(const std::filesystem::path &path) {
  auto extension = path.extension().string();
  if (extension == ".vert") { return ShaderKind::VERTEX; }
  if (extension == ".geom") { return ShaderKind::GEOMETRY; }
  if (extension == ".tesc") { return ShaderKind::TESS_CONTROL; }
  if (extension == ".tese") { return ShaderKind::TESS_EVALUATION; }
  if (extension == ".frag") { return ShaderKind::FRAGMENT; }
  return {};
}
// clang-format on

ShaderBit GetShaderBit(ShaderKind kind) {
  switch (kind) {
  case ShaderKind::VERTEX:
    return ShaderBit::VERTEX;
  case ShaderKind::TESS_CONTROL:
    return ShaderBit::TESS_CONTROL;
  case ShaderKind::TESS_EVALUATION:
    return ShaderBit::TESS_EVALUATION;
  case ShaderKind::GEOMETRY:
    return ShaderBit::GEOMETRY;
  case ShaderKind::FRAGMENT:
    return ShaderBit::FRAGMENT;
  default:
    UNREACHABLE();
    break;
  }
}

} // namespace Gloom