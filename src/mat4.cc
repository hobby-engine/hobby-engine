#include "mat4.hh"

// A lot of this implementation had Love2D used a reference.
// https://github.com/love2d/love/blob/64a30f177fd182cfd34735df8e82e0239a0f330e/src/common/Matrix.cpp

#include <cmath>
#include <cstring>

Mat4::Mat4()
{
  setidentity();
}

void Mat4::setidentity()
{
  memset(m_e, 0, sizeof(float) * 16);
  m_e[0] = 1;
  m_e[5] = 1;
  m_e[10] = 1;
  m_e[15] = 1;
}

void Mat4::settranslation(float x, float y)
{
  setidentity();
  m_e[12] = x;
  m_e[13] = y;
}

void Mat4::setscale(float x, float y)
{
  setidentity();
  m_e[0] = x;
  m_e[5] = y;
}

void Mat4::setskew(float x, float y)
{
  setidentity();
  m_e[1] = x;
  m_e[4] = y;
}

void Mat4::setrotation(float r)
{
  setidentity();
  float c = cosf(r);
  float s = sinf(r);
  m_e[0] = c;
  m_e[4] = -s;
  m_e[1] = s;
  m_e[5] = c;
}

void Mat4::translate(float x, float y)
{
  Mat4 translation;
  translation.settranslation(x, y);
  multiply(translation, m_e);
}

void Mat4::scale(float x, float y)
{
  Mat4 scale;
  scale.setscale(x, y);
  multiply(scale, m_e);
}

void Mat4::rotate(float r)
{
  Mat4 rotation;
  rotation.setrotation(r);
  multiply(rotation, m_e);
}

void Mat4::skew(float x, float y)
{
  Mat4 skew;
  skew.setskew(x, y);
  multiply(skew, m_e);
}

void Mat4::multiply(const Mat4& o, float t[16]) const
{
  /*
   * 1 0 0 0
   * 0 1 0 0
   * 0 0 1 0
   * 0 0 0 1
   */

  // clang-format off
  t[0]  = (m_e[0]  * o.m_e[0]) + (m_e[1]  * o.m_e[4]) + (m_e[2]  * o.m_e[8])  + (m_e[3]  * o.m_e[12]);
  t[1]  = (m_e[0]  * o.m_e[1]) + (m_e[1]  * o.m_e[5]) + (m_e[2]  * o.m_e[9])  + (m_e[3]  * o.m_e[13]);
  t[2]  = (m_e[0]  * o.m_e[2]) + (m_e[1]  * o.m_e[6]) + (m_e[2]  * o.m_e[10]) + (m_e[3]  * o.m_e[14]);
  t[3]  = (m_e[0]  * o.m_e[3]) + (m_e[1]  * o.m_e[7]) + (m_e[2]  * o.m_e[11]) + (m_e[3]  * o.m_e[15]);
  t[4]  = (m_e[4]  * o.m_e[0]) + (m_e[5]  * o.m_e[4]) + (m_e[6]  * o.m_e[8])  + (m_e[7]  * o.m_e[12]);
  t[5]  = (m_e[4]  * o.m_e[1]) + (m_e[5]  * o.m_e[5]) + (m_e[6]  * o.m_e[9])  + (m_e[7]  * o.m_e[13]);
  t[6]  = (m_e[4]  * o.m_e[2]) + (m_e[5]  * o.m_e[6]) + (m_e[6]  * o.m_e[10]) + (m_e[7]  * o.m_e[14]);
  t[7]  = (m_e[4]  * o.m_e[3]) + (m_e[5]  * o.m_e[7]) + (m_e[6]  * o.m_e[11]) + (m_e[7]  * o.m_e[15]);
  t[8]  = (m_e[8]  * o.m_e[0]) + (m_e[9]  * o.m_e[4]) + (m_e[10] * o.m_e[8])  + (m_e[11] * o.m_e[12]);
  t[9]  = (m_e[8]  * o.m_e[1]) + (m_e[9]  * o.m_e[5]) + (m_e[10] * o.m_e[9])  + (m_e[11] * o.m_e[13]);
  t[10] = (m_e[8]  * o.m_e[2]) + (m_e[9]  * o.m_e[6]) + (m_e[10] * o.m_e[10]) + (m_e[11] * o.m_e[14]);
  t[11] = (m_e[8]  * o.m_e[3]) + (m_e[9]  * o.m_e[7]) + (m_e[10] * o.m_e[11]) + (m_e[11] * o.m_e[15]);
  t[12] = (m_e[12] * o.m_e[0]) + (m_e[13] * o.m_e[4]) + (m_e[14] * o.m_e[8])  + (m_e[15] * o.m_e[12]);
  t[13] = (m_e[12] * o.m_e[1]) + (m_e[13] * o.m_e[5]) + (m_e[14] * o.m_e[9])  + (m_e[15] * o.m_e[13]);
  t[14] = (m_e[12] * o.m_e[2]) + (m_e[13] * o.m_e[6]) + (m_e[14] * o.m_e[10]) + (m_e[15] * o.m_e[14]);
  t[15] = (m_e[12] * o.m_e[3]) + (m_e[13] * o.m_e[7]) + (m_e[14] * o.m_e[11]) + (m_e[15] * o.m_e[15]);
  // clang-format on
}

void Mat4::multiply(const Mat4& o, Mat4& t) const
{
  multiply(o, t.m_e);
}

void Mat4::ortho(float l, float r, float b, float t, float n, float f)
{
  m_e[0] = 2.0f / (r - l);
  m_e[5] = 2.0f / (t - b);
  m_e[10] = -2.0f / (f - n);

  m_e[12] = -(r + l) / (r - l);
  m_e[13] = -(t + b) / (t - b);
  m_e[14] = -(f + n) / (f - n);
}

void Mat4::applytransform(float* x, float* y)
{
  float cx = *x, cy = *y;
  *x = (m_e[0] * cx) + (m_e[4] * cy) + (m_e[12]);
  *y = (m_e[1] * cx) + (m_e[5] * cy) + (m_e[13]);
}
