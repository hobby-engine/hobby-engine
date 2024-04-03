#include "shader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "glad/glad.h"

#include "log.h"

static char* loadFile(const char* path) {
  FILE* file = fopen(path, "rb");
  if (!file) {
    printf("%s\n", path);
    fatal("Failed to open file '%s'.", path);
  }

  fseek(file, 0, SEEK_END);
  size_t fileLength = ftell(file);
  rewind(file);

  char* buf = (char*)malloc(fileLength + 1);
  fatalAssert(buf != NULL, "Not enough memory to read '%s'.", path);

  size_t bytesRead = fread(buf, sizeof(char), fileLength, file);
  fatalAssert(bytesRead == fileLength, "Failed to read '%s'.", path);

  buf[bytesRead] = '\0';

  fclose(file);

  return buf;
}

static inline s32 getGlShaderType(enum ShaderType type) {
  switch (type) {
    case SHADER_TYPE_FRAGMENT:
      return GL_FRAGMENT_SHADER;
    case SHADER_TYPE_VERTEX:
      return GL_VERTEX_SHADER;
  }
  return -1;
}

static void compileShader(u32 shader, const char* path) {
  glCompileShader(shader);

  int success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    char errorMessage[512];
    glGetShaderInfoLog(shader, 512, NULL, errorMessage);
    if (path == NULL) {
      fatal("Error compiling: %s", errorMessage);
    } else {
      fatal("Error compiling '%s': %s", path, errorMessage);
    }
  }
}

static u32 createShader(
    const char* source, const char* path, enum ShaderType type) {
  u32 id = glCreateShader(getGlShaderType(type));
  glShaderSource(id, 1, &source, NULL);
  compileShader(id, path);

  return id;
}

static struct Shader createShaderProgram() {
  u32 id = glCreateProgram();

  struct Shader program;
  program.glId = id;
  return program;
}

static void linkProgram(struct Shader* program) {
  glLinkProgram(program->glId);

  int success;
  glGetProgramiv(program->glId, GL_LINK_STATUS, &success);
  if (!success) {
    char errorMessage[512];
    glGetProgramInfoLog(program->glId, 512, NULL, errorMessage);
    fatal(errorMessage);
  }
}

struct Shader createInternalShader(
    const char* vertSource, const char* fragSource) {
  u32 vertex = createShader(vertSource, NULL, SHADER_TYPE_VERTEX);
  u32 fragment = createShader(fragSource, NULL, SHADER_TYPE_FRAGMENT);
  struct Shader program = createShaderProgram();

  glAttachShader(program.glId, vertex);
  glAttachShader(program.glId, fragment);

  linkProgram(&program);
  return program;
}

struct Shader loadShader(const char* vertPath, const char* fragPath) {
  char* vertSource = loadFile(vertPath);
  char* fragSource = loadFile(fragPath);

  u32 vertex = createShader(vertSource, vertPath, SHADER_TYPE_VERTEX);
  u32 fragment = createShader(fragSource, fragPath, SHADER_TYPE_FRAGMENT);

  struct Shader program = createShaderProgram();

  glAttachShader(program.glId, vertex);
  glAttachShader(program.glId, fragment);

  linkProgram(&program);

  free(vertSource);
  free(fragSource);
  return program;
}

void destroyShader(struct Shader* program) {
  glDeleteProgram(program->glId);
}

void useShader(struct Shader* program) {
  glUseProgram(program->glId);
}

void setShaderF32(struct Shader* program, const char* name, f32 value) {
  glUniform1f(glGetUniformLocation(program->glId, name), value);
}

void setShaderVec2(struct Shader* program, const char* name, vec2 value) {
  glUniform2f(glGetUniformLocation(program->glId, name), value[0], value[1]);
}

void setShaderProgramVec3(struct Shader* program, const char* name, vec3 value) {
  glUniform3f(glGetUniformLocation(program->glId, name), value[0], value[1], value[3]);
}

void setShaderVec4(struct Shader* program, const char* name, vec4 value) {
  glUniform4f(glGetUniformLocation(program->glId, name), value[0], value[1], value[3], value[4]);
}

void setShaderMat4(struct Shader* program, const char* name, mat4x4 value) {
  glUniformMatrix4fv(glGetUniformLocation(program->glId, name),
                     1, GL_FALSE, *value);
}

void setShaderColor(struct Shader* program, const char* name, struct Color value) {
  glUniform4f(glGetUniformLocation(program->glId, name), value.r, value.g, value.b, value.a);
}
