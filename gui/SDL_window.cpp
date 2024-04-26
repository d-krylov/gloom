#include "SDL_window.h"
#include "glad/glad.h"
#include <SDL2/SDL.h>

namespace Gloom {

void SDLInitialize() {
  SDL_GL_LoadLibrary(nullptr);
  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
}

SDL_window::SDL_window(std::string_view name, uint32_t width, uint32_t height) {
  auto status = SDL_Init(SDL_INIT_EVERYTHING);

  SDLInitialize();

  auto flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL;

  native_window_ = SDL_CreateWindow(name.data(), 0, 0, width, height, flags);

  if (native_window_ == nullptr) {
  }

  auto context = SDL_GL_CreateContext(native_window_);

  if (context == nullptr) {
  }

  status = gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
}

} // namespace Gloom
