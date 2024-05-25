#ifndef GLOOM_TYPES_H
#define GLOOM_TYPES_H

#include "core_assert.h"
#include "core_macros.h"
#include "core_types.h"
#include "glad/glad.h"
#include <array>

namespace Gloom ::Types {

enum class DataType {
#define GLSL_DATA_TYPE(X, Y, Z, V, W) X,
#include "graphics_types.def"
};

enum class ShaderKind {
  VERTEX = GL_VERTEX_SHADER,
  TESSELATION_CONTROL = GL_TESS_CONTROL_SHADER,
  TESSELATION_EVALUATION = GL_TESS_EVALUATION_SHADER,
  GEOMETRY = GL_GEOMETRY_SHADER,
  FRAGMENT = GL_FRAGMENT_SHADER,
  COMPUTE = GL_COMPUTE_SHADER,
};

enum class ShaderBit {
  VERTEX = GL_VERTEX_SHADER_BIT,
  TESSELATION_CONTROL = GL_TESS_CONTROL_SHADER_BIT,
  TESSELATION_EVALUATION = GL_TESS_EVALUATION_SHADER_BIT,
  GEOMETRY = GL_GEOMETRY_SHADER_BIT,
  FRAGMENT = GL_FRAGMENT_SHADER_BIT,
  COMPUTE = GL_COMPUTE_SHADER_BIT,
};

enum ShaderIndex : std::size_t {
  VERTEX = 0,
  TESSELATION_CONTROL = 1,
  TESSELATION_EVALUATION = 2,
  GEOMETRY = 3,
  FRAGMENT = 4,
  COMPUTE = 5,
};

constexpr std::size_t SHADER_STAGES_COUNT = ShaderIndex::COMPUTE + 1;

enum class AttributeUsage {
  NONE = 0,
  POSITION = (1 << 0U),
  COLOR = (1 << 1U),
  NORMAL = (1 << 2U),
  TANGENT = (1 << 3U),
  BITANGENT = (1 << 4U),
  TEXTURE_UV = (1 << 5U),
  IDENTIFIER = (1 << 6U)
};

enum class BufferStorage {
  MAP_READ = GL_MAP_READ_BIT,
  MAP_WRITE = GL_MAP_WRITE_BIT,
  MAP_PERSISTENT = GL_MAP_PERSISTENT_BIT,
  MAP_COHERENT = GL_MAP_COHERENT_BIT,
  DYNAMIC_STORAGE = GL_DYNAMIC_STORAGE_BIT,
  CLIENT_STORAGE = GL_CLIENT_STORAGE_BIT,
  RW_STORAGE = MAP_READ | MAP_WRITE,
  RWPC_STORAGE = RW_STORAGE | MAP_PERSISTENT | MAP_COHERENT
};

enum class BufferTarget {
  ARRAY_BUFFER = GL_ARRAY_BUFFER,
  ATOMIC_COUNTER_BUFFER = GL_ATOMIC_COUNTER_BUFFER,
  COPY_READ_BUFFER = GL_COPY_READ_BUFFER,
  COPY_WRITE_BUFFER = GL_COPY_WRITE_BUFFER,
  DISPATCH_INDIRECT_BUFFER = GL_DISPATCH_INDIRECT_BUFFER,
  DRAW_INDIRECT_BUFFER = GL_DRAW_INDIRECT_BUFFER,
  ELEMENT_ARRAY_BUFFER = GL_ELEMENT_ARRAY_BUFFER,
  PIXEL_PACK_BUFFER = GL_PIXEL_PACK_BUFFER,
  PIXEL_UNPACK_BUFFER = GL_PIXEL_UNPACK_BUFFER,
  QUERY_BUFFER = GL_QUERY_BUFFER,
  SHADER_STORAGE_BUFFER = GL_SHADER_STORAGE_BUFFER,
  TEXTURE_BUFFER = GL_TEXTURE_BUFFER,
  TRANSFORM_FEEDBACK_BUFFER = GL_TRANSFORM_FEEDBACK_BUFFER,
  UNIFORM_BUFFER = GL_UNIFORM_BUFFER
};

enum class PrimitiveKind {
  POINTS = GL_POINTS,
  LINE_STRIP = GL_LINE_STRIP,
  LINE_LOOP = GL_LINE_LOOP,
  LINES = GL_LINES,
  LINE_STRIP_ADJACENCY = GL_LINE_STRIP_ADJACENCY,
  LINES_ADJACENCY = GL_LINES_ADJACENCY,
  TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
  TRIANGLE_FAN = GL_TRIANGLE_FAN,
  TRIANGLES = GL_TRIANGLES,
  TRIANGLE_STRIP_ADJACENCY = GL_TRIANGLE_STRIP_ADJACENCY,
  TRIANGLES_ADJACENCY = GL_TRIANGLES_ADJACENCY,
  PATCHES = GL_PATCHES,
};

enum class FramebufferAttachmentType {
  COLOR = GL_COLOR_ATTACHMENT0,
  DEPTH = GL_DEPTH_ATTACHMENT,
  STENCIL = GL_STENCIL_ATTACHMENT,
  DEPTH_STENCIL = GL_DEPTH_STENCIL_ATTACHMENT
};

enum class TextureTarget {
#define TEXTURE_TARGET(X, D, L) X = GL_##X,
#include "graphics_types.def"
};

enum class TextureInternalFormat {
#define TEXTURE_INTERNAL_FORMAT(X, Y, Z) X = GL_##X,
#include "graphics_types.def"
};

enum class PixelFormat { RED = GL_RED, RG = GL_RG, RGB = GL_RGB, RGBA = GL_RGBA };

enum class TextureMinifyingFunction {
  NEAREST = GL_NEAREST,
  LINEAR = GL_LINEAR,
  NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
  LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
  NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
  LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR
};

enum class TextureMagnificationFunction { NEAREST = GL_NEAREST, LINEAR = GL_LINEAR };

enum class TextureComparisonFunction {
  NEVER = GL_NEVER,
  LESS = GL_LESS,
  EQUAL = GL_EQUAL,
  LEQUAL = GL_LEQUAL,
  GREATER = GL_GREATER,
  NOTEQUAL = GL_NOTEQUAL,
  GEQUAL = GL_GEQUAL,
  ALWAYS = GL_ALWAYS
};

enum class TextureWrapMode {
  CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
  CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER,
  MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
  REPEAT = GL_REPEAT,
  MIRROR_CLAMP_TO_EDGE = GL_MIRROR_CLAMP_TO_EDGE
};

enum class FramebufferKind {
  READ = GL_READ_FRAMEBUFFER,
  DRAW = GL_DRAW_FRAMEBUFFER,
  FULL = GL_FRAMEBUFFER
};

enum class BlendEquation {
  ADD = GL_FUNC_ADD,
  SUBTRACT = GL_FUNC_SUBTRACT,
  REVERSE_SUBTRACT = GL_FUNC_REVERSE_SUBTRACT,
  MIN = GL_MIN,
  MAX = GL_MAX
};

enum class BlendFunctionSeparate {
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

enum class PolygonMode { POINT = GL_POINT, LINE = GL_LINE, FILL = GL_FILL };

using Handle = uint32_t;

constexpr int64_t WHOLE_SIZE = 0;

enum class CoreType {
  BYTE = GL_BYTE,
  UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
  SHORT = GL_SHORT,
  UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
  INTEGER = GL_INT,
  UNSIGNED_INTEGER = GL_UNSIGNED_INT,
  FLOAT = GL_FLOAT,
  DOUBLE = GL_DOUBLE
};

constexpr uint16_t Index = static_cast<uint16_t>(CoreType::UNSIGNED_INTEGER);

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

struct SamplerCreateInformation {
  TextureMagnificationFunction magnification_filter_{TextureMagnificationFunction::LINEAR};
  TextureMinifyingFunction minifying_filter_{TextureMinifyingFunction::LINEAR};
  TextureComparisonFunction compare_function_{TextureComparisonFunction::NEVER};
  std::array<TextureWrapMode, 3> wrap_mode_ = {TextureWrapMode::REPEAT};
};

constexpr auto ARRAYS_COMMAND_SIZE = sizeof(DrawArraysIndirectCommand);
constexpr auto ELEMENTS_COMMAND_SIZE = sizeof(DrawElementsIndirectCommand);

[[nodiscard]] CoreType GetComponentType(DataType type);
[[nodiscard]] std::size_t GetComponentCount(DataType type);
[[nodiscard]] std::size_t GetComponentSize(DataType type);
[[nodiscard]] std::size_t GetSize(DataType type);
[[nodiscard]] ShaderKind GetShaderKind(ShaderIndex index);
[[nodiscard]] ShaderBit GetShaderBit(ShaderIndex index);
[[nodiscard]] std::size_t GetTextureDimensions(TextureTarget target);
[[nodiscard]] CoreType GetPixelDataType(TextureInternalFormat format);
[[nodiscard]] bool IsTextureLayered(TextureTarget target);
[[nodiscard]] PixelFormat GetPixelDataFormat(TextureInternalFormat format);
[[nodiscard]] std::pair<PixelFormat, CoreType>
GetPixelFormatAndType(TextureInternalFormat format);

} // namespace Gloom::Types

#endif // GLOOM_TYPES_H