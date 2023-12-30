find_library(LIB_LUA luajit-5.1)

set(LUA_SOURCE_FILES
  src/main.cc
  src/wrap_window.cc
  src/wrap_graphics.cc
)

add_executable(
  ${HOBBY_LUA_NAME}

  ${LUA_SOURCE_FILES}
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
