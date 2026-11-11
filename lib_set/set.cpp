#include "../lib_set/set.h"

#include <algorithm>
#include <istream>
#include <ostream>
#include <utility>

Set::Set(std::size_t maxPower) : _maxPower(maxPower), _bf(maxPower) {}

Set::Set(const BitField& bf) : _maxPower(bf.size()), _bf(bf) {}

Set::Set(Set&& other) noexcept
    : _maxPower(other._maxPower), _bf(std::move(other._bf)) {
  other._maxPower = 0;
}

Set& Set::operator=(Set&& other) noexcept {
  if (this != &other) {
    _maxPower = other._maxPower;
    _bf = std::move(other._bf);
    other._maxPower = 0;
  }
  return *this;
}

void Set::insert(std::size_t elem) { _bf.set(elem); }

void Set::erase(std::size_t elem) { _bf.reset(elem); }

bool Set::is_member(std::size_t elem) const { return _bf.get(elem); }

Set Set::operator+(std::size_t elem) const {
  Set res(*this);
  res.insert(elem);
  return res;
}

Set Set::operator-(std::size_t elem) const {
  Set res(*this);
  res.erase(elem);
  return res;
}

Set& Set::operator+=(std::size_t elem) {
  insert(elem);
  return *this;
}

Set& Set::operator-=(std::size_t elem) {
  erase(elem);
  return *this;
}

Set Set::operator+(const Set& rhs) const { return Set(_bf | rhs._bf); }

Set Set::operator*(const Set& rhs) const { return Set(_bf & rhs._bf); }

Set Set::operator-(const Set& rhs) const {

  BitField zero(std::max(_maxPower, rhs._maxPower));
  return Set((_bf | zero) & ~(rhs._bf | zero));
}

Set& Set::operator+=(const Set& rhs) { return *this = *this + rhs; }

Set& Set::operator*=(const Set& rhs) { return *this = *this * rhs; }

Set& Set::operator-=(const Set& rhs) { return *this = *this - rhs; }

Set Set::operator-() const { return Set(~_bf); }

std::ostream& operator<<(std::ostream& os, const Set& s) {
  os << '{';
  bool first = true;
  for (std::size_t i = 0; i < s._maxPower; ++i) {
    if (s.is_member(i)) {
      if (!first) os << ", ";
      os << i;
      first = false;
    }
  }
  return os << '}';
}

std::istream& operator>>(std::istream& is, Set& s) {
  char c;
  if (!(is >> c)) return is;
  if (c != '{') {
    is.setstate(std::ios::failbit);
    return is;
  }
  Set tmp(s._maxPower);
  while (true) {
    if (!(is >> c)) return is;
    if (c == '}') break;
    if (c == ',') continue;
    is.putback(c);
    std::size_t v;
    if (!(is >> v) || v >= tmp._maxPower) {
      is.setstate(std::ios::failbit);
      return is;
    }
    tmp.insert(v);
  }
  s = std::move(tmp);
  return is;
}
