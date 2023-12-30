#ifndef _HOBBY_SHADER_H
#define _HOBBY_SHADER_H

namespace Hobby {

class Shader {
public:
  Shader(const char* vertexSource, const char* fragmentSource);

  void Apply();
  
private:
  unsigned int _vertexId, _fragmentId, _shaderId;
};

} // namespace Hobby

#endif // _HOBBY_SHADER_H
