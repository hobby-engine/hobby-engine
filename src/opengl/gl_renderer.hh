#ifndef _HOBBY_GL_RENDERER_HH
#define _HOBBY_GL_RENDERER_HH

#include "gl_shader.hh"
#include "opengl/vertex.hh"
#include "renderer.hh"

class OpenGlRenderer final : public Renderer
{
public:
  OpenGlRenderer(Window* window);

  void clear(Color color) override;
  void draw() override;
  void drawIndexed() override;

private:
  void _setAttributes();
  GLenum _getGlIndexMode(IndexMode mode);

  VertexBuffer _vbo;
  VertexBuffer _ibo;
  VertexArray _vao;
  OpenGlShader _colorShader;
  OpenGlShader _textureShader;
};

#endif // _HOBBY_GL_RENDERER_HH
