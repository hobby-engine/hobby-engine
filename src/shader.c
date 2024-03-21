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
    hb_error("Failed to open file '%s'.", path);
  }

  fseek(file, 0, SEEK_END);
  size_t fileLength = ftell(file);
  rewind(file);

  char* buf = (char*)malloc(fileLength + 1);
  hb_assert(buf != NULL, "Not enough memory to read '%s'.", path);

  size_t bytesRead = fread(buf, sizeof(char), fileLength, file);
  hb_assert(bytesRead == fileLength, "Failed to read '%s'.", path);

  buf[bytesRead] = '\0';

  fclose(file);

  return buf;
}

static inline int getGlShaderType(hb_ShaderType type) {
  switch (type) {
    case hb_SHADER_TYPE_FRAGMENT:
      return GL_FRAGMENT_SHADER;
    case hb_SHADER_TYPE_VERTEX:
      return GL_VERTEX_SHADER;
  }
  return -1;
}

hb_Shader* hb_createShader(const char* source, hb_ShaderType type) {
  u32 id = glCreateShader(getGlShaderType(type));
  glShaderSource(id, 1, &source, NULL);

  hb_Shader* shader = (hb_Shader*)malloc(sizeof(hb_Shader));
  shader->glId = id;
  shader->type = type;
  shader->path = NULL;

  return shader;
}

hb_Shader* hb_loadShader(const char* path, hb_ShaderType type) {
  char* source = loadFile(path);
  hb_Shader* shader = hb_createShader(source, type);
  shader->path = path;
  free(source);
  return shader;
}

void hb_compileShader(hb_Shader* shader) {
  glCompileShader(shader->glId);

  int success;
  glGetShaderiv(shader->glId, GL_COMPILE_STATUS, &success);
  if (!success) {
    char errorMessage[512];
    glGetShaderInfoLog(shader->glId, 512, NULL, errorMessage);
    if (shader->path == NULL) {
      hb_error("Error compiling: %s", errorMessage);
    } else {
      hb_error("Error compiling '%s': %s", shader->path, errorMessage);
    }
  }
}

hb_Shader* hb_createAndCompileShader(const char* source, hb_ShaderType type) {
  hb_Shader* shader = hb_createShader(source, type);
  hb_compileShader(shader);
  return shader;
}

hb_Shader* hb_loadAndCompileShader(const char *path, hb_ShaderType type) {
  hb_Shader* shader = hb_loadShader(path, type);
  hb_compileShader(shader);
  return shader;
}

void hb_destroyShader(hb_Shader* shader) {
  glDeleteShader(shader->glId);
  free(shader);
}

hb_ShaderProgram hb_createShaderProgram() {
  u32 id = glCreateProgram();

  hb_ShaderProgram program;
  program.glId = id;
  program.vertex = NULL;
  program.fragment = NULL;
  return program;
}

void hb_addShaderToProgram(hb_ShaderProgram* program, hb_Shader* shader) {
  glAttachShader(program->glId, shader->glId);

  switch (shader->type) {
    case hb_SHADER_TYPE_VERTEX:
      program->vertex = shader;
      break;
    case hb_SHADER_TYPE_FRAGMENT:
      program->fragment = shader;
      break;
    default:
      hb_error("Invalid shader type.");
      break;
  }
}

void hb_linkProgram(hb_ShaderProgram* program) {
  glLinkProgram(program->glId);

  int success;
  glGetProgramiv(program->glId, GL_LINK_STATUS, &success);
  if (!success) {
    char errorMessage[512];
    glGetProgramInfoLog(program->glId, 512, NULL, errorMessage);
    hb_error(errorMessage);
  }
}

hb_ShaderProgram hb_createAndLinkShaderProgram(hb_Shader* vert, hb_Shader* frag) {
  hb_ShaderProgram program = hb_createShaderProgram();
  hb_addShaderToProgram(&program, vert);
  hb_addShaderToProgram(&program, frag);
  hb_linkProgram(&program);
  return program;
}

hb_ShaderProgram hb_createShaderProgramFromSources(
    const char* vertSource, const char* fragSource) {
  hb_Shader* vertex = hb_createAndCompileShader(vertSource, hb_SHADER_TYPE_VERTEX);
  hb_Shader* fragment = hb_createAndCompileShader(fragSource, hb_SHADER_TYPE_FRAGMENT);
  return hb_createAndLinkShaderProgram(vertex, fragment);
}

hb_ShaderProgram hb_loadShaderProgram(
    const char* vertPath, const char* fragPath) {
  hb_Shader* vertex = hb_loadAndCompileShader(vertPath, hb_SHADER_TYPE_VERTEX);
  hb_Shader* fragment = hb_loadAndCompileShader(fragPath, hb_SHADER_TYPE_FRAGMENT);
  return hb_createAndLinkShaderProgram(vertex, fragment);
}

void hb_destroyShaderProgram(hb_ShaderProgram* program) {
  glDeleteProgram(program->glId);
  hb_destroyShader(program->vertex);
  hb_destroyShader(program->fragment);
}

void hb_useShaderProgram(hb_ShaderProgram* program) {
  glUseProgram(program->glId);
}

void hb_setShaderProgramFloat(hb_ShaderProgram* program, const char* name, f32 value) {
  glUniform1f(glGetUniformLocation(program->glId, name), value);
}

void hb_setShaderProgramVec2(hb_ShaderProgram* program, const char* name, vec2 value) {
  glUniform2f(glGetUniformLocation(program->glId, name), value[0], value[1]);
}

void hb_setShaderProgramVec3(hb_ShaderProgram* program, const char* name, vec3 value) {
  glUniform3f(glGetUniformLocation(program->glId, name), value[0], value[1], value[3]);
}

void hb_setShaderProgramVec4(hb_ShaderProgram* program, const char* name, vec4 value) {
  glUniform4f(glGetUniformLocation(program->glId, name), value[0], value[1], value[3], value[4]);
}

void hb_setShaderProgramMat4(hb_ShaderProgram* program, const char* name, mat4x4 value) {
  glUniformMatrix4fv(glGetUniformLocation(program->glId, name),
                     1, GL_FALSE, *value);
}
