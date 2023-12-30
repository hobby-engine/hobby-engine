#include "shader.hh"

#include "glad/glad.h"
#include <iostream>

namespace Hobby {

Shader::Shader(const char* vertexSource, const char* fragmentSource) {
  _vertexId = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(_vertexId, 1, &vertexSource, nullptr);
  glCompileShader(_vertexId);

  int compileRes;
  glGetShaderiv(_vertexId, GL_COMPILE_STATUS, &compileRes);
  if(!compileRes) {
    char error[512];
    glGetShaderInfoLog(_vertexId, 512, NULL, error);
    std::cout << "Vertex shader error: " << error << std::endl;
    exit(1);
  };

  _fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(_fragmentId, 1, &fragmentSource, nullptr);
  glCompileShader(_fragmentId);

  glGetShaderiv(_fragmentId, GL_COMPILE_STATUS, &compileRes);
  if(!compileRes) {
    char error[512];
    glGetShaderInfoLog(_fragmentId, 512, NULL, error);
    std::cout << "Fragment shader error: " << error << std::endl;
    exit(1);
  };

  _shaderId = glCreateProgram();
  glAttachShader(_shaderId, _vertexId);
  glAttachShader(_shaderId, _fragmentId);
  glLinkProgram(_shaderId);

  glGetProgramiv(_vertexId, GL_LINK_STATUS, &compileRes);
  if(!compileRes) {
    char error[512];
    glGetShaderInfoLog(_vertexId, 512, NULL, error);
    std::cout << "Linking shader error: " << error << std::endl;
    exit(1);
  };
}

void Shader::Apply() {
  glUseProgram(_shaderId);
}

} // namespace Hobby
