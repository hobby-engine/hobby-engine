cmake_minimum_required(VERSION 3.29)
project(hobby)

if(LINUX OR APPLE)
  set(DLL_EXT so)
  set(STATIC_EXT a)
elseif(WIN32)
  set(DLL_EXT dll)
  set(STATIC_EXT lib)
endif()

set(SRC
  src/main.cc src/log.cc src/shader.cc src/mat4.cc
  src/engine.cc src/time.cc
  
  src/glfw/glfw_window.cc src/glfw/glfw_input.cc
  
  src/opengl/gl_renderer.cc src/opengl/gl_shader.cc 
  src/opengl/vertex.cc src/opengl/gl_texture.cc
  
  src/lua_wrapper/wrapper.cc src/lua_wrapper/wrap_renderer.cc
  src/lua_wrapper/wrap_engine.cc src/lua_wrapper/wrap_input.cc
  src/lua_wrapper/wrap_log.cc src/lua_wrapper/wrap_texture.cc
  src/lua_wrapper/wrap_window.cc

  third/glad/src/glad.c
  third/stb/stb_image.c
)

if(CONFIG STREQUAL "release")
  set(CXXFLAGS "-O3")
else()
  set(CXXFLAGS "-O3 -g")
  # I don't know if asan is on Mac too, but I don't really wanna find out
  if(LINUX)
    set(CXXFLAGS "${CXXFLAGS} -fsanitize=address")
  endif()
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
file(COPY src/lua DESTINATION src)
