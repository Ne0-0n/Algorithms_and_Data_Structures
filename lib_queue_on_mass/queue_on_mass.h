// Copyright 2026 Kutyaev Egor
#ifndef LIB_QUEUE_ON_MASS_QUEUE_ON_MASS_H_
#define LIB_QUEUE_ON_MASS_QUEUE_ON_MASS_H_

#include <cstddef>
#include <stdexcept>

template <class T>
class TQueueOnMass {
  T* _data;
  size_t _size;
  int _head;
  int _count;

 public:
  explicit TQueueOnMass(size_t size);
  TQueueOnMass(const TQueueOnMass& other);
  TQueueOnMass& operator=(const TQueueOnMass& other);
  ~TQueueOnMass();

  bool is_empty() const noexcept;
  bool is_full() const noexcept;
  size_t size() const noexcept;

  void push(const T& val);
  T pop();
  T& front();
  T& back();
};

#endif  // LIB_QUEUE_ON_MASS_QUEUE_ON_MASS_H_