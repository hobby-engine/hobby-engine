find_library(LIB_GLFW glfw)
find_library(LIB_SDL SDL2)

set(ENGINE_SOURCE_FILES
  src/window.cc
  src/shader.cc
  src/texture.cc
  src/lib_impl.cc
)

set(ENGINE_HEADER_FILES
  include/point.h
  include/window.h
  include/shader.h
  include/texture.h
  include/vec2.h
)

set(ENGINE_THIRDPARTY_SOURCE_FILES
  thirdparty/glad/glad.c
)

add_library(
  ${POINT_LIB_NAME} SHARED

  ${ENGINE_SOURCE_FILES}
  ${ENGINE_HEADER_FILES}
  ${ENGINE_THIRDPARTY_SOURCE_FILES}
)
target_link_libraries(${POINT_LIB_NAME} PRIVATE ${LIB_GLFW} ${LIB_SDL})
target_include_directories(
  ${POINT_LIB_NAME} PRIVATE 
  src
  include
  thirdparty
)

