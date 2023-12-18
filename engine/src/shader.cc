#include "shader.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "glad/glad.h"

namespace point {

static unsigned int CreateShader(unsigned int type, const char *source, std::string path) {
  unsigned int shader;
  shader = glCreateShader(type);
  glShaderSource(shader, 1, &source, NULL);
  glCompileShader(shader);

  int success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    char infoLog[512];
    glGetShaderInfoLog(shader, 512, NULL, infoLog);
    if (type == GL_VERTEX_SHADER) {
      std::cout << "Vertex shader failed to compile (" << path << "):\n";
    } else {
      std::cout << "Fragment shader failed to compile (" << path << "):\n";
    }
    std::cout << infoLog << std::endl;

    std::exit(1);
  }

  return shader;
}

static unsigned int CreateShaderProgram(unsigned int vert, unsigned int frag) {
  unsigned int program;
  program = glCreateProgram();

  glAttachShader(program, vert);
  glAttachShader(program, frag);
  glLinkProgram(program);

  int success;
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    char infoLog[512];
    glGetProgramInfoLog(program, 512, NULL, infoLog);

    std::cout << "Failed to link shaders:\n" << infoLog << std::endl;
    exit(1);
  }

  return program;
}

static std::string ReadFile(const char* path) {
  std::string source;
  std::ifstream file;

  file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  try {
    file.open(path);

    std::stringstream fileStream;

    fileStream << file.rdbuf();

    file.close();

    source = fileStream.str();
  } catch(std::ifstream::failure e) {
    std::cerr << "Could not load shader." << std::endl;
  }

  return source;
}

Shader::Shader(const char* vertPath, const char* fragPath) {
  _vert = CreateShader(GL_VERTEX_SHADER, ReadFile(vertPath).c_str(), vertPath);
  _frag = CreateShader(GL_FRAGMENT_SHADER, ReadFile(fragPath).c_str(), fragPath);
  _id = CreateShaderProgram(_vert, _frag);
}

void Shader::Apply() {
  glUseProgram(_id);
}

#define SET_UNIFORM(func) \
  func(glGetUniformLocation(_id, name.c_str()), value)

void Shader::SetBool(const std::string& name, bool value) const {
  SET_UNIFORM(glUniform1i);
}

void Shader::SetInt(const std::string& name, int value) const {
  SET_UNIFORM(glUniform1i);
}

void Shader::SetFloat(const std::string& name, float value) const {
  SET_UNIFORM(glUniform1f);
}

#undef SET_UNIFORM

}
