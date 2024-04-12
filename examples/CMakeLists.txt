add_executable(triangle ${CMAKE_CURRENT_SOURCE_DIR}/triangle/triangle.cpp)
target_link_libraries(triangle PRIVATE gloom)

add_executable(texture ${CMAKE_CURRENT_SOURCE_DIR}/texture/texture.cpp)
target_link_libraries(texture PRIVATE gloom)

add_executable(separated_buffers 
  ${CMAKE_CURRENT_SOURCE_DIR}/separated_buffers/separated_buffers.cpp
)

target_link_libraries(separated_buffers PRIVATE gloom)