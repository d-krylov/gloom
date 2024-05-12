add_executable(triangle ${CMAKE_CURRENT_SOURCE_DIR}/triangle/triangle.cpp)
target_link_libraries(triangle PRIVATE gloom)

add_executable(learn_opengl_texture ${CMAKE_CURRENT_SOURCE_DIR}/learn_opengl_texture/learn_opengl_texture.cpp)
target_link_libraries(learn_opengl_texture PRIVATE gloom)

add_executable(separated_buffers ${CMAKE_CURRENT_SOURCE_DIR}/separated_buffers/separated_buffers.cpp)
target_link_libraries(separated_buffers PRIVATE gloom)

add_executable(learn_opengl_camera ${CMAKE_CURRENT_SOURCE_DIR}/learn_opengl_camera/learn_opengl_camera.cpp)
target_link_libraries(learn_opengl_camera PRIVATE gloom)

add_executable(example ${CMAKE_CURRENT_SOURCE_DIR}/example/example.cpp)
target_link_libraries(example PRIVATE gloom)