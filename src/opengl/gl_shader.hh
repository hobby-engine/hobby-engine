#ifndef _HOBBY_OPENGL_SHADER_HH
#define _HOBBY_OPENGL_SHADER_HH

#include "shader.hh"

class OpenGlShader final : public Shader
{
public:
  OpenGlShader(const char* vertpath, const char* fragpath);
  OpenGlShader(unsigned int handle);
  ~OpenGlShader();

  unsigned int handle;

  static OpenGlShader embedded(const char* vertsource, const char* fragsource);

  void apply() override;

  void sendfloat(const char* name, float value) override;
  void sendint(const char* name, int value) override;
  void sendmat4(const char* name, const Mat4& value) override;
  void sendcolor(const char* name, Color value) override;

private:
};

#endif // _HOBBY_OPENGL_SHADER_HH
