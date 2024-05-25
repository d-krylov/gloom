add_executable(example_1 ${CMAKE_CURRENT_SOURCE_DIR}/example_1/example_1.cpp)
target_link_libraries(example_1 PRIVATE gloom)

add_executable(example_2 ${CMAKE_CURRENT_SOURCE_DIR}/example_2/example_2.cpp)
target_link_libraries(example_2 PRIVATE gloom)

add_executable(example_3 ${CMAKE_CURRENT_SOURCE_DIR}/example_3/example_3.cpp)
target_link_libraries(example_3 PRIVATE gloom)

add_executable(example ${CMAKE_CURRENT_SOURCE_DIR}/example/example.cpp)
target_link_libraries(example PRIVATE gloom)