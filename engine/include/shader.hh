#ifndef _POINT_ENGINE_SHADER_H
#define _POINT_ENGINE_SHADER_H

#include <string>

namespace point {

class Shader {
  public:
    Shader(const char* vertexPath, const char* fragmentPath);
    
    void Apply();
    void SetBool(const std::string& name, bool value) const;
    void SetInt(const std::string& name, int value) const;
    void SetFloat(const std::string& name, float value) const;
  private:
    unsigned int _vert;
    unsigned int _frag;
    unsigned int _id;
};

} // namespace point

#endif // _POINT_ENGINE_SHADER_H
