#include "mat4.hh"

// A lot of this implementation had Love2D used a reference.
// https://github.com/love2d/love/blob/64a30f177fd182cfd34735df8e82e0239a0f330e/src/common/Matrix.cpp

#include <cmath>
#include <cstring>

Mat4::Mat4() {
  setIdentity();
}

void Mat4::setIdentity() {
  memset(e, 0, sizeof(float) * 16);
  e[0] = 1;
  e[5] = 1;
  e[10] = 1;
  e[15] = 1;
}

void Mat4::setTranslation(float x, float y) {
  setIdentity();
  e[12] = x;
  e[13] = y;
}

void Mat4::setScale(float x, float y) {
  setIdentity();
  e[0] = x;
  e[5] = y;
}

void Mat4::setSkew(float x, float y) {
  setIdentity();
  e[1] = x;
  e[4] = y;
}

void Mat4::setRotation(float r) {
  setIdentity();
  float c = cosf(r);
  float s = sinf(r);
	e[0] = c; e[4] = -s;
	e[1] = s; e[5] = c;
}

void Mat4::translate(float x, float y) {
  Mat4 translation;
  translation.setTranslation(x, y);
  multiply(translation, e);
}

void Mat4::scale(float x, float y) {
  Mat4 scale;
  scale.setScale(x, y);
  multiply(scale, e);
}

void Mat4::rotate(float r) {
  Mat4 rotation;
  rotation.setRotation(r);
  multiply(rotation, e);
}

void Mat4::skew(float x, float y) {
  Mat4 skew;
  skew.setSkew(x, y);
  multiply(skew, e);
}

void Mat4::multiply(const Mat4& o, float t[16]) const {
  /*
   * 1 0 0 0
   * 0 1 0 0
   * 0 0 1 0
   * 0 0 0 1
  */
  t[0]  = (e[0] * o.e[0])  + (e[1] * o.e[4])  + (e[2] * o.e[8])   + (e[3] * o.e[12]);
  t[1]  = (e[0] * o.e[1])  + (e[1] * o.e[5])  + (e[2] * o.e[9])   + (e[3] * o.e[13]);
  t[2]  = (e[0] * o.e[2])  + (e[1] * o.e[6])  + (e[2] * o.e[10])  + (e[3] * o.e[14]);
  t[3]  = (e[0] * o.e[3])  + (e[1] * o.e[7])  + (e[2] * o.e[11])  + (e[3] * o.e[15]);
 
  t[4]  = (e[4] * o.e[0])  + (e[5] * o.e[4])  + (e[6] * o.e[8])   + (e[7] * o.e[12]);
  t[5]  = (e[4] * o.e[1])  + (e[5] * o.e[5])  + (e[6] * o.e[9])   + (e[7] * o.e[13]);
  t[6]  = (e[4] * o.e[2])  + (e[5] * o.e[6])  + (e[6] * o.e[10])  + (e[7] * o.e[14]);
  t[7]  = (e[4] * o.e[3])  + (e[5] * o.e[7])  + (e[6] * o.e[11])  + (e[7] * o.e[15]);
 
  t[8]  = (e[8] * o.e[0])  + (e[9] * o.e[4])  + (e[10] * o.e[8])  + (e[11] * o.e[12]);
  t[9]  = (e[8] * o.e[1])  + (e[9] * o.e[5])  + (e[10] * o.e[9])  + (e[11] * o.e[13]);
  t[10] = (e[8] * o.e[2])  + (e[9] * o.e[6])  + (e[10] * o.e[10]) + (e[11] * o.e[14]);
  t[11] = (e[8] * o.e[3])  + (e[9] * o.e[7])  + (e[10] * o.e[11]) + (e[11] * o.e[15]);
 
  t[12] = (e[12] * o.e[0]) + (e[13] * o.e[4]) + (e[14] * o.e[8])  + (e[15] * o.e[12]);
  t[13] = (e[12] * o.e[1]) + (e[13] * o.e[5]) + (e[14] * o.e[9])  + (e[15] * o.e[13]);
  t[14] = (e[12] * o.e[2]) + (e[13] * o.e[6]) + (e[14] * o.e[10]) + (e[15] * o.e[14]);
  t[15] = (e[12] * o.e[3]) + (e[13] * o.e[7]) + (e[14] * o.e[11]) + (e[15] * o.e[15]);
}

void Mat4::multiply(const Mat4& o, Mat4& t) const {
  multiply(o, t.e);
}

void Mat4::ortho(float l, float r, float b, float t, float n, float f) {
  e[0] = 2.0f / (r - l);
	e[5] = 2.0f / (t - b);
	e[10] = -2.0f / (f - n);

	e[12] = -(r + l) / (r - l);
	e[13] = -(t + b) / (t - b);
	e[14] = -(f + n) / (f - n);
}
