// Copyright 2026 Kutyaev Egor

#include <gtest/gtest.h>

#include <stdexcept>

#include "../lib_queue_on_mass/queue_on_mass.h"

TEST(QueueOnMass, StartsEmpty) {
  TQueueOnMass<int> q(3);
  EXPECT_TRUE(q.is_empty());
  EXPECT_FALSE(q.is_full());
  EXPECT_EQ(q.size(), 0u);
}


TEST(QueueOnMass, PushPopKeepsFifoOrder) {
  TQueueOnMass<int> q(3);
  q.push(1);
  q.push(2);
  q.push(3);
  EXPECT_EQ(q.pop(), 1);
  EXPECT_EQ(q.pop(), 2);
  EXPECT_EQ(q.pop(), 3);
  EXPECT_TRUE(q.is_empty());
}

TEST(QueueOnMass, FrontAndBackDoNotRemove) {
  TQueueOnMass<int> q(3);
  q.push(1);
  q.push(2);
  EXPECT_EQ(q.front(), 1);
  EXPECT_EQ(q.back(), 2);
  EXPECT_EQ(q.size(), 2u);
}

TEST(QueueOnMass, IsFullWhenCapacityReached) {
  TQueueOnMass<int> q(2);
  q.push(1);
  EXPECT_FALSE(q.is_full());
  q.push(2);
  EXPECT_TRUE(q.is_full());
}

TEST(QueueOnMass, ThrowsOnPushToFull) {
  TQueueOnMass<int> q(1);
  q.push(1);
  EXPECT_THROW(q.push(2), std::out_of_range);
}

TEST(QueueOnMass, ThrowsOnPopFromEmpty) {
  TQueueOnMass<int> q(2);
  EXPECT_THROW(q.pop(), std::out_of_range);
}

TEST(QueueOnMass, ThrowsOnFrontAndBackOfEmpty) {
  TQueueOnMass<int> q(2);
  EXPECT_THROW(q.front(), std::out_of_range);
  EXPECT_THROW(q.back(), std::out_of_range);
}


TEST(QueueOnMass, CopyConstructorMakesIndependentCopy) {
  TQueueOnMass<int> q(3);
  q.push(1);
  q.push(2);
  q.pop();
  q.push(3);
  TQueueOnMass<int> copy(q);
  EXPECT_EQ(copy.size(), 2u);
  EXPECT_EQ(copy.pop(), 2);
  EXPECT_EQ(copy.pop(), 3);
  EXPECT_EQ(q.size(), 2u);
  EXPECT_EQ(q.front(), 2);
}

TEST(QueueOnMass, AssignmentMakesIndependentCopy) {
  TQueueOnMass<int> q(3);
  q.push(1);
  q.push(2);
  TQueueOnMass<int> other(5);
  other.push(9);
  other = q;
  EXPECT_EQ(other.size(), 2u);
  EXPECT_EQ(other.pop(), 1);
  EXPECT_EQ(other.pop(), 2);
  EXPECT_EQ(q.size(), 2u);
}

TEST(QueueOnMass, SelfAssignmentKeepsData) {
  TQueueOnMass<int> q(3);
  q.push(1);
  q.push(2);
  TQueueOnMass<int>& ref = q;
  q = ref;
  EXPECT_EQ(q.pop(), 1);
  EXPECT_EQ(q.pop(), 2);
}
