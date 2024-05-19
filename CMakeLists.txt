cmake_minimum_required(VERSION 3.25)

project(gloom)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_BUILD_TYPE Debug)

add_definitions(-DPROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}")

find_package(glfw3  REQUIRED)
find_package(OpenGL REQUIRED)

set(MESH_SOURCES
  ${PROJECT_SOURCE_DIR}/mesh/gloom_mesh_tools.cpp
  ${PROJECT_SOURCE_DIR}/mesh/mesh_loader.cpp
  ${PROJECT_SOURCE_DIR}/mesh/mesh.cpp
  ${PROJECT_SOURCE_DIR}/mesh/primitives.cpp
)

set(IMGUI_BACKEND_SOURCES
  ${PROJECT_SOURCE_DIR}/external/imgui/backend/imgui_impl_glfw.cpp
  ${PROJECT_SOURCE_DIR}/external/imgui/backend/imgui_impl_opengl3.cpp
)

set(IMGUI_SOURCES
  ${PROJECT_SOURCE_DIR}/external/imgui/sources/imgui_draw.cpp
  ${PROJECT_SOURCE_DIR}/external/imgui/sources/imgui_tables.cpp
  ${PROJECT_SOURCE_DIR}/external/imgui/sources/imgui_widgets.cpp
  ${PROJECT_SOURCE_DIR}/external/imgui/sources/imgui.cpp
  ${IMGUI_BACKEND_SOURCES}
)

set(GUI_SOURCES
  ${PROJECT_SOURCE_DIR}/gui/imgui/imgui_renderer.cpp
  ${PROJECT_SOURCE_DIR}/gui/imgui/imgui_platform.cpp
  ${PROJECT_SOURCE_DIR}/gui/imgui/imgui_helpers.cpp
  ${PROJECT_SOURCE_DIR}/gui/window.cpp
  ${PROJECT_SOURCE_DIR}/gui/window_callback.cpp
)

set(GRAPHICS_SOURCES
  ${PROJECT_SOURCE_DIR}/graphics/buffer/buffer.cpp
  ${PROJECT_SOURCE_DIR}/graphics/graphics_pipeline/graphics_pipeline.cpp
  ${PROJECT_SOURCE_DIR}/graphics/graphics_pipeline/shader_reflection.cpp
  ${PROJECT_SOURCE_DIR}/graphics/texture/texture.cpp
  ${PROJECT_SOURCE_DIR}/graphics/texture/sampler.cpp
  ${PROJECT_SOURCE_DIR}/graphics/texture/renderbuffer.cpp
  ${PROJECT_SOURCE_DIR}/graphics/texture/framebuffer.cpp
  ${PROJECT_SOURCE_DIR}/graphics/graphics_types.cpp
  ${PROJECT_SOURCE_DIR}/graphics/debug.cpp
  ${PROJECT_SOURCE_DIR}/graphics/commands.cpp
  ${PROJECT_SOURCE_DIR}/graphics/vertex/vertex_format.cpp
  ${PROJECT_SOURCE_DIR}/graphics/vertex/vertex_array.cpp
)

set(RENDERER_SOURCES
  ${PROJECT_SOURCE_DIR}/renderer/renderer.cpp
)

set(GLOOM_SOURCES
  ${MESH_SOURCES}
  ${IMGUI_SOURCES}
  ${GUI_SOURCES}
  ${RENDERER_SOURCES}
  ${GRAPHICS_SOURCES}
  ${PROJECT_SOURCE_DIR}/external/glad/glad.c

  ${PROJECT_SOURCE_DIR}/scene/camera.cpp
  ${PROJECT_SOURCE_DIR}/scene/material.cpp

  ${PROJECT_SOURCE_DIR}/core/gloom_tools.cpp
  ${PROJECT_SOURCE_DIR}/core/gloom_image.cpp
)

include(cmake/ClangFormat.cmake)

add_clang_format_target(format)

add_library(${PROJECT_NAME} SHARED 
  ${GLOOM_SOURCES}
)

target_include_directories(${PROJECT_NAME} PUBLIC
  ${PROJECT_SOURCE_DIR}/external/
  ${PROJECT_SOURCE_DIR}/graphics/texture
  ${PROJECT_SOURCE_DIR}/graphics/buffer
  ${PROJECT_SOURCE_DIR}/graphics/include
  ${PROJECT_SOURCE_DIR}/graphics/vertex
  ${PROJECT_SOURCE_DIR}/graphics/graphics_pipeline
  ${PROJECT_SOURCE_DIR}/external/imgui/include
  ${PROJECT_SOURCE_DIR}/external/imgui/backend
  ${PROJECT_SOURCE_DIR}/core/include
  ${PROJECT_SOURCE_DIR}/scene/include
  ${PROJECT_SOURCE_DIR}/renderer/include
  ${PROJECT_SOURCE_DIR}/mesh/include
  ${PROJECT_SOURCE_DIR}/gui/include
  ${PROJECT_SOURCE_DIR}/gui/imgui
  ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} PUBLIC 
  OpenGL::GL
  glfw
)

add_subdirectory(examples)