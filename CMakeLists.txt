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

set(MESH_SOURCES
  ${PROJECT_SOURCE_DIR}/gloom_mesh/gloom_model_loader.cpp
  ${PROJECT_SOURCE_DIR}/gloom_mesh/gloom_mesh.cpp
  ${PROJECT_SOURCE_DIR}/gloom_mesh/gloom_mesh_tools.cpp
  ${PROJECT_SOURCE_DIR}/gloom_mesh/gloom_primitives.cpp
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
)

set(GRAPHICS_SOURCES

)

set(GLOOM_SOURCES
  ${MESH_SOURCES}
  ${IMGUI_SOURCES}
  ${GUI_SOURCES}
  ${PROJECT_SOURCE_DIR}/external/glad/glad.c
  ${PROJECT_SOURCE_DIR}/gloom/vertex_array.cpp
  ${PROJECT_SOURCE_DIR}/gloom/renderbuffer.cpp
  ${PROJECT_SOURCE_DIR}/gloom/buffer.cpp
  ${PROJECT_SOURCE_DIR}/gloom/framebuffer.cpp
  ${PROJECT_SOURCE_DIR}/gloom/texture.cpp
  ${PROJECT_SOURCE_DIR}/gloom/gloom_commands.cpp
  ${PROJECT_SOURCE_DIR}/gloom/graphics_pipeline.cpp
  ${PROJECT_SOURCE_DIR}/gloom/graphics_types.cpp
  ${PROJECT_SOURCE_DIR}/gloom/gloom_debug.cpp
  ${PROJECT_SOURCE_DIR}/gloom/vertex_format.cpp
  ${PROJECT_SOURCE_DIR}/scene/camera.cpp
  ${PROJECT_SOURCE_DIR}/scene/material.cpp
  ${PROJECT_SOURCE_DIR}/renderer/gloom_renderer.cpp
  ${PROJECT_SOURCE_DIR}/core/gloom_tools.cpp
  ${PROJECT_SOURCE_DIR}/core/gloom_image.cpp
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
  ${PROJECT_SOURCE_DIR}/external/imgui/include
  ${PROJECT_SOURCE_DIR}/external/imgui/backend
  ${PROJECT_SOURCE_DIR}/core/include
  ${PROJECT_SOURCE_DIR}/scene/include
  ${PROJECT_SOURCE_DIR}/renderer/include
  ${PROJECT_SOURCE_DIR}/gloom_mesh/include
  ${PROJECT_SOURCE_DIR}/gui/include
  ${PROJECT_SOURCE_DIR}/gui/imgui
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