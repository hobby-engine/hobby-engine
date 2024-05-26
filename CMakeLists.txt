cmake_minimum_required(VERSION 3.29)
project(hobby)

if(LINUX OR APPLE)
  set(DLL_EXT so)
  set(STATIC_EXT a)
elseif(WIN32)
  set(DLL_EXT dll)
  set(STATIC_EXT lib)
endif()

if(LINUX)
  add_compile_definitions(HB_LINUX)
  add_compile_definitions(HB_POSIX)
elseif(APPLE)
  add_compile_definitions(HB_APPLE)
  add_compile_definitions(HB_POSIX)
elseif(WIN32)
  add_compile_definitions(HB_WINDOWS)
else()
  message(FATAL_ERROR "Platform not supported, and there are no plans to support.")
endif()

set(SRC
  # Main
  src/main.cc
  src/log.cc
  src/mat4.cc
  src/engine.cc
  src/time.cc
  src/renderer.cc
  src/mesh.cc
  src/window.cc
  
  # GLFW implementation
  src/glfw/glfw_window.cc
  src/glfw/glfw_input.cc
  
  # OpenGL implementation
  src/opengl/gl_renderer.cc
  src/opengl/gl_shader.cc 
  src/opengl/vertex.cc
  src/opengl/gl_texture.cc
  
  # Lua
  src/lua_wrapper/wrapper.cc
  src/lua_wrapper/wrap_renderer.cc
  src/lua_wrapper/wrap_engine.cc
  src/lua_wrapper/wrap_input.cc
  src/lua_wrapper/wrap_log.cc
  src/lua_wrapper/wrap_texture.cc
  src/lua_wrapper/wrap_window.cc

  # Thirdparty
  third/glad/src/glad.c
  third/stb/stb_image.c
)

set(CXXFLAGS "-fno-exceptions -Wall -Wextra")
add_compile_options(-Wall -Wextra -fno-exceptions)

if(CONFIG STREQUAL "release")
  add_compile_options(-O3)
  add_compile_definitions(HB_RELEASE)
else()
  add_compile_options(-O2 -g)
  # I don't know if asan is on Mac too, but I don't really wanna find out
  if(LINUX)
    add_compile_options(-fsanitize=address -fsanitize=undefined)
    add_link_options(-fsanitize=address -fsanitize=undefined)
  endif()
  add_compile_definitions(HB_DEBUG)
endif()

add_executable(hobby ${SRC})
target_include_directories(hobby PRIVATE src third third/glad/include third/luajit)
target_link_libraries(
  hobby
  ${CMAKE_SOURCE_DIR}/bin/libglfw3.a
  ${CMAKE_SOURCE_DIR}/bin/libluajit.a
)

# Just for testing, remove once Lua scripts and shaders are embedded
file(COPY res DESTINATION .)
