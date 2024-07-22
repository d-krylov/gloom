set(EXECUTABLES
  compute_raytracing
  wavefront_viewer
  raymarching
  khronos_viewer
  skybox
  terrain
)

foreach(exe ${EXECUTABLES})
  add_executable(${exe} ${CMAKE_CURRENT_SOURCE_DIR}/${exe}/${exe}.cpp)
  target_link_libraries(${exe} PRIVATE gloom)
endforeach()