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
    m_resize(DYN_ARR_SMALLEST);
  }

  DynArr(const DynArr<T>& arr)
  {
    arr.copy(*this);
  }

  ~DynArr()
  {
    m_resize(0);
  }

  inline void reserve(size_t size)
  {
    if (m_capacity >= size) {
      return;
    }
    m_resize(size);
  }

  inline void pushback(const T& e)
  {
    if (m_count + 1 > m_capacity) {
      m_resize(m_capacity * DYN_ARR_GROW);
    }
    m_d[m_count++] = e;
  }

  inline void pushfront(const T& e)
  {
    insert(0, e);
  }

  void insert(size_t index, const T& e)
  {
    if (m_count + 1 > m_capacity) {
      m_resize(m_capacity * DYN_ARR_GROW);
    }

    for (int i = m_count; i > index; i--) {
      m_d[i] = m_d[i - 1];
    }

    m_d[index] = e;
    m_count++;
  }

  inline void clear()
  {
    free(m_d);
    m_d = nullptr;
    m_count = 0;
    m_resize(DYN_ARR_SMALLEST);
  }

  inline void copy(DynArr<T>& dest) const
  {
    dest.m_resize(m_capacity);
    dest.m_count = m_count;
    memcpy(dest.m_d, m_d, sizeof(T) * m_count);
  }

  void remove(size_t index)
  {
    for (int i = index; i < m_count - 1; i++) {
      m_d[i] = m_d[i + 1];
    }
    m_count--;
  }

  inline void swapremove(size_t index)
  {
    m_d[index] = m_d[m_count--];
  }

  T& popback()
  {
    return m_d[m_count--];
  }

  inline T& operator[](size_t index) const;

  inline int capacity() const
  {
    return m_capacity;
  }

  inline int size() const
  {
    return m_count;
  }

  inline T* data() const
  {
    return m_d;
  }

private:
  void m_resize(size_t size)
  {
    if (size == 0) {
      free(m_d);
      m_d = nullptr;
      return;
    }

    m_d = (T*)realloc(m_d, sizeof(T) * size);
    m_capacity = size;
  }

  T* m_d = nullptr;
  size_t m_count = 0;
  size_t m_capacity = 0;
};

template <typename T>
T& DynArr<T>::operator[](size_t index) const
{
#ifdef HB_DEBUG
  if (index >= m_count || index < 0) {
    return Logger::instance()->fatal(
      "Index '%d' out of bounds (Size %d).", index, m_count);
  }
#endif

  return m_d[index];
}

#endif // _HOBBY_DYNARR_HH
