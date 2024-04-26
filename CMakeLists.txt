cmake_minimum_required(VERSION 3.25)

project(gloom)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_BUILD_TYPE Debug)

add_definitions(-DPROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}")

option(USE_GLFW "Use GLFW" ON)
option(USE_GLFW "Use SDL" ON)

find_package(glfw3  REQUIRED)
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

set(GLOOM_MESH_SOURCES
  ${PROJECT_SOURCE_DIR}/gloom_mesh/gloom_model_loader.cpp
  ${PROJECT_SOURCE_DIR}/gloom_mesh/gloom_mesh.cpp
  ${PROJECT_SOURCE_DIR}/gloom_mesh/gloom_mesh_tools.cpp
  ${PROJECT_SOURCE_DIR}/gloom_mesh/gloom_primitives.cpp
)

set(GLOOM_SOURCES
  ${GLOOM_MESH_SOURCES}
  ${PROJECT_SOURCE_DIR}/external/glad/glad.c
  ${PROJECT_SOURCE_DIR}/gloom/vertex_array.cpp
  ${PROJECT_SOURCE_DIR}/gloom/renderbuffer.cpp
  ${PROJECT_SOURCE_DIR}/gloom/buffer.cpp
  ${PROJECT_SOURCE_DIR}/gloom/framebuffer.cpp
  ${PROJECT_SOURCE_DIR}/gloom/texture.cpp
  ${PROJECT_SOURCE_DIR}/gloom/gloom_commands.cpp
  ${PROJECT_SOURCE_DIR}/gloom/shader_pipeline.cpp
  ${PROJECT_SOURCE_DIR}/gloom/gloom_types.cpp
  ${PROJECT_SOURCE_DIR}/gloom/gloom_debug.cpp
  ${PROJECT_SOURCE_DIR}/gloom/vertex_format.cpp
  ${PROJECT_SOURCE_DIR}/gloom_scene/camera.cpp
  ${PROJECT_SOURCE_DIR}/gloom_scene/material.cpp
  ${PROJECT_SOURCE_DIR}/gloom_renderer/gloom_renderer.cpp
  ${PROJECT_SOURCE_DIR}/gloom_tools/gloom_tools.cpp
  ${PROJECT_SOURCE_DIR}/gloom_tools/gloom_image.cpp
)

if(USE_GLFW)
set(GLOOM_SOURCES 
  ${GLOOM_SOURCES}
  ${PROJECT_SOURCE_DIR}/gui/GLFW_window.cpp
  ${PROJECT_SOURCE_DIR}/gui/GLFW_window_callback.cpp
)
endif()

if(USE_SDL)
set(GLOOM_SOURCES
  ${GLOOM_SOURCES}
  ${PROJECT_SOURCE_DIR}/gui/SDL_window.cpp
  ${PROJECT_SOURCE_DIR}/gui/SDL_window_callback.cpp
)
endif()

include(cmake/ClangFormat.cmake)

add_clang_format_target(format)

add_library(${PROJECT_NAME} SHARED 
  ${GLOOM_SOURCES}
)

target_include_directories(${PROJECT_NAME} PUBLIC
  ${PROJECT_SOURCE_DIR}/external/
  ${PROJECT_SOURCE_DIR}/gloom_tools/include
  ${PROJECT_SOURCE_DIR}/gloom_scene/include
  ${PROJECT_SOURCE_DIR}/gloom_renderer/include
  ${PROJECT_SOURCE_DIR}/gloom_mesh/include
  ${PROJECT_SOURCE_DIR}/gui/include
  ${PROJECT_SOURCE_DIR}/include
  ${SDL2_INCLUDE_DIRS}
)

set(LINK_LIBRARIES
  OpenGL::GL
)

if(USE_GLFW)
  set(LINK_LIBRARIES ${LINK_LIBRARIES} glfw)
endif()

if(USE_SDL)
  set(LINK_LIBRARIES ${LINK_LIBRARIES} ${SDL2_LIBRARIES})
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC 
  ${LINK_LIBRARIES}
)

add_subdirectory(examples)