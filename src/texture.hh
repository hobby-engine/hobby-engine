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
  virtual ~Texture()
  {
  }

  virtual int getWidth() const = 0;
  virtual int getHeight() const = 0;
  virtual int getChannelCount() const = 0;

private:
};

class Texture2D : public Texture
{
public:
  virtual void bind() const = 0;
};

#endif // _HOBBY_TEXTURE_HH
