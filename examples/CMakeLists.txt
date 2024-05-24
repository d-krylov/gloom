add_executable(example_1 ${CMAKE_CURRENT_SOURCE_DIR}/example_1/example_1.cpp)
target_link_libraries(example_1 PRIVATE gloom)

add_executable(example_2 ${CMAKE_CURRENT_SOURCE_DIR}/example_2/example_2.cpp)
target_link_libraries(example_2 PRIVATE gloom)

add_executable(separated_buffers ${CMAKE_CURRENT_SOURCE_DIR}/separated_buffers/separated_buffers.cpp)
target_link_libraries(separated_buffers PRIVATE gloom)

add_executable(example ${CMAKE_CURRENT_SOURCE_DIR}/example/example.cpp)
target_link_libraries(example PRIVATE gloom)