#ifndef _HOBBY_TEXTURE_HH
#define _HOBBY_TEXTURE_HH

enum class FilterMode
{
  Nearest,
  Linear,
};

enum class WrapMode
{
  None,
  Repeat,
  MirroredRepeat,
  Clamp,
};

class Texture
{
public:
  virtual ~Texture();

  virtual int getwidth() const = 0;
  virtual int getheight() const = 0;
  virtual int getchannels() const = 0;

private:
};

class Texture2D : public Texture
{
public:
  virtual void bind() const = 0;
};

#endif // _HOBBY_TEXTURE_HH
