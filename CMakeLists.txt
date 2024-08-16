cmake_minimum_required(VERSION 3.25)

project(gloom)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_BUILD_TYPE Debug)

add_definitions(-DPROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}")

find_package(glfw3  REQUIRED)
find_package(OpenGL REQUIRED)

include(cmake/Libraries.cmake)

FetchContent_MakeAvailable(glm)

add_definitions(-DGLM_ENABLE_EXPERIMENTAL)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-volatile")

set(MESH_SOURCES
  ${PROJECT_SOURCE_DIR}/gloom_mesh/wavefront_loader.cpp
  ${PROJECT_SOURCE_DIR}/gloom_mesh/mesh.cpp
  ${PROJECT_SOURCE_DIR}/gloom_mesh/primitives.cpp
  ${PROJECT_SOURCE_DIR}/gloom_mesh/khronos_loader.cpp
  ${PROJECT_SOURCE_DIR}/gloom_mesh/terrain.cpp
  ${PROJECT_SOURCE_DIR}/gloom_mesh/transform.cpp
)

set(IMGUI_SOURCES
  ${PROJECT_SOURCE_DIR}/external/imgui/sources/imgui_draw.cpp
  ${PROJECT_SOURCE_DIR}/external/imgui/sources/imgui_tables.cpp
  ${PROJECT_SOURCE_DIR}/external/imgui/sources/imgui_widgets.cpp
  ${PROJECT_SOURCE_DIR}/external/imgui/sources/imgui.cpp
)

set(GLOOM_WIDGET_SOURCES  
  ${PROJECT_SOURCE_DIR}/gloom_widgets/camera_widget.cpp
  ${PROJECT_SOURCE_DIR}/gloom_widgets/transform_widget.cpp
)

set(GLOOM_GUI_SOURCES
  ${PROJECT_SOURCE_DIR}/gui/imgui/imgui_renderer.cpp
  ${PROJECT_SOURCE_DIR}/gui/imgui/imgui_platform.cpp
  ${PROJECT_SOURCE_DIR}/gui/imgui/imgui_helpers.cpp
  ${PROJECT_SOURCE_DIR}/gui/window.cpp
  ${PROJECT_SOURCE_DIR}/gui/window_callback.cpp
)

set(GRAPHICS_SOURCES
  ${PROJECT_SOURCE_DIR}/graphics/buffer/buffer.cpp
  ${PROJECT_SOURCE_DIR}/graphics/graphics_pipeline/graphics_pipeline.cpp
  ${PROJECT_SOURCE_DIR}/graphics/compute_pipeline/compute_pipeline.cpp
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
  ${PROJECT_SOURCE_DIR}/renderer/direct_renderer.cpp
)

set(SCENE_SOURCES
  ${PROJECT_SOURCE_DIR}/scene/camera.cpp
)

set(GLOOM_SOURCES
  ${MESH_SOURCES}
  ${IMGUI_SOURCES}
  ${GLOOM_GUI_SOURCES}
  ${RENDERER_SOURCES}
  ${GRAPHICS_SOURCES}
  ${SCENE_SOURCES}
  ${GLOOM_WIDGET_SOURCES}
  ${PROJECT_SOURCE_DIR}/external/glad/glad.c
  ${PROJECT_SOURCE_DIR}/external/tinygltf/tiny_gltf.cc
  ${PROJECT_SOURCE_DIR}/external/easyloggingpp/easylogging++.cc
  ${PROJECT_SOURCE_DIR}/external/tinyobjloader/tiny_obj_loader.cc
  ${PROJECT_SOURCE_DIR}/gloom_core/tools.cpp
  ${PROJECT_SOURCE_DIR}/gloom_core/image.cpp
  ${PROJECT_SOURCE_DIR}/gloom_core/cubemap.cpp
  ${PROJECT_SOURCE_DIR}/gloom_mathematics/triangle.cpp
  ${PROJECT_SOURCE_DIR}/gloom_mathematics/bounding_box.cpp
  ${PROJECT_SOURCE_DIR}/gloom/application.cpp
)

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  
  include(cmake/ClangFormat.cmake)

  add_clang_format_target(format)

  add_subdirectory(examples)

endif()

add_library(${PROJECT_NAME} SHARED 
  ${GLOOM_SOURCES}
)

target_include_directories(${PROJECT_NAME} PUBLIC
  ${PROJECT_SOURCE_DIR}
  ${PROJECT_SOURCE_DIR}/external/
  ${PROJECT_SOURCE_DIR}/graphics/graphics_pipeline
  ${PROJECT_SOURCE_DIR}/external/imgui/include
  ${PROJECT_SOURCE_DIR}/external/imgui/backend
  ${PROJECT_SOURCE_DIR}/scene/include
  ${PROJECT_SOURCE_DIR}/gui/include
  ${PROJECT_SOURCE_DIR}/gui/imgui
)

target_link_libraries(${PROJECT_NAME} PUBLIC 
  OpenGL::GL
  glfw
  glm::glm
)