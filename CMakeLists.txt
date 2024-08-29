cmake_minimum_required(VERSION 3.25)

project(gloom)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_BUILD_TYPE Debug)

add_definitions(-DPROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}")

find_package(glfw3  REQUIRED)
find_package(OpenGL REQUIRED)
find_package(assimp REQUIRED)

include(cmake/Libraries.cmake)

FetchContent_MakeAvailable(glm)

add_definitions(-DGLM_ENABLE_EXPERIMENTAL)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-volatile")

add_subdirectory(gloom)

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  
  include(cmake/ClangFormat.cmake)

  add_clang_format_target(format "build;external")

  add_subdirectory(examples)

endif()

