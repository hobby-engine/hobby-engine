#include "opengl/gl_shader.hh"
#include "shader.hh"

#include <cstdio>
#include <cstdlib>

#include "glad/glad.h"

#include "log.hh"

static char* loadfile(const char* path)
{
  FILE* file = fopen(path, "rb");
  if (!file) {
    printf("%s\n", path);
    Logger::instance()->fatal("Failed to open file '%s'.", path);
  }

  fseek(file, 0, SEEK_END);
  size_t size = ftell(file);
  rewind(file);

  char* buf = new char[size + 1];
  if (!Logger::instance()->fassert(
        buf != NULL, "Not enough memory to read '%s'.", path)) {
    std::exit(1);
  }

  size_t read = fread(buf, sizeof(char), size, file);
  if (!Logger::instance()->fassert(
        read == size, "Failed to read '%s'.", path)) {
    std::exit(1);
  }

  buf[read] = '\0';

  fclose(file);

  return buf;
}

static inline int getgltype(ShaderType type)
{
  switch (type) {
    case ShaderType::Fragment:
      return GL_FRAGMENT_SHADER;
    case ShaderType::Vertex:
      return GL_VERTEX_SHADER;
  }
  return -1;
}

static unsigned int
createshader(const char* source, const char* path, ShaderType type)
{
  unsigned int shader = glCreateShader(getgltype(type));
  glShaderSource(shader, 1, &source, nullptr);

  glCompileShader(shader);

  int success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    char error[512];
    glGetShaderInfoLog(shader, 512, nullptr, error);
    if (path != nullptr) {
      Logger::instance()->fatal("Error compiling '%s': %s", path, error);
    } else {
      Logger::instance()->fatal(
        "Error compiling embedded shader: %s", path, error);
    }
    std::exit(1);
  }

  return shader;
}

unsigned int createprog(
  const char* vertsrc, const char* fragsrc, const char* vertpath,
  const char* fragpath)
{
  unsigned int vert = createshader(vertsrc, vertpath, ShaderType::Vertex);
  unsigned int frag = createshader(fragsrc, fragpath, ShaderType::Fragment);

  unsigned int handle = glCreateProgram();
  glAttachShader(handle, vert);
  glAttachShader(handle, frag);

  glLinkProgram(handle);

  int success;
  glGetProgramiv(handle, GL_LINK_STATUS, &success);
  if (!success) {
    char error[512];
    glGetProgramInfoLog(success, 512, nullptr, error);
    Logger::instance()->fatal(
      "Error linking shader '%s' and '%s': %s", vertpath, fragpath, error);
    std::exit(1);
  }

  glDeleteShader(vert);
  glDeleteShader(frag);

  return handle;
}

OpenGlShader::OpenGlShader(const char* vertpath, const char* fragpath)
{
  char* vertsrc = loadfile(vertpath);
  char* fragsrc = loadfile(fragpath);

  handle = createprog(vertsrc, fragsrc, vertpath, fragpath);

  delete[] vertsrc;
  delete[] fragsrc;
}

OpenGlShader::OpenGlShader(unsigned int handle) : handle(handle)
{
}

OpenGlShader OpenGlShader::embedded(const char* vertsrc, const char* fragsrc)
{
  unsigned int handle = createprog(vertsrc, fragsrc, nullptr, nullptr);
  return OpenGlShader(handle);
}

OpenGlShader::~OpenGlShader()
{
  glDeleteProgram(handle);
}

void OpenGlShader::apply()
{
  glUseProgram(handle);
}

static int getShaderLocation(unsigned int handle, const char* name)
{
  int location = glGetUniformLocation(handle, name);
  if (!Logger::instance()->fassert(
        location != -1, "Shader uniform '%s' doesn't exist.", name)) {
    std::exit(1);
  }
  return location;
}

void OpenGlShader::sendfloat(const char* name, float value)
{
  glUniform1f(getShaderLocation(handle, name), value);
}

void OpenGlShader::sendint(const char* name, int value)
{
  glUniform1i(getShaderLocation(handle, name), value);
}

void OpenGlShader::sendmat4(const char* name, const Mat4& value)
{
  glUniformMatrix4fv(
    getShaderLocation(handle, name), 1, GL_FALSE, value.data());
}

void OpenGlShader::sendcolor(const char* name, Color value)
{
  glUniform4f(
    getShaderLocation(handle, name), value.r, value.g, value.b, value.a);
}
