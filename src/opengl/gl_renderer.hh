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
  void m_setattribs();
  GLenum m_getglindexmode(IndexMode mode);
  void m_setupshader(const Mat4& transform);

  Mat4 m_projection;

  OpenGlTexture2D* m_coltex = nullptr;

  VertexFormat m_currentformat;

  VertexBuffer m_vbo;
  VertexBuffer m_ibo;
  VertexArray m_vao;
  OpenGlShader m_defaultshader;
};

#endif // _HOBBY_GL_RENDERER_HH
