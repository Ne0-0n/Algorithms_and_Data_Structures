// Copyright 2026

#include <gtest/gtest.h>

#include <vector>

#include "../lib_sieve/sieve.h"

using V = std::vector<std::size_t>;

TEST(Sieve, SmallValues) {
    EXPECT_EQ(sieve(0), V{});
    EXPECT_EQ(sieve(1), V{});
    EXPECT_EQ(sieve(2), (V{2}));
    EXPECT_EQ(sieve(3), (V{2, 3}));
    EXPECT_EQ(sieve(4), (V{2, 3}));
}

TEST(Sieve, UpTo30) {
    EXPECT_EQ(sieve(30), (V{2, 3, 5, 7, 11, 13, 17, 19, 23, 29}));
}

TEST(Sieve, BoundaryIsIncluded) {
    EXPECT_EQ(sieve(31).back(), 31u);
    EXPECT_EQ(sieve(32).back(), 31u);
}

TEST(Sieve, CountOfPrimes) {
    EXPECT_EQ(sieve(100).size(), 25u);
    EXPECT_EQ(sieve(1000).size(), 168u);
    EXPECT_EQ(sieve(100000).size(), 9592u);
}

TEST(Sieve, SetResult) {
    Set s = sieve_set(10);
    EXPECT_TRUE(s.is_member(7));
    EXPECT_FALSE(s.is_member(9));
    EXPECT_FALSE(s.is_member(0));
    EXPECT_FALSE(s.is_member(1));
}
