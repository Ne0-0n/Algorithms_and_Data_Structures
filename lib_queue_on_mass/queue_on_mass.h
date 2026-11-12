// Copyright 2026 Kutyaev Egor
#include <stdexcept>

#ifndef LIB_QUEUE_ON_MASS_QUEUE_ON_MASS_H_
#define LIB_QUEUE_ON_MASS_QUEUE_ON_MASS_H_


template <class T>
class TQueueOnMass {
  T* _data;
  size_t _size;
  int _head;
  int _count;

 public:
  explicit TQueueOnMass(size_t size) {
    if (size == 0) {
      throw std::invalid_argument{"ERROR: Queue size must be > 0"};
    }
    _data = new T[size];
    _size = size;
    _head = 0;
    _count = 0;
  }

  TQueueOnMass(const TQueueOnMass& other) {
    _data = new T[other._size];
    _size = other._size;
    _head = 0;
    _count = other._count;
    for (size_t i = 0; i < _count; ++i) {
      _data[i] = other._data[(other._head + i) % other._size];
    }
  }

  TQueueOnMass& operator=(const TQueueOnMass& other) {
    if (this == &other) {
      return *this;
    }
    T* new_data = new T[other._size];
    for (size_t i = 0; i < other._count; ++i) {
      new_data[i] = other._data[(other._head + i) % other._size];
    }
    delete[] _data;
    _data = new_data;
    _size = other._size;
    _head = 0;
    _count = other._count;
    return *this;
  }

  ~TQueueOnMass() { delete[] _data; }

  inline bool is_empty() const noexcept { return _count == 0; }
  inline bool is_full() const noexcept { return _count == _size; }
  inline size_t size() const noexcept { return _count; }

  inline void push(const T& val) {
    if (is_full()) {
      throw std::out_of_range{"ERROR: Queue overflow, can't push"};
    }
    _data[(_head + _count) % _size] = val;
    ++_count;
  }


  inline T pop() {
    if (is_empty()) {
      throw std::out_of_range{"ERROR: Queue is empty, can't pop"};
    }
    T val = _data[_head];
    _head = (_head + 1) % _size;
    --_count;
    return val;
  }

  inline T& front() {
    if (is_empty()) {
      throw std::out_of_range{"ERROR: Queue is empty, can't get front"};
    }
    return _data[_head];
  }

  inline T& back() {
    if (is_empty()) {
      throw std::out_of_range{"ERROR: Queue is empty, can't get back"};
    }
    return _data[(_head + _count - 1) % _size];
  }
};

#endif  // LIB_QUEUE_ON_MASS_QUEUE_ON_MASS_H_
