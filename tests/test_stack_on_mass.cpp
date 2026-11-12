// Copyright 2026 Kutyaev Egor
#include <gtest/gtest.h>

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

TEST(TStackOnMassTest, InitialStateIsEmpty) {
  TStackOnMass<int> stack(3);
  EXPECT_TRUE(stack.is_empty());
  EXPECT_FALSE(stack.is_full());
}

TEST(TStackOnMassTest, PushAndTop) {
  TStackOnMass<int> stack(3);
  stack.push(10);
  EXPECT_FALSE(stack.is_empty());
  EXPECT_EQ(stack.top(), 10);

  stack.push(20);
  EXPECT_EQ(stack.top(), 20);
}

TEST(TStackOnMassTest, OverflowThrowsOutOfRange) {
  TStackOnMass<int> stack(2);
  stack.push(1);
  stack.push(2);
  EXPECT_THROW(stack.push(3), std::out_of_range);
}

