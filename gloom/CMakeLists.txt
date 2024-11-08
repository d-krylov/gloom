set(GLOOM_SOURCE_DIR ${PROJECT_SOURCE_DIR}/gloom)

set(MESH_SOURCES
  ${GLOOM_SOURCE_DIR}/mesh/wavefront_loader.cpp
  ${GLOOM_SOURCE_DIR}/mesh/primitives.cpp
  ${GLOOM_SOURCE_DIR}/mesh/assimp_loader.cpp
  ${GLOOM_SOURCE_DIR}/mesh/terrain.cpp
  ${GLOOM_SOURCE_DIR}/mesh/transform.cpp
  ${GLOOM_SOURCE_DIR}/mesh/model.cpp
)

set(GLOOM_WIDGET_SOURCES  
  ${GLOOM_SOURCE_DIR}/widgets/camera_widget.cpp
  ${GLOOM_SOURCE_DIR}/widgets/transform_widget.cpp
  ${GLOOM_SOURCE_DIR}/widgets/light_widget.cpp
  ${GLOOM_SOURCE_DIR}/widgets/editor_widget.cpp
)

set(GLOOM_GUI_SOURCES
  ${GLOOM_SOURCE_DIR}/gui/imgui/imgui_renderer.cpp
  ${GLOOM_SOURCE_DIR}/gui/imgui/imgui_layer.cpp
  ${GLOOM_SOURCE_DIR}/gui/window.cpp
  ${GLOOM_SOURCE_DIR}/gui/window_callback.cpp
)

set(GRAPHICS_SOURCES
  ${GLOOM_SOURCE_DIR}/graphics/buffer/buffer.cpp
  ${GLOOM_SOURCE_DIR}/graphics/pipeline/graphics_pipeline.cpp
  ${GLOOM_SOURCE_DIR}/graphics/pipeline/compute_pipeline.cpp
  ${GLOOM_SOURCE_DIR}/graphics/texture/texture.cpp
  ${GLOOM_SOURCE_DIR}/graphics/texture/sampler.cpp
  ${GLOOM_SOURCE_DIR}/graphics/texture/texture_2d.cpp
  ${GLOOM_SOURCE_DIR}/graphics/texture/renderbuffer.cpp
  ${GLOOM_SOURCE_DIR}/graphics/texture/framebuffer.cpp
  ${GLOOM_SOURCE_DIR}/graphics/graphics_types.cpp
  ${GLOOM_SOURCE_DIR}/graphics/graphics_command.cpp
  ${GLOOM_SOURCE_DIR}/graphics/debug.cpp
  ${GLOOM_SOURCE_DIR}/graphics/vertex/vertex_format.cpp
  ${GLOOM_SOURCE_DIR}/graphics/vertex/vertex_array.cpp
)

set(EXTERNAL_SOURCES
  ${imgui_SOURCE_DIR}/imgui_draw.cpp
  ${imgui_SOURCE_DIR}/imgui_tables.cpp
  ${imgui_SOURCE_DIR}/imgui_widgets.cpp
  ${imgui_SOURCE_DIR}/imgui.cpp
  ${PROJECT_SOURCE_DIR}/external/glad/glad.c
  ${PROJECT_SOURCE_DIR}/external/stb/stb_image.cpp
  ${PROJECT_SOURCE_DIR}/external/tinyobjloader/tiny_obj_loader.cc
)

set(RENDERER_SOURCES
  ${GLOOM_SOURCE_DIR}/renderer/renderer.cpp
  ${GLOOM_SOURCE_DIR}/renderer/model_renderer.cpp
  ${GLOOM_SOURCE_DIR}/renderer/primitive_renderer.cpp
)

set(SCENE_SOURCES
  ${GLOOM_SOURCE_DIR}/scene/camera.cpp
  ${GLOOM_SOURCE_DIR}/scene/perspective_camera.cpp
  ${GLOOM_SOURCE_DIR}/scene/orthographic_camera.cpp
)

set(CORE_SOURCES
  ${GLOOM_SOURCE_DIR}/core/tools.cpp
  ${GLOOM_SOURCE_DIR}/core/image.cpp
  ${GLOOM_SOURCE_DIR}/core/cubemap.cpp
)

set(GLOOM_SOURCES
  ${MESH_SOURCES}
  ${GLOOM_GUI_SOURCES}
  ${EXTERNAL_SOURCES}
  ${GRAPHICS_SOURCES}
  ${SCENE_SOURCES}
  ${GLOOM_WIDGET_SOURCES}
  ${RENDERER_SOURCES}
  ${CORE_SOURCES}
  ${GLOOM_SOURCE_DIR}/mathematics/triangle.cpp
  ${GLOOM_SOURCE_DIR}/mathematics/bounding_box.cpp
  ${GLOOM_SOURCE_DIR}/application/application.cpp
)

add_library(${PROJECT_NAME} SHARED 
  ${GLOOM_SOURCES}
)

target_include_directories(${PROJECT_NAME} PUBLIC
  ${GLOOM_SOURCE_DIR}
  ${ASSIMP_INCLUDE_DIR}
  ${PROJECT_SOURCE_DIR}/external/
  ${imgui_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME} PUBLIC 
  OpenGL::GL
  glfw
  glm::glm
  assimp
)

target_compile_definitions(${PROJECT_NAME} PUBLIC GLOOM_PROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}")