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

  static void initopengl();

  void clear(Color color) override;
  void draw() override;
  void drawindexed() override;
  void resizewindow(Window* window) override;

private:
  void _setattribs();
  GLenum _getglindexmode(IndexMode mode);
  void _setupshader(const Mat4& transform);

  Mat4 _projection;

  OpenGlTexture2D* _coltex = nullptr;

  VertexFormat _currentformat;

  VertexBuffer _vbo;
  VertexBuffer _ibo;
  VertexArray _vao;
  OpenGlShader _defaultshader;
};

#endif // _HOBBY_GL_RENDERER_HH
