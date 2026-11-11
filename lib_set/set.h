#ifndef LIB_SET_SET_H_
#define LIB_SET_SET_H_

#include <iosfwd>

#include "../lib_bitfield/bitfield.h"

class Set {
 public:
  explicit Set(std::size_t maxPower = 0);
  explicit Set(const BitField& bf);
  Set(const Set& other) = default;
  Set(Set&& other) noexcept;
  ~Set() = default;

  Set& operator=(const Set& other) = default;
  Set& operator=(Set&& other) noexcept;

  operator BitField() const { return _bf; }

  std::size_t max_power() const noexcept { return _maxPower; }

  void insert(std::size_t elem);
  void erase(std::size_t elem);
  bool is_member(std::size_t elem) const;

  bool operator==(const Set& rhs) const noexcept { return _bf == rhs._bf; }
  bool operator!=(const Set& rhs) const noexcept { return !(*this == rhs); }

  Set operator+(std::size_t elem) const;
  Set operator-(std::size_t elem) const;
  Set& operator+=(std::size_t elem);
  Set& operator-=(std::size_t elem);

  Set operator+(const Set& rhs) const;
  Set operator*(const Set& rhs) const;
  Set operator-(const Set& rhs) const;
  Set& operator+=(const Set& rhs);
  Set& operator*=(const Set& rhs);
  Set& operator-=(const Set& rhs);

  Set operator-() const;

  friend std::ostream& operator<<(std::ostream& os, const Set& s);
  friend std::istream& operator>>(std::istream& is, Set& s);

 private:
  std::size_t _maxPower;
  BitField _bf;
};

#endif  // LIB_SET_SET_H_
