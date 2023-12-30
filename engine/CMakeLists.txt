find_library(LIB_SDL SDL2)

set(ENGINE_SOURCE_FILES
  src/window.cc
  src/input.cc
  src/graphics.cc
  src/shader.cc
  src/builtin_shaders.cc
  src/quad.cc
  src/texture.cc
  src/vec2.cc
  src/event_impl.cc
  src/lib_impl.cc
)

set(ENGINE_HEADER_FILES
  include/hobby.hh
  include/window.hh
  include/input.hh
  include/input_types.hh
  include/graphics.hh
  include/event.hh
  include/event/key.hh
  include/event/mouse.hh
  include/color.hh
  include/texture.hh
  include/vec2.hh
)

set(ENGINE_THIRDPARTY_SOURCE_FILES
  thirdparty/glad/glad.c
)

add_library(
  ${HOBBY_LIB_NAME} SHARED

  ${ENGINE_SOURCE_FILES}
  ${ENGINE_HEADER_FILES}
  ${ENGINE_THIRDPARTY_SOURCE_FILES}
)
target_link_libraries(${HOBBY_LIB_NAME} PRIVATE
  ${LIB_SDL}
)

target_include_directories(${HOBBY_LIB_NAME} PRIVATE 
  src
  include
  thirdparty
)

