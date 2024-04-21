#ifndef _HOBBY_SHADER_HH
#define _HOBBY_SHADER_HH

#include "mat4.hh"
#include "renderer.hh"
#include "common.hh"

enum class ShaderType {
  Vertex,
  Fragment,
};

class Shader {
  public:
    Shader(UNUSED const char* vertPath, UNUSED const char* fragPath) {}
    virtual ~Shader() {}
    
    virtual void apply() = 0;
    
    virtual void sendFloat(const char* name, float value) = 0;
    virtual void sendMat4(const char* name, const Mat4& value) = 0;
    virtual void sendColor(const char* name, Color value) = 0;
  private:
};

#endif // _HOBBY_SHADER_HH
