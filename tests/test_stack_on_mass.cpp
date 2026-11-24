// Copyright 2026 Kutyaev Egor
#include <gtest/gtest.h>

#include <algorithm>
#include <stdexcept>
#include <string>

#include "../lib_algorithms/algorithm.h"
#include "../lib_stack_on_mass/stack_on_mas.h"

TEST(CheckBracketsTest, ValidExpressions) {
  EXPECT_TRUE(check_breckets(""));
  EXPECT_TRUE(check_breckets("()"));
  EXPECT_TRUE(check_breckets("()[]{}"));
  EXPECT_TRUE(check_breckets("{[()]}"));
  EXPECT_TRUE(check_breckets("a + (b * [c - {d / e}])"));
}

TEST(CheckBracketsTest, InvalidExpressions) {
  EXPECT_FALSE(check_breckets("("));
  EXPECT_FALSE(check_breckets(")"));
  EXPECT_FALSE(check_breckets("([)]"));
  EXPECT_FALSE(check_breckets("{[}]"));
  EXPECT_FALSE(check_breckets("((())"));
  EXPECT_FALSE(check_breckets("())"));
}

struct Point {
  int x = 0;
  int y = 0;
  bool operator==(const Point& other) const {
    return x == other.x && y == other.y;
  }
};

TEST(StackOnMass, StartsEmpty) {
  TStackOnMass<int> s(3);
  EXPECT_TRUE(s.is_empty());
  EXPECT_FALSE(s.is_full());
}

TEST(StackOnMass, PushPopKeepsLifoOrder) {
  TStackOnMass<int> s(4);
  s.push(1);
  s.push(2);
  s.push(3);
  EXPECT_EQ(s.pop(), 3);
  EXPECT_EQ(s.pop(), 2);
  EXPECT_EQ(s.pop(), 1);
  EXPECT_TRUE(s.is_empty());
}

TEST(StackOnMass, TopDoesNotRemove) {
  TStackOnMass<int> s(4);
  s.push(1);
  s.push(2);
  EXPECT_EQ(s.top(), 2);
  EXPECT_EQ(s.top(), 2);
  EXPECT_FALSE(s.is_empty());
  EXPECT_EQ(s.pop(), 2);
  EXPECT_EQ(s.top(), 1);
}

TEST(StackOnMass, IsFullWhenCapacityReached) {
  TStackOnMass<int> s(2);
  s.push(1);
  EXPECT_FALSE(s.is_full());
  s.push(2);
  EXPECT_TRUE(s.is_full());
}

TEST(StackOnMass, ThrowsOnPushToFull) {
  TStackOnMass<int> s(1);
  s.push(1);
  EXPECT_THROW(s.push(2), std::out_of_range);
}

TEST(StackOnMass, ReusableAfterBecomingEmpty) {
  TStackOnMass<int> s(3);
  s.push(1);
  s.push(2);
  EXPECT_EQ(s.pop(), 2);
  EXPECT_EQ(s.pop(), 1);
  EXPECT_TRUE(s.is_empty());
  s.push(3);
  s.push(4);
  EXPECT_EQ(s.top(), 4);
  EXPECT_EQ(s.pop(), 4);
  EXPECT_EQ(s.pop(), 3);
}

TEST(StackOnMass, AssignmentMakesIndependentCopy) {
  TStackOnMass<int> s(4);
  s.push(1);
  s.push(2);
  TStackOnMass<int> other(5);
  other.push(9);
  other = s;
  EXPECT_EQ(other.pop(), 2);
  EXPECT_EQ(other.pop(), 1);
  EXPECT_TRUE(other.is_empty());
  EXPECT_EQ(s.top(), 2);
}

TEST(StackOnMass, SelfAssignmentKeepsData) {
  TStackOnMass<int> s(4);
  s.push(1);
  s.push(2);
  TStackOnMass<int>& ref = s;
  s = ref;
  EXPECT_EQ(s.pop(), 2);
  EXPECT_EQ(s.pop(), 1);
}

TEST(StackOnMass, WorksWithStructType) {
  TStackOnMass<Point> s(3);
  s.push(Point{1, 2});
  s.push(Point{3, 4});
  EXPECT_TRUE(s.pop() == (Point{3, 4}));
  EXPECT_TRUE(s.pop() == (Point{1, 2}));
}

TEST(StackOnMass, ThrowsOnPopFromEmpty) {
  TStackOnMass<int> s(2);
  EXPECT_THROW(s.pop(), std::out_of_range);
}

TEST(StackOnMass, ThrowsOnTopOfEmpty) {
  TStackOnMass<int> s(2);
  EXPECT_THROW(s.top(), std::out_of_range);
}

TEST(StackOnMass, PopAndTopWorkOnFull) {
  TStackOnMass<int> s(2);
  s.push(1);
  s.push(2);
  ASSERT_TRUE(s.is_full());
  EXPECT_EQ(s.top(), 2);
  EXPECT_EQ(s.pop(), 2);
  EXPECT_FALSE(s.is_full());
}

TEST(StackOnMass, CopyConstructorMakesIndependentCopy) {
  TStackOnMass<int> s(3);
  s.push(1);
  s.push(2);
  TStackOnMass<int> copy(s);
  EXPECT_EQ(copy.pop(), 2);
  EXPECT_EQ(copy.pop(), 1);
  EXPECT_EQ(s.top(), 2);
}
