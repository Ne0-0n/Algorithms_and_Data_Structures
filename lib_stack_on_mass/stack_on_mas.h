// Copyright 2026 Kutyaev Egor
#ifndef LIB_STACK_ON_MASS_STACK_ON_MAS_H_
#define LIB_STACK_ON_MASS_STACK_ON_MAS_H_

#include <cstddef>
#include <stdexcept>

template <class T>
class TStackOnMass {
  T* _data;
  size_t _size;
  int _top;

 public:
  explicit TStackOnMass(size_t size);
  TStackOnMass(const TStackOnMass& other);
  TStackOnMass& operator=(const TStackOnMass& other);
  ~TStackOnMass();

  bool is_empty() const noexcept;
  bool is_full() const noexcept;
  void push(const T& val);
  T pop();
  T top();
};

#endif  // LIB_STACK_ON_MASS_STACK_ON_MAS_H_
