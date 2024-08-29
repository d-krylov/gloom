#ifndef GLOOM_TYPES_H
#define GLOOM_TYPES_H

#include "glad/glad.h"
#include "gloom/core/include/core_assert.h"
#include "gloom/core/include/core_types.h"
#include "gloom/core/include/macros.h"
#include <array>

namespace Gloom {

enum class Access { READ = GL_READ_ONLY, WRITE = GL_WRITE_ONLY, READ_WRITE = GL_READ_WRITE };
enum class PolygonMode { POINT = GL_POINT, LINE = GL_LINE, FILL = GL_FILL };

enum class BufferStorage {
  MAP_READ = GL_MAP_READ_BIT,
  MAP_WRITE = GL_MAP_WRITE_BIT,
  MAP_PERSISTENT = GL_MAP_PERSISTENT_BIT,
  MAP_COHERENT = GL_MAP_COHERENT_BIT,
  DYNAMIC_STORAGE = GL_DYNAMIC_STORAGE_BIT,
  CLIENT_STORAGE = GL_CLIENT_STORAGE_BIT,
  MAP_READ_WRITE = MAP_READ | MAP_WRITE,
  MAP_READ_WRITE_PERSISTENT = MAP_READ_WRITE | MAP_PERSISTENT | MAP_COHERENT
};

enum class ShaderBit {
  VERTEX = GL_VERTEX_SHADER_BIT,
  TESS_CONTROL = GL_TESS_CONTROL_SHADER_BIT,
  TESS_EVALUATION = GL_TESS_EVALUATION_SHADER_BIT,
  GEOMETRY = GL_GEOMETRY_SHADER_BIT,
  FRAGMENT = GL_FRAGMENT_SHADER_BIT,
};

enum class PixelFormat {
  RED = GL_RED,
  RG = GL_RG,
  RGB = GL_RGB,
  RGBA = GL_RGBA,
  BGR = GL_BGR,
  BGRA = GL_BGRA,
  DEPTH_COMPONENT = GL_DEPTH_COMPONENT,
  DEPTH_STENCIL = GL_DEPTH_STENCIL,
  STENCIL_INDEX = GL_STENCIL_INDEX
};

enum class MinFilter {
  NEAREST = GL_NEAREST,
  LINEAR = GL_LINEAR,
  NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
  LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
  NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
  LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR
};

enum class MagFilter { NEAREST = GL_NEAREST, LINEAR = GL_LINEAR };

enum class WrapMode {
  CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
  CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER,
  MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
  REPEAT = GL_REPEAT,
  MIRROR_CLAMP_TO_EDGE = GL_MIRROR_CLAMP_TO_EDGE
};

enum class BlendOperation {
  ADD = GL_FUNC_ADD,
  SUBTRACT = GL_FUNC_SUBTRACT,
  REVERSE_SUBTRACT = GL_FUNC_REVERSE_SUBTRACT,
  MIN = GL_MIN,
  MAX = GL_MAX
};

enum class BlendFactor {
  ZERO = GL_ZERO,
  ONE = GL_ONE,
  SRC_COLOR = GL_SRC_COLOR,
  ONE_MINUS_SRC_COLOR = GL_ONE_MINUS_SRC_COLOR,
  DST_COLOR = GL_DST_COLOR,
  ONE_MINUS_DST_COLOR = GL_ONE_MINUS_DST_COLOR,
  SRC_ALPHA = GL_SRC_ALPHA,
  ONE_MINUS_SRC_ALPHA = GL_ONE_MINUS_SRC_ALPHA,
  DST_ALPHA = GL_DST_ALPHA,
  ONE_MINUS_DST_ALPHA = GL_ONE_MINUS_DST_ALPHA,
  CONSTANT_COLOR = GL_CONSTANT_COLOR,
  ONE_MINUS_CONSTANT_COLOR = GL_ONE_MINUS_CONSTANT_COLOR,
  CONSTANT_ALPHA = GL_CONSTANT_ALPHA,
  ONE_MINUS_CONSTANT_ALPHA = GL_ONE_MINUS_CONSTANT_ALPHA,
  SRC_ALPHA_SATURATE = GL_SRC_ALPHA_SATURATE,
  SRC1_COLOR = GL_SRC1_COLOR,
  ONE_MINUS_SRC1_COLOR = GL_ONE_MINUS_SRC1_COLOR,
  SRC1_ALPHA = GL_SRC1_ALPHA,
  ONE_MINUS_SRC1_ALPHA = GL_ONE_MINUS_SRC1_ALPHA
};

inline constexpr uint32_t SHADER_STAGES_COUNT = 5;

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

enum class PrimitiveDataType {
  BYTE = GL_BYTE,
  UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
  SHORT = GL_SHORT,
  UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
  INT = GL_INT,
  UNSIGNED_INT = GL_UNSIGNED_INT,
  FLOAT = GL_FLOAT,
  DOUBLE = GL_DOUBLE
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

enum class StencilFunction {
  NEVER = GL_NEVER,
  LESS = GL_LESS,
  EQUAL = GL_EQUAL,
  LEQUAL = GL_LEQUAL,
  GREATER = GL_GREATER,
  NOTEQUAL = GL_NOTEQUAL,
  GEQUAL = GL_GEQUAL,
  ALWAYS = GL_ALWAYS
};

enum class StencilOption {
  KEEP = GL_KEEP,
  ZERO = GL_ZERO,
  REPLACE = GL_REPLACE,
  INCREMENT = GL_INCR,
  INCREMENT_WRAP = GL_INCR_WRAP,
  DECREMENT = GL_DECR,
  DECREMENT_WRAP = GL_DECR_WRAP,
  INVERT = GL_INVERT
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