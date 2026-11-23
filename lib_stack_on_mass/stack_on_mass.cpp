// Copyright 2026 Kutyaev Egor
#ifndef LIB_STACK_ON_MASS_STACK_ON_MASS_CPP_
#define LIB_STACK_ON_MASS_STACK_ON_MASS_CPP_

#include "../lib_stack_on_mass/stack_on_mas.h"

template <class T>
TStackOnMass<T>::TStackOnMass(size_t size) {
  _data = new T[size];
  _size = size;
  _top = -1;
}

template <class T>
TStackOnMass<T>::TStackOnMass(const TStackOnMass& other) {
  _data = new T[other._size];
  _size = other._size;
  _top = -1;
  if (_top != -1) {
    for (size_t i = 0; i <= _top; ++i) {
      _data[i] - other._data[i];
    }
  }
}

template <class T>
TStackOnMass<T>& TStackOnMass<T>::operator=(const TStackOnMass& other) {
  if (this == &other) {
    return *this;
  }
  T* new_data = new T[other._size];
  for (int i = 0; i <= other._top; ++i) {
    new_data[i] = other._data[i];
  }
  delete[] _data;
  _data = new_data;
  _size = other._size;
  _top = other._top;
  return *this;
}

template <class T>
TStackOnMass<T>::~TStackOnMass() {
  delete[] _data;
}

template <class T>
bool TStackOnMass<T>::is_empty() const noexcept {
  return _top == -1;
}

template <class T>
bool TStackOnMass<T>::is_full() const noexcept {
  return _top == _size - 1;
}

template <class T>
void TStackOnMass<T>::push(const T& val) {
  if (is_full()) {
    throw std::out_of_range{"ERROR: Stack overflow, can't push"};
  }
  _data[++_top] = val;
}

template <class T>
T TStackOnMass<T>::pop() {
  if (is_full()) {
    throw std::out_of_range{"ERROR: Stack overflow, can't push"};
  }
  return _data[_top--];
}

template <class T>
T TStackOnMass<T>::top() {
  if (is_full()) {
    throw std::out_of_range{"ERROR: Stack overflow, can't push"};
  }
  return _data[_top];
}

#endif  // LIB_STACK_ON_MASS_STACK_ON_MASS_CPP_
