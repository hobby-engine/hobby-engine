#include "gl_renderer.hh"

#include "glfw/glfw_window.hh"
#include "mesh.hh"
#include "opengl/vertex.hh"
#include "renderer.hh"

#include "glad/glad.h"

#include "common.hh"
#include "log.hh"

// TEXTURE SHADER

const char* defaultvert = R"glsl(
#version 330 core

in vec2 ipos;
in vec2 iuv;
in vec4 icolor;

uniform mat4 proj, trans;

out vec2 v_uv;
out vec4 v_color;

void main() {
  gl_Position = proj * trans * vec4(ipos, 0., 1.);

  v_uv = iuv;
  v_color = icolor;
}
)glsl";

const char* defaultfrag = R"glsl(
#version 330 core

out vec4 fragcolor;

in vec2 v_uv;
in vec4 v_color;

uniform sampler2D tex;

void main() {
  fragcolor = texture(tex, v_uv) * v_color;
}
)glsl";

void openGlMessage(
  UNUSED unsigned source, UNUSED unsigned type, UNUSED unsigned id,
  unsigned severity, UNUSED int length, const char* message,
  UNUSED const void* userParam)
{
  switch (severity) {
    case GL_DEBUG_SEVERITY_HIGH:
    case GL_DEBUG_SEVERITY_MEDIUM:
      Logger::instance()->error("OpenGL: %s", message);
      return;
    case GL_DEBUG_SEVERITY_LOW:
      Logger::instance()->warn("OpenGL: %s", message);
      return;
    case GL_DEBUG_SEVERITY_NOTIFICATION:
      Logger::instance()->log("OpenGL: %s", message);
      return;
  }

  Logger::instance()->error("Unknown severity level!");
}

OpenGlRenderer::OpenGlRenderer(Window* window)
    : Renderer(window), m_currentformat(VertexFormat::XY),
      m_vbo(VertexBuffer(VertexBufferType::Array, false)),
      m_ibo(VertexBuffer(VertexBufferType::Index, false)), m_vao(VertexArray()),
      m_defaultshader(OpenGlShader::embedded(defaultvert, defaultfrag))
{
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

#ifdef HB_DEBUG
  Logger::instance()->log("OpenGL debug enabled.");
  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback(openGlMessage, nullptr);
#endif

  m_defaultshader.apply();

  m_coltex = new OpenGlTexture2D({1.0, 1.0, 1.0, 1.0});

  resizewindow(window);
}

OpenGlRenderer::~OpenGlRenderer()
{
  delete m_coltex;
}

void OpenGlRenderer::initopengl()
{
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    glfwTerminate();
    Logger::instance()->fatal("Failed to initialize glad.");
  }
}

void OpenGlRenderer::resizewindow(Window* window)
{
  int w, h;
  window->getsize(w, h);

  m_projection.setidentity();
  m_projection.ortho(0, w, h, 0, -1, 1);

  window->makecurrent();
  glViewport(0, 0, w, h);
}

void OpenGlRenderer::clear(Color color)
{
  glClearColor(color.r, color.g, color.b, color.a);
  glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGlRenderer::m_setattribs()
{
  VertexFormat format = m_currentformat;
  if (m_state) {
    format = m_state->mesh.getformat();
    // Nothing changed, this is a waste of our time
    if (format == m_currentformat) {
      return;
    }
  }

  size_t stride = getvertformatstride(format);

  switch (format) {
    case VertexFormat::XY:
      m_vao.setattrib(m_vbo, 0, 2, GL_FLOAT, stride, 0);
      break;
    case VertexFormat::XYU:
      m_vao.setattrib(m_vbo, 0, 2, GL_FLOAT, stride, 0);
      m_vao.setattrib(m_vbo, 1, 2, GL_FLOAT, stride, 2 * sizeof(float));
      break;
    case VertexFormat::XYC:
      m_vao.setattrib(m_vbo, 0, 2, GL_FLOAT, stride, 0);
      m_vao.setattrib(m_vbo, 1, 4, GL_FLOAT, stride, 2 * sizeof(float));
      break;
    case VertexFormat::XYUC:
      m_vao.setattrib(m_vbo, 0, 2, GL_FLOAT, stride, 0);
      m_vao.setattrib(m_vbo, 1, 2, GL_FLOAT, stride, 2 * sizeof(float));
      m_vao.setattrib(m_vbo, 2, 4, GL_FLOAT, stride, 4 * sizeof(float));
      break;
    default:
      return;
  }
}

GLenum OpenGlRenderer::m_getglindexmode(IndexMode mode)
{
  switch (mode) {
    case IndexMode::Triangles:
      return GL_TRIANGLES;
    case IndexMode::TriangleFan:
      return GL_TRIANGLE_FAN;
    case IndexMode::TriangleStripe:
      return GL_TRIANGLE_STRIP;
  }

  // Unreachable.
  return GL_TRIANGLES;
}

void OpenGlRenderer::m_setupshader(const Mat4& transform)
{
  glActiveTexture(GL_TEXTURE0);
  m_coltex->bind();

  m_defaultshader.apply();

  if (m_state->texture) {
    m_state->texture->bind();
  }
  m_defaultshader.sendint("tex", 0);
  m_defaultshader.sendmat4("proj", m_projection);
  m_defaultshader.sendmat4("trans", transform);
}

void OpenGlRenderer::draw()
{
  float* vertices = m_state->mesh.data();

  int vertexlen = getverformatlen(m_state->mesh.getformat());
  int meshlen = m_state->mesh.vertexcount();

  m_vbo.setdata(meshlen * sizeof(float), vertices);
  m_setattribs();

  Mat4 transform;
  transform.setidentity();

  m_setupshader(transform);

  m_vao.bind();

  int elementc = meshlen / vertexlen;
  glDrawArrays(m_getglindexmode(m_state->indexmode), 0, elementc);
}

void OpenGlRenderer::drawindexed()
{
  float* vertices = m_state->mesh.data();
  unsigned int* indices = m_state->mesh.indices();

  int vertexcount = m_state->mesh.vertexcount();
  int indexcount = m_state->mesh.indexcount();

  m_vbo.setdata(vertexcount * sizeof(float), vertices);
  m_ibo.setdata(indexcount * sizeof(uint32_t), indices);
  m_setattribs();

  Mat4 transform;
  transform.setidentity();

  m_setupshader(transform);

  m_ibo.bind();

  GLenum indexmode = m_getglindexmode(m_state->indexmode);
  glDrawElements(indexmode, indexcount, GL_UNSIGNED_INT, nullptr);
}
