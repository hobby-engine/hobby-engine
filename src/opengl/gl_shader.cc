#include "opengl/gl_shader.hh"
#include "shader.hh"

#include <cstdio>
#include <cstdlib>

#include "glad/glad.h"

#include "log.hh"

static char* loadFile(const char* path)
{
  FILE* file = fopen(path, "rb");
  if (!file) {
    printf("%s\n", path);
    fatal("Failed to open file '%s'.", path);
  }

  fseek(file, 0, SEEK_END);
  size_t fileLength = ftell(file);
  rewind(file);

  char* buf = new char[fileLength + 1];
  fatalAssert(buf != NULL, "Not enough memory to read '%s'.", path);

  size_t bytesRead = fread(buf, sizeof(char), fileLength, file);
  fatalAssert(bytesRead == fileLength, "Failed to read '%s'.", path);

  buf[bytesRead] = '\0';

  fclose(file);

  return buf;
}

static inline int getGlShaderType(ShaderType type)
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
createShader(const char* source, const char* path, ShaderType type)
{
  unsigned int shader = glCreateShader(getGlShaderType(type));
  glShaderSource(shader, 1, &source, nullptr);

  glCompileShader(shader);

  int success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    char error[512];
    glGetShaderInfoLog(shader, 512, nullptr, error);
    if (path != nullptr) {
      fatal("Error compiling '%s': %s", path, error);
    } else {
      fatal("Error compiling embedded shader: %s", path, error);
    }
  }

  return shader;
}

unsigned int createProgram(
  const char* vertSource, const char* fragSource, const char* vertPath,
  const char* fragPath)
{
  unsigned int vert = createShader(vertSource, vertPath, ShaderType::Vertex);
  unsigned int frag = createShader(fragSource, fragPath, ShaderType::Fragment);

  unsigned int handle = glCreateProgram();
  glAttachShader(handle, vert);
  glAttachShader(handle, frag);

  glLinkProgram(handle);

  int success;
  glGetProgramiv(handle, GL_LINK_STATUS, &success);
  if (!success) {
    char error[512];
    glGetProgramInfoLog(success, 512, nullptr, error);
    fatal("Error linking shader '%s' and '%s': %s", vertPath, fragPath, error);
  }

  glDeleteShader(vert);
  glDeleteShader(frag);

  return handle;
}

OpenGlShader::OpenGlShader(const char* vertPath, const char* fragPath)
{
  char* vertSource = loadFile(vertPath);
  char* fragSource = loadFile(fragPath);

  handle = createProgram(vertSource, fragSource, vertPath, fragPath);

  delete[] vertSource;
  delete[] fragSource;
}

OpenGlShader::OpenGlShader(unsigned int handle) : handle(handle)
{
}

OpenGlShader
OpenGlShader::embedded(const char* vertSource, const char* fragSource)
{
  unsigned int handle = createProgram(vertSource, fragSource, nullptr, nullptr);
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
  fatalAssert(location != -1, "Shader uniform '%s' doesn't exist.", name);
  return location;
}

void OpenGlShader::sendFloat(const char* name, float value)
{
  glUniform1f(getShaderLocation(handle, name), value);
}

void OpenGlShader::sendInt(const char* name, int value)
{
  glUniform1i(getShaderLocation(handle, name), value);
}

void OpenGlShader::sendMat4(const char* name, const Mat4& value)
{
  glUniformMatrix4fv(
    getShaderLocation(handle, name), 1, GL_FALSE, value.data());
}

void OpenGlShader::sendColor(const char* name, Color value)
{
  glUniform4f(
    getShaderLocation(handle, name), value.r, value.g, value.b, value.a);
}
