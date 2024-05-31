#ifndef _HOBBY_MAT4_HH
#define _HOBBY_MAT4_HH

struct Mat4
{
public:
  Mat4();

  void setidentity();
  void settranslation(float x, float y);
  void setscale(float x, float y);
  void setrotation(float r);
  void setskew(float x, float y);
  void translate(float x, float y);
  void scale(float x, float y);
  void rotate(float r);
  void skew(float x, float y);
  void multiply(const Mat4& o, float t[16]) const;
  void multiply(const Mat4& o, Mat4& t) const;
  void ortho(float l, float r, float b, float t, float n, float f);
  void applytransform(float* x, float* y);

  inline const float* data() const
  {
    return e;
  }

private:
  float e[16];
};

#endif // _HOBBY_MAT4_HH
