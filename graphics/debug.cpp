#include "debug.h"
#include <cstdio>

namespace Gloom {

bool GetShaderLinkStatus(Types::Handle shader_handle) {
  int32_t compiled = 0;
  glGetProgramiv(shader_handle, GL_LINK_STATUS, &compiled);
  return compiled == GL_TRUE;
}

std::string GetShaderLog(Types::Handle shader_handle) {
  int message_size = 0;
  glGetProgramiv(shader_handle, GL_INFO_LOG_LENGTH, &message_size);
  std::string message(message_size, ' ');
  glGetProgramInfoLog(shader_handle, message_size, nullptr, message.data());
  return message;
}

std::string_view GetSource(GLenum source) {
  switch (source) {
  case GL_DEBUG_SOURCE_API:
    return "API";
  case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
    return "WINDOW SYSTEM";
  case GL_DEBUG_SOURCE_SHADER_COMPILER:
    return "SHADER COMPILER";
  case GL_DEBUG_SOURCE_THIRD_PARTY:
    return "THIRD PARTY";
  case GL_DEBUG_SOURCE_APPLICATION:
    return "APPLICATION";
  case GL_DEBUG_SOURCE_OTHER:
    return "OTHER";
  }
  CORE_UNREACHABLE();
}

std::string_view GetType(GLenum type) {
  switch (type) {
  case GL_DEBUG_TYPE_ERROR:
    return "ERROR";
  case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
    return "DEPRECATED_BEHAVIOR";
  case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
    return "UNDEFINED_BEHAVIOR";
  case GL_DEBUG_TYPE_PORTABILITY:
    return "PORTABILITY";
  case GL_DEBUG_TYPE_PERFORMANCE:
    return "PERFORMANCE";
  case GL_DEBUG_TYPE_MARKER:
    return "MARKER";
  case GL_DEBUG_TYPE_OTHER:
    return "OTHER";
  }
  CORE_UNREACHABLE();
}

std::string_view GetSeverity(GLenum severity) {
  switch (severity) {
  case GL_DEBUG_SEVERITY_NOTIFICATION:
    return "NOTIFICATION";
  case GL_DEBUG_SEVERITY_LOW:
    return "LOW";
  case GL_DEBUG_SEVERITY_MEDIUM:
    return "MEDIUM";
  case GL_DEBUG_SEVERITY_HIGH:
    return "HIGH";
  }
  CORE_UNREACHABLE();
}

void MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                     GLchar const *message, void const *user_param) {
  std::printf("%s %s %s %#x %s\n", GetSource(source).data(), GetType(type).data(),
              GetSeverity(severity).data(), id, message);
}

void EnableDebug() {
  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback(MessageCallback, nullptr);
}

} // namespace Gloom