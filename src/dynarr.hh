#ifndef _HOBBY_DYNARR_HH
#define _HOBBY_DYNARR_HH

#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "log.hh"

#define DYN_ARR_GROW 2
#define DYN_ARR_SMALLEST 8

template <typename T>
class DynArr
{
public:
  DynArr()
  {
    _resize(DYN_ARR_SMALLEST);
  }

  DynArr(const DynArr<T>& arr)
  {
    arr.copy(*this);
  }

  ~DynArr()
  {
    _resize(0);
  }

  inline void reserve(size_t size)
  {
    if (_capacity >= size) {
      return;
    }
    _resize(size);
  }

  inline void pushback(const T& e)
  {
    if (_count + 1 > _capacity) {
      _resize(_capacity * DYN_ARR_GROW);
    }
    _d[_count++] = e;
  }

  inline void pushfront(const T& e)
  {
    insert(0, e);
  }

  void insert(size_t index, const T& e)
  {
    if (_count + 1 > _capacity) {
      _resize(_capacity * DYN_ARR_GROW);
    }

    for (int i = _count; i > index; i--) {
      _d[i] = _d[i - 1];
    }

    _d[index] = e;
    _count++;
  }

  inline void clear()
  {
    free(_d);
    _d = nullptr;
    _count = 0;
    _resize(DYN_ARR_SMALLEST);
  }

  inline void copy(DynArr<T>& dest) const
  {
    dest._resize(_capacity);
    dest._count = _count;
    memcpy(dest._d, _d, sizeof(T) * _count);
  }

  void remove(size_t index)
  {
    for (int i = index; i < _count - 1; i++) {
      _d[i] = _d[i + 1];
    }
    _count--;
  }

  inline void swapremove(size_t index)
  {
    _d[index] = _d[_count--];
  }

  T& popback()
  {
    return _d[_count--];
  }

  inline T& operator[](size_t index) const;

  inline int capacity() const
  {
    return _capacity;
  }

  inline int size() const
  {
    return _count;
  }

  inline T* data() const
  {
    return _d;
  }

private:
  void _resize(size_t size)
  {
    if (size == 0) {
      free(_d);
      _d = nullptr;
      return;
    }

    _d = (T*)realloc(_d, sizeof(T) * size);
    _capacity = size;
  }

  T* _d = nullptr;
  size_t _count = 0, _capacity = 0;
};

template <typename T>
T& DynArr<T>::operator[](size_t index) const
{
#ifdef HB_DEBUG
  if (index >= _count || index < 0) {
    return fatal("Index '%d' out of bounds (Size %d).", index, _count);
  }
#endif

  return _d[index];
}

#endif // _HOBBY_DYNARR_HH
