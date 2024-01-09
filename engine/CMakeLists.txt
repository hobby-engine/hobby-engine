find_library(LIB_SDL SDL2)
find_library(LIB_SDL_IMAGE SDL2_image)

set(ENGINE_SOURCE_FILES
  src/vec2.cc
  src/event_impl.cc
  src/window.cc
  src/texture.cc
  src/draw.cc
)

set(ENGINE_SDL2_FILES
)

set(ENGINE_HEADER_FILES
  include/hobby.hh
  include/draw.hh
  include/texture.hh
  include/input_types.hh
  include/transform.hh
  include/types.hh
  include/event.hh
  include/event/key.hh
  include/event/mouse.hh
  include/color.hh
  include/vec2.hh
  include/window.hh
)

set(ENGINE_THIRDPARTY_SOURCE_FILES
)

add_library(
  ${HOBBY_LIB_NAME} SHARED

  ${ENGINE_SOURCE_FILES}
  ${ENGINE_SDL2_FILES}
  ${ENGINE_HEADER_FILES}
  ${ENGINE_THIRDPARTY_SOURCE_FILES}
)
target_link_libraries(${HOBBY_LIB_NAME} PRIVATE
  ${LIB_SDL}
  ${LIB_SDL_IMAGE}
)

target_include_directories(${HOBBY_LIB_NAME} PRIVATE 
  src
  include
  thirdparty
)

