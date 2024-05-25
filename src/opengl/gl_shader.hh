#ifndef _HOBBY_OPENGL_SHADER_HH
#define _HOBBY_OPENGL_SHADER_HH

#include "shader.hh"

class OpenGlShader final : public Shader
{
public:
  OpenGlShader(const char* vertPath, const char* fragPath);
  OpenGlShader(unsigned int handle);
  ~OpenGlShader();

  unsigned int handle;

  static OpenGlShader embedded(const char* vertSource, const char* fragSource);

  void apply() override;

  void sendFloat(const char* name, float value) override;
  void sendInt(const char* name, int value) override;
  void sendMat4(const char* name, const Mat4& value) override;
  void sendColor(const char* name, Color value) override;

private:
};

#endif // _HOBBY_OPENGL_SHADER_HH
