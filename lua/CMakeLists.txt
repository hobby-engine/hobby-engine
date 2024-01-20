find_library(LIB_LUA luajit-5.1)

set(LUA_SOURCE_FILES
  src/main.cc
  src/wrap_texture.cc
  src/wrap_input.cc
  src/wrap_window.cc
  src/wrap_draw.cc
  src/wrap_time.cc
  src/wrap_app.cc
)

set(LUA_HEADER_FILES
  src/wrap.hh
  src/wrap_texture.hh
  src/wrap_input.hh
  src/wrap_window.hh
  src/wrap_draw.hh
  src/wrap_time.hh
  src/wrap_app.hh
)

add_executable(
  ${HOBBY_LUA_NAME}

  ${LUA_SOURCE_FILES}
  ${LUA_HEADER_FILES}
)
target_link_libraries(${HOBBY_LUA_NAME} PRIVATE ${HOBBY_LIB_NAME})
target_include_directories(${HOBBY_LUA_NAME} PRIVATE
  ../engine/include
  thirdparty
  src
)
target_link_libraries(${HOBBY_LUA_NAME} PRIVATE
  ${LIB_LUA}
)
