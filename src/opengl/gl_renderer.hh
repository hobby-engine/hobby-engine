#ifndef _HOBBY_GL_RENDERER_HH
#define _HOBBY_GL_RENDERER_HH

#include "gl_shader.hh"
#include "opengl/gl_texture.hh"
#include "opengl/vertex.hh"
#include "renderer.hh"

class OpenGlRenderer final : public Renderer
{
public:
  OpenGlRenderer(Window* window);
  ~OpenGlRenderer();

  static void initOpenGl();

  void clear(Color color) override;
  void draw() override;
  void drawIndexed() override;
  void resizeWindow(Window* window) override;

private:
  void _setAttributes();
  GLenum _getGlIndexMode(IndexMode mode);
  void _setupShaderForDraw(const Mat4& transform);

  Mat4 _projection;

  OpenGlTexture2D* _colorTexture = nullptr;

  VertexFormat _currentFormat;

  VertexBuffer _vbo;
  VertexBuffer _ibo;
  VertexArray _vao;
  OpenGlShader _defaultShader;
};

#endif // _HOBBY_GL_RENDERER_HH
