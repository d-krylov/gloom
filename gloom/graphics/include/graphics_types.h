#ifndef GLOOM_TYPES_H
#define GLOOM_TYPES_H

#include "core/include/concepts.h"
#include "core/include/core_types.h"
#include "core/include/macros.h"
#include "core/include/tools.h"
#include "glad/glad.h"
#include <array>

namespace Gloom {

enum class PolygonMode {
#define POLYGON_MODE(X) X = GL_##X,
#include "graphics_types.def"
};

enum class PixelFormat {
#define PIXEL_FORMAT(X) X = GL_##X,
#include "graphics_types.def"
};

enum class MinFilter {
#define MIN_FILTER(X) X = GL_##X,
#include "graphics_types.def"
};

enum class MagFilter {
#define MAG_FILTER(X) X = GL_##X,
#include "graphics_types.def"
};

enum class WrapMode {
#define WRAP_MODE(X) X = GL_##X,
#include "graphics_types.def"
};

inline constexpr uint32_t SHADER_STAGES_COUNT = 5;

enum class BlendOperation {
#define BLEND_OPERATION(X) X = GL_##X,
#include "graphics_types.def"
};

enum class BlendFactor {
#define BLEND_FACTOR(X) X = GL_##X,
#include "graphics_types.def"
};

enum class ShaderBit {
#define SHADER_BIT(X) X = GL_##X##_SHADER_BIT,
#include "graphics_types.def"
};

enum class BufferStorage {
#define BUFFER_STORAGE(X) X = GL_##X##_BIT,
#include "graphics_types.def"
};

enum class MapAccess {
#define MAP_ACCESS(X) X = GL_MAP_##X##_BIT,
#include "graphics_types.def"
};

enum class Access {
#define ACCESS(X) X = GL_##X,
#include "graphics_types.def"
};

enum class ShaderKind {
#define SHADER_KIND(X, N) X = GL_##X##_SHADER,
#include "graphics_types.def"
};

enum class DataType {
#define GLSL_DATA_TYPE(X, Y, Z, V, W) X,
#include "graphics_types.def"
};

enum class PrimitiveKind {
#define PRIMITIVE_KIND(X) X = GL_##X,
#include "graphics_types.def"
};

enum class BufferTarget {
#define BUFFER_TARGET(X) X = GL_##X##_BUFFER,
#include "graphics_types.def"
};

enum class TextureTarget {
#define TEXTURE_TARGET(X, D, L) X = GL_##X,
#include "graphics_types.def"
};

enum class InternalFormat {
#define TEXTURE_FORMAT(X, Y, Z) X = GL_##X,
#include "graphics_types.def"
};

enum class AttachmentType {
#define ATTACHMENT_TYPE(X) X = GL_##X,
#include "graphics_types.def"
};

enum class BarrierBit {
#define BARRIER_BIT(X) X = GL_##X##_BARRIER_BIT,
#include "graphics_types.def"
};

enum class ComparasionFunction {
#define COMPARASION_FUNCTION(X) X = GL_##X,
#include "graphics_types.def"
};

enum class StencilOperation {
#define STENCIL_OPERATION(X) X = GL_##X,
#include "graphics_types.def"
};

enum class PrimitiveDataType {
#define PRIMITIVE_DATA_TYPE(X) X = GL_##X,
#include "graphics_types.def"
};

enum class PixelType {
#define PIXEL_TYPE(X) X = GL_##X,
#include "graphics_types.def"
};

enum class IndexType {
#define INDEX_TYPE(X) X = GL_##X,
#include "graphics_types.def"
};

struct DrawArraysIndirectCommand {
  uint32_t count_{0};
  uint32_t instance_count_{0};
  uint32_t first_vertex_{0};
  uint32_t base_instance_{0};
};

struct DrawElementsIndirectCommand {
  uint32_t count_{0};
  uint32_t instance_count_{0};
  uint32_t first_index_{0};
  int32_t base_vertex_{0};
  uint32_t base_instance_{0};
};

ALLOW_BITMASK_ENUM(BufferStorage);
ALLOW_BITMASK_ENUM(MapAccess);

[[nodiscard]] uint32_t GetShaderIndex(ShaderKind kind);
[[nodiscard]] std::optional<ShaderKind> GetShaderKind(const std::filesystem::path &path);
[[nodiscard]] ShaderBit GetShaderBit(ShaderKind kind);
[[nodiscard]] uint32_t GetTextureDimensions(TextureTarget target);
[[nodiscard]] bool IsTextureLayered(TextureTarget target);
[[nodiscard]] std::pair<PixelFormat, PixelType> GetPixelFormatAndType(InternalFormat format);
[[nodiscard]] InternalFormat GetInternalFormat(uint32_t channels);
[[nodiscard]] std::size_t GetDataTypeComponentSize(DataType type);
[[nodiscard]] std::size_t GetDataTypeComponentCount(DataType type);
[[nodiscard]] PrimitiveDataType GetDataTypeComponentType(DataType type);
[[nodiscard]] std::size_t GetDataTypeSize(DataType type);

} // namespace Gloom

#endif // GLOOM_TYPES_H