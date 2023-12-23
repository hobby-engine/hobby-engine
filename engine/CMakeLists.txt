find_library(LIB_SDL NAME SDL2)

set(ENGINE_SOURCE_FILES
  src/window.cc
  src/draw.cc
  src/texture.cc
  src/vec2.cc
  src/event_impl.cc
  src/lib_impl.cc
)

set(ENGINE_HEADER_FILES
  include/point.hh
  include/window.hh
  include/draw.hh
  include/event.hh
  include/event/key.hh
  include/color.hh
  include/texture.hh
  include/vec2.hh
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
target_link_libraries(${POINT_LIB_NAME} PRIVATE
  ${LIB_SDL}
)

target_include_directories(${POINT_LIB_NAME} PRIVATE 
  src
  include
  thirdparty
)

