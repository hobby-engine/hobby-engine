cmake_minimum_required(VERSION 3.28.0)

if(WIN32)
  add_compile_definitions(POINT_WIN)
elseif(LINUX)
  add_compile_definitions(POINT_LINUX POINT_UNIX)
elseif(APPLE)
  add_compile_definitions(POINT_APPLE POINT_UNIX)
elseif(BSD)
  add_compile_definitions(POINT_BSD POINT_UNIX)
endif()

project(
  hobby
  VERSION 0.1.0
  LANGUAGES CXX C
)

set(HOBBY_LUA_NAME hobbylua)
set(HOBBY_LIB_NAME hobby)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-O2 -Wall -Wextra")

# Allow custom options (in my case, -fsanitize=address for debugging)
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/CustomOpts.cmake)
  message("Custom Opts!")
  include(${CMAKE_CURRENT_SOURCE_DIR}/CustomOpts.cmake)
endif()


add_subdirectory(engine)
add_subdirectory(lua)
