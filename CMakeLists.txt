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
  point
  VERSION 0.1.0
  LANGUAGES CXX C
)

set(POINT_LUA_NAME pointlua)
set(POINT_LIB_NAME point)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-O2 -Wall -Wextra")

add_subdirectory(engine)
add_subdirectory(lua)
