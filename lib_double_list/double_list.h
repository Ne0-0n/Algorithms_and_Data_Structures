// Copyright 2026 Kutyaev Egor
#pragma once

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

  Node* _head;
  Node* _tail;

 public:
  template <class Type>
  class Iterator {
    Type* p_cur;

   public:
    Iterator(Type* ptr = nullptr) { p_cur = ptr; }
    Iterator(const Iterator& other) { p_cur = other.p_cur; }

    Type& operator*() const { return *p_cur; }

    Iterator& operator=(const Iterator& other) {
      if (*this != other) {
        p_cur = other.p_cur;
      }
      return *this;
    }

    bool operator!=(const Iterator& other) const {
      return p_cur != other.p_cur;
    }

    Iterator operator++(int) {
      Iterator tmp = *this;
      p_cur++;
      return tmp;
    }
  };

  typedef Iterator<T> iterator;
  typedef Iterator<const T> iterator;

  iterator begin() noexcept;
  iterator end() noexcept;

  const_iterator begin() const noexcept;
  const_iterator end() const noexcept;
};
