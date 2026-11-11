// Copyright 2026

#include <gtest/gtest.h>

#include <initializer_list>
#include <sstream>
#include <utility>

#include "../lib_set/set.h"

static Set make(std::size_t n, std::initializer_list<std::size_t> elems) {
    Set s(n);
    for (auto e : elems) s.insert(e);
    return s;
}

TEST(Set, StartsEmpty) {
    Set s(20);
    EXPECT_EQ(s.max_power(), 20u);
    for (std::size_t i = 0; i < 20; ++i) EXPECT_FALSE(s.is_member(i));
}

TEST(Set, InsertEraseIsMember) {
    Set s(100);
    s.insert(3); s.insert(64);
    EXPECT_TRUE(s.is_member(3));
    EXPECT_TRUE(s.is_member(64));
    s.erase(3);
    EXPECT_FALSE(s.is_member(3));
    s.insert(64);                       // идемпотентность
    EXPECT_TRUE(s.is_member(64));
}

TEST(Set, OutOfUniverseThrows) {
    Set s(10);
    EXPECT_THROW(s.insert(10), std::out_of_range);
    EXPECT_THROW(s.erase(11), std::out_of_range);
    EXPECT_THROW(s.is_member(10), std::out_of_range);
}

TEST(Set, ElementOperators) {
    Set s(10);
    Set t = s + 3;
    EXPECT_FALSE(s.is_member(3));       // исходное не изменилось
    EXPECT_TRUE(t.is_member(3));
    Set u = t - 3;
    EXPECT_FALSE(u.is_member(3));
    s += 4;
    EXPECT_TRUE(s.is_member(4));
    s -= 4;
    EXPECT_FALSE(s.is_member(4));
}

TEST(Set, ChainedElementOperators) {
    Set s = Set(10) + 1 + 2 + 3 - 2;
    EXPECT_TRUE(s.is_member(1));
    EXPECT_FALSE(s.is_member(2));
    EXPECT_TRUE(s.is_member(3));
}

TEST(Set, Union) {
    Set a = make(10, {1, 2}), b = make(10, {2, 3});
    EXPECT_EQ(a + b, make(10, {1, 2, 3}));
}

TEST(Set, Intersection) {
    Set a = make(10, {1, 2}), b = make(10, {2, 3});
    EXPECT_EQ(a * b, make(10, {2}));
}

TEST(Set, Difference) {
    Set a = make(10, {1, 2}), b = make(10, {2, 3});
    EXPECT_EQ(a - b, make(10, {1}));
}

TEST(Set, DifferenceWithSmallerUniverseKeepsHighElements) {
    Set a = make(70, {1, 65}), b = make(10, {1});
    Set d = a - b;
    EXPECT_FALSE(d.is_member(1));
    EXPECT_TRUE(d.is_member(65));
}

TEST(Set, CompoundSetOperators) {
    Set a = make(10, {1, 2});
    a += make(10, {3});
    EXPECT_EQ(a, make(10, {1, 2, 3}));
    a *= make(10, {2, 3, 4});
    EXPECT_EQ(a, make(10, {2, 3}));
    a -= make(10, {3});
    EXPECT_EQ(a, make(10, {2}));
}

TEST(Set, Complement) {
    Set a = make(5, {1, 3});
    Set c = -a;
    EXPECT_EQ(c, make(5, {0, 2, 4}));
    EXPECT_EQ(-c, a);
    EXPECT_EQ(c.max_power(), 5u);
    EXPECT_EQ(a + c, -Set(5));          // объединение с дополнением = универсум
    EXPECT_EQ(a * c, Set(5));
}

TEST(Set, ConstructFromBitField) {
    BitField bf(8);
    bf.set(2); bf.set(7);
    Set s(bf);
    EXPECT_EQ(s.max_power(), 8u);
    EXPECT_TRUE(s.is_member(2));
    EXPECT_TRUE(s.is_member(7));
    EXPECT_FALSE(s.is_member(0));
}

TEST(Set, ConversionToBitField) {
    Set s = make(8, {1, 4});
    BitField bf = s;
    EXPECT_EQ(bf.size(), 8u);
    EXPECT_TRUE(bf.get(1));
    EXPECT_TRUE(bf.get(4));
    EXPECT_FALSE(bf.get(0));
}

TEST(Set, CopySemantics) {
    Set a = make(10, {1, 2});
    Set b(a);
    b.insert(5);
    EXPECT_FALSE(a.is_member(5));
    Set c(3);
    c = a;
    EXPECT_EQ(c, a);
    c = c;
    EXPECT_EQ(c, a);
}

TEST(Set, MoveSemantics) {
    Set a = make(10, {1, 2});
    Set b(std::move(a));
    EXPECT_EQ(b, make(10, {1, 2}));
    EXPECT_EQ(a.max_power(), 0u);       // NOLINT
    Set c(3);
    c = std::move(b);
    EXPECT_EQ(c, make(10, {1, 2}));
    EXPECT_EQ(b.max_power(), 0u);       // NOLINT
}

TEST(Set, Output) {
    std::ostringstream os;
    os << make(10, {1, 3, 9});
    EXPECT_EQ(os.str(), "{1, 3, 9}");
    std::ostringstream empty;
    empty << Set(5);
    EXPECT_EQ(empty.str(), "{}");
}

TEST(Set, Input) {
    Set s(10);
    std::istringstream is("{1, 3, 9}");
    is >> s;
    EXPECT_TRUE(is);
    EXPECT_EQ(s, make(10, {1, 3, 9}));
}

TEST(Set, InputWithoutCommasAndEmpty) {
    Set s(10);
    std::istringstream is("{2 4} {}");
    is >> s;
    EXPECT_EQ(s, make(10, {2, 4}));
    is >> s;
    EXPECT_EQ(s, Set(10));
}

TEST(Set, InputErrors) {
    Set s = make(10, {1});
    std::istringstream bad1("1, 2}");
    bad1 >> s;
    EXPECT_TRUE(bad1.fail());
    std::istringstream bad2("{1, 20}");
    bad2 >> s;
    EXPECT_TRUE(bad2.fail());
    EXPECT_EQ(s, make(10, {1}));        // при ошибке множество не меняется
}
