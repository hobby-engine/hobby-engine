#ifndef _HOBBY_GL_RENDERER_HH
#define _HOBBY_GL_RENDERER_HH

#include "mat4.hh"
#include "renderer.hh"
#include "gl_shader.hh"
#include "glfw/glfw_window.hh"
#include "vertex.hh"

class OpenGlRenderer final : public Renderer {
  public:
    OpenGlRenderer(GlfwWindow* window);

    void update() override;
    void setColor(Color color) override;
    void clear(Color color) override;
    void drawRect(float x, float y, float w, float h) override;
    void drawEllipse(float x, float y, float rx, float ry) override;
    void drawVertices(int count, float* vertices) override;
    void drawBoid(float x, float y, float b, float h, float r) override;
    void draw(
        const Texture2D& texture,
        float x, float y,
        float r,
        float sx, float sy,
        float ox, float oy) override;
  private:
    GlfwWindow* _window;

    VertexBuffer _vertexBuffer;
    VertexBuffer _indexBuffer;
    VertexArray _vertexArray;

    OpenGlShader _colorShader;
    OpenGlShader _textureShader;

    Mat4 _projection;
};

#endif // _HOBBY_GL_RENDERER_HH
