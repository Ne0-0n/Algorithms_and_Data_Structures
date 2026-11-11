#ifndef LIB_BITFIELD_BITFIELD_H_
#define LIB_BITFIELD_BITFIELD_H_

#include <iosfwd>

class BitField {
public:
    typedef unsigned int Word;

    explicit BitField(unsigned int len = 0);
    BitField(const BitField& other);
    BitField(BitField&& other);
    ~BitField();

    BitField& operator=(const BitField& other);
    BitField& operator=(BitField&& other);

    unsigned int size() const { return _size; }
    void set(unsigned int n);
    void reset(unsigned int n);
    bool get(unsigned int n) const;

    bool operator==(const BitField& rhs) const;
    bool operator!=(const BitField& rhs) const { return !(*this == rhs); }

    BitField operator|(const BitField& rhs) const;
    BitField operator&(const BitField& rhs) const;
    BitField operator~() const;
    BitField& operator|=(const BitField& rhs);
    BitField& operator&=(const BitField& rhs);

    friend std::ostream& operator<<(std::ostream& os, const BitField& bf);
    friend std::istream& operator>>(std::istream& is, BitField& bf);

private:
    static const unsigned int BITS_IN_WORD = sizeof(Word) * 8;

    static unsigned int words_for(unsigned int bits) {
        unsigned int words = bits / BITS_IN_WORD;
        if (bits % BITS_IN_WORD != 0) {
            ++words;
        }
        return words;
    }
    void check_index(unsigned int n) const;
    void clear_tail();

    unsigned int _size;
    unsigned int _memSize;
    Word* _mem;
};

#endif  // LIB_BITFIELD_BITFIELD_H_