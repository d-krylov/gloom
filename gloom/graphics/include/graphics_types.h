#ifndef GLOOM_TYPES_H
#define GLOOM_TYPES_H

#include "glad/glad.h"
#include "gloom/core/include/concepts.h"
#include "gloom/core/include/core_assert.h"
#include "gloom/core/include/core_types.h"
#include "gloom/core/include/macros.h"
#include <array>

namespace Gloom {

enum class Access { READ = GL_READ_ONLY, WRITE = GL_WRITE_ONLY, READ_WRITE = GL_READ_WRITE };
enum class PolygonMode { POINT = GL_POINT, LINE = GL_LINE, FILL = GL_FILL };

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
  BYTE = GL_BYTE,
  UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
  SHORT = GL_SHORT,
  UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
  INT = GL_INT,
  UNSIGNED_INT = GL_UNSIGNED_INT,
  FLOAT = GL_FLOAT
};

enum class IndexType {
  BYTE = GL_UNSIGNED_BYTE,
  UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
  UNSIGNED_INT = GL_UNSIGNED_INT
};

enum class ClipOrigin { LOWER_LEFT = GL_LOWER_LEFT, UPPER_LEFT = GL_UPPER_LEFT };

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