#include "../lib_bitfield/bitfield.h"

#include <istream>
#include <ostream>
#include <stdexcept>

BitField::BitField(unsigned int len) {
    _size = len;
    _memSize = words_for(len);
    _mem = new Word[_memSize]();
}

BitField::BitField(const BitField& other) {
    _size = other._size;
    _memSize = other._memSize;
    _mem = new Word[_memSize];
    for (unsigned int i = 0; i < _memSize; ++i) {
        _mem[i] = other._mem[i];
    }
}

BitField::BitField(BitField&& other) {
    _size = other._size;
    _memSize = other._memSize;
    _mem = other._mem;
    other._size = 0;
    other._memSize = 0;
    other._mem = nullptr;
}

BitField::~BitField() { delete[] _mem; }

BitField& BitField::operator=(const BitField& other) {
    if (this == &other) {
        return *this;
    }
    Word* newMem = new Word[other._memSize];
    for (unsigned int i = 0; i < other._memSize; ++i) {
        newMem[i] = other._mem[i];
    }
    delete[] _mem;
    _mem = newMem;
    _size = other._size;
    _memSize = other._memSize;
    return *this;
}

BitField& BitField::operator=(BitField&& other) {
    if (this == &other) {
        return *this;
    }
    delete[] _mem;
    _size = other._size;
    _memSize = other._memSize;
    _mem = other._mem;
    other._size = 0;
    other._memSize = 0;
    other._mem = nullptr;
    return *this;
}

void BitField::check_index(unsigned int n) const {
    if (n >= _size) {
        throw std::out_of_range("BitField: bit index out of range");
    }
}

void BitField::clear_tail() {
    unsigned int rest = _size % BITS_IN_WORD;
    if (rest != 0) {
        _mem[_memSize - 1] &= (Word(1) << rest) - 1;
    }
}

void BitField::set(unsigned int n) {
    check_index(n);
    _mem[n / BITS_IN_WORD] |= Word(1) << (n % BITS_IN_WORD);
}

void BitField::reset(unsigned int n) {
    check_index(n);
    _mem[n / BITS_IN_WORD] &= ~(Word(1) << (n % BITS_IN_WORD));
}

bool BitField::get(unsigned int n) const {
    check_index(n);
    Word bit = (_mem[n / BITS_IN_WORD] >> (n % BITS_IN_WORD)) & Word(1);
    return bit != 0;
}

bool BitField::operator==(const BitField& rhs) const {
    if (_size != rhs._size) {
        return false;
    }
    for (unsigned int i = 0; i < _memSize; ++i) {
        if (_mem[i] != rhs._mem[i]) {
            return false;
        }
    }
    return true;
}

BitField BitField::operator|(const BitField& rhs) const {
    unsigned int len = _size;
    if (rhs._size > len) {
        len = rhs._size;
    }
    BitField res(len);
    for (unsigned int i = 0; i < res._memSize; ++i) {
        Word a = 0;
        Word b = 0;
        if (i < _memSize) {
            a = _mem[i];
        }
        if (i < rhs._memSize) {
            b = rhs._mem[i];
        }
        res._mem[i] = a | b;
    }
    return res;
}

BitField BitField::operator&(const BitField& rhs) const {
    unsigned int len = _size;
    if (rhs._size > len) {
        len = rhs._size;
    }
    BitField res(len);
    for (unsigned int i = 0; i < res._memSize; ++i) {
        if (i < _memSize && i < rhs._memSize) {
            res._mem[i] = _mem[i] & rhs._mem[i];
        }
    }
    return res;
}

BitField BitField::operator~() const {
    BitField res(_size);
    for (unsigned int i = 0; i < _memSize; ++i) {
        res._mem[i] = ~_mem[i];
    }
    res.clear_tail();
    return res;
}

BitField& BitField::operator|=(const BitField& rhs) {
    *this = *this | rhs;
    return *this;
}

BitField& BitField::operator&=(const BitField& rhs) {
    *this = *this & rhs;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const BitField& bf) {
    for (unsigned int i = 0; i < bf._size; ++i) {
        if (bf.get(i)) {
            os << '1';
        }
        else {
            os << '0';
        }
    }
    return os;
}

std::istream& operator>>(std::istream& is, BitField& bf) {
    char c;
    is >> c;
    if (!is) {
        return is;
    }
    is.putback(c);

    BitField tmp(bf._size);
    for (unsigned int i = 0; i < bf._size; ++i) {
        is.get(c);
        if (!is || (c != '0' && c != '1')) {
            is.setstate(std::ios::failbit);
            return is;
        }
        if (c == '1') {
            tmp.set(i);
        }
    }
    bf = tmp;
    return is;
}