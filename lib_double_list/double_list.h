// Copyright 2026 Kutyaev Egor
#pragma once

#include <cstddef>

template <typename T>
struct Node {
  T data_;
  Node<T>* _next;
  Node<T>* _prev;
};

template <typename T>
class DoubleList {
 private:
  Node<T>* _head;
  Node<T>* _tail;
  size_t _size;

 public:
  template <class Type>
  class Iterator {
    Node<T>* p_cur;

   public:
    explicit Iterator(Node<T>* ptr = nullptr) { p_cur = ptr; }
    Iterator(const Iterator& other) { p_cur = other.p_cur; }

    Type& operator*() const { return p_cur->data_; }

    Iterator& operator=(const Iterator& other) {
      if (*this != other) {
        p_cur = other.p_cur;
      }
      return *this;
    }

    bool operator!=(const Iterator& other) const {
      return p_cur != other.p_cur;
    }

    bool operator==(const Iterator& other) const {
      return p_cur == other.p_cur;
    }

    Iterator& operator++() {
      p_cur = p_cur->_next;
      return *this;
    }

    Iterator operator++(int) {
      Iterator tmp = *this;
      p_cur = p_cur->_next;
      return tmp;
    }
  };

  typedef Iterator<T> iterator;
  typedef Iterator<const T> const_iterator;

  DoubleList() : _head(nullptr), _tail(nullptr), _size(0) {}

  iterator begin() noexcept { return iterator(_head); }
  iterator end() noexcept { return iterator(nullptr); }

  const_iterator begin() const noexcept { return const_iterator(_head); }
  const_iterator end() const noexcept { return const_iterator(nullptr); }
};