// Copyright 2026

#include <gtest/gtest.h>

#include <sstream>
#include <utility>

#include "../lib_bitfield/bitfield.h"

TEST(BitField, CreatedZeroed) {
    BitField bf(70);
    EXPECT_EQ(bf.size(), 70u);
    for (std::size_t i = 0; i < 70; ++i) EXPECT_FALSE(bf.get(i));
}

TEST(BitField, ZeroLength) {
    BitField bf(0);
    EXPECT_EQ(bf.size(), 0u);
    EXPECT_THROW(bf.get(0), std::out_of_range);
    EXPECT_EQ(~bf, bf);
}

TEST(BitField, SetResetGet) {
    BitField bf(100);
    bf.set(0); bf.set(31); bf.set(32); bf.set(99);
    EXPECT_TRUE(bf.get(0));
    EXPECT_TRUE(bf.get(31));
    EXPECT_TRUE(bf.get(32));
    EXPECT_TRUE(bf.get(99));
    EXPECT_FALSE(bf.get(1));
    bf.reset(32);
    EXPECT_FALSE(bf.get(32));
    bf.set(5); bf.set(5);              // повторная установка безвредна
    EXPECT_TRUE(bf.get(5));
    bf.reset(6);                       // сброс нулевого бита безвреден
    EXPECT_FALSE(bf.get(6));
}

TEST(BitField, OutOfRangeThrows) {
    BitField bf(10);
    EXPECT_THROW(bf.set(10), std::out_of_range);
    EXPECT_THROW(bf.reset(10), std::out_of_range);
    EXPECT_THROW(bf.get(100), std::out_of_range);
}

TEST(BitField, Or) {
    BitField a(40), b(40);
    a.set(1); a.set(35);
    b.set(2); b.set(35);
    BitField c = a | b;
    EXPECT_TRUE(c.get(1));
    EXPECT_TRUE(c.get(2));
    EXPECT_TRUE(c.get(35));
    EXPECT_FALSE(c.get(3));
}

TEST(BitField, And) {
    BitField a(40), b(40);
    a.set(1); a.set(35);
    b.set(2); b.set(35);
    BitField c = a & b;
    EXPECT_FALSE(c.get(1));
    EXPECT_FALSE(c.get(2));
    EXPECT_TRUE(c.get(35));
}

TEST(BitField, NotRespectsLengthAndIsInvolution) {
    BitField a(37);
    a.set(3);
    BitField n = ~a;
    EXPECT_EQ(n.size(), 37u);
    for (std::size_t i = 0; i < 37; ++i) EXPECT_EQ(n.get(i), i != 3);
    EXPECT_EQ(~n, a);
    // хвост последнего слова не должен загрязняться
    EXPECT_EQ(~BitField(37) & ~BitField(37), ~BitField(37));
}

TEST(BitField, CompoundOperators) {
    BitField a(20), b(20);
    a.set(1); b.set(2);
    a |= b;
    EXPECT_TRUE(a.get(1));
    EXPECT_TRUE(a.get(2));
    a &= b;
    EXPECT_FALSE(a.get(1));
    EXPECT_TRUE(a.get(2));
}

TEST(BitField, DifferentLengths) {
    BitField a(10), b(70);
    a.set(9); b.set(65); b.set(9);
    BitField o = a | b;
    EXPECT_EQ(o.size(), 70u);
    EXPECT_TRUE(o.get(9));
    EXPECT_TRUE(o.get(65));
    BitField n = a & b;
    EXPECT_EQ(n.size(), 70u);
    EXPECT_TRUE(n.get(9));
    EXPECT_FALSE(n.get(65));
}

TEST(BitField, Equality) {
    BitField a(10), b(10), c(11);
    EXPECT_EQ(a, b);
    a.set(1);
    EXPECT_NE(a, b);
    b.set(1);
    EXPECT_EQ(a, b);
    EXPECT_NE(a, c);
}

TEST(BitField, CopyConstructorMakesDeepCopy) {
    BitField a(50);
    a.set(10);
    BitField b(a);
    b.set(11);
    EXPECT_FALSE(a.get(11));
    EXPECT_TRUE(b.get(10));
}

TEST(BitField, CopyAssignment) {
    BitField a(50), b(5);
    a.set(10);
    b = a;
    EXPECT_EQ(b, a);
    b.set(20);
    EXPECT_FALSE(a.get(20));
    b = b;                              // самоприсваивание
    EXPECT_TRUE(b.get(20));
}

TEST(BitField, MoveConstructor) {
    BitField a(50);
    a.set(7);
    BitField b(std::move(a));
    EXPECT_EQ(b.size(), 50u);
    EXPECT_TRUE(b.get(7));
    EXPECT_EQ(a.size(), 0u);            // NOLINT: проверка после move
}

TEST(BitField, MoveAssignment) {
    BitField a(50), b(3);
    a.set(7);
    b = std::move(a);
    EXPECT_EQ(b.size(), 50u);
    EXPECT_TRUE(b.get(7));
    EXPECT_EQ(a.size(), 0u);            // NOLINT
    a = BitField(8);                    // moved-from объект остаётся пригодным
    a.set(1);
    EXPECT_TRUE(a.get(1));
}

TEST(BitField, Output) {
    BitField a(6);
    a.set(0); a.set(3); a.set(5);
    std::ostringstream os;
    os << a;
    EXPECT_EQ(os.str(), "100101");
}

TEST(BitField, Input) {
    BitField a(6);
    std::istringstream is("  100101");
    is >> a;
    EXPECT_TRUE(is);
    EXPECT_TRUE(a.get(0));
    EXPECT_FALSE(a.get(1));
    EXPECT_TRUE(a.get(5));
}

TEST(BitField, InputInvalidSetsFailAndKeepsValue) {
    BitField a(4);
    a.set(1);
    std::istringstream is("01x1");
    is >> a;
    EXPECT_TRUE(is.fail());
    EXPECT_TRUE(a.get(1));
    EXPECT_FALSE(a.get(0));
}

TEST(BitField, InputTooShortFails) {
    BitField a(8);
    std::istringstream is("101");
    is >> a;
    EXPECT_TRUE(is.fail());
}
