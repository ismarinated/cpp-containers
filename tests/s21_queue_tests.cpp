#include <gtest/gtest.h>

#include "../queue/s21_queue.h"

TEST(QueueTest, DefaultConstructor) {
  s21::queue<int> q;

  EXPECT_TRUE(q.empty());
  EXPECT_EQ(q.size(), 0);
}

TEST(QueueTest, InitializerListConstructor) {
  s21::queue<int> q = {1, 2, 3, 4, 5};

  EXPECT_FALSE(q.empty());
  EXPECT_EQ(q.size(), 5);
  EXPECT_EQ(q.front(), 1);
  EXPECT_EQ(q.back(), 5);
}

TEST(QueueTest, CopyConstructor) {
  s21::queue<int> q1 = {10, 20, 30};
  s21::queue<int> q2 = q1;

  EXPECT_EQ(q2.size(), 3);
  EXPECT_EQ(q2.front(), 10);
  EXPECT_EQ(q2.back(), 30);
}

TEST(QueueTest, MoveConstructor) {
  s21::queue<int> q1 = {10, 20, 30};
  s21::queue<int> q2 = std::move(q1);

  EXPECT_EQ(q2.size(), 3);
  EXPECT_EQ(q2.front(), 10);
  EXPECT_EQ(q2.back(), 30);
  EXPECT_TRUE(q1.empty());
}

TEST(QueueTest, MoveAssignmentOperator) {
  s21::queue<int> q1 = {5, 6, 7};
  s21::queue<int> q2;
  q2 = std::move(q1);

  EXPECT_EQ(q2.size(), 3);
  EXPECT_EQ(q2.front(), 5);
  EXPECT_EQ(q2.back(), 7);
  EXPECT_TRUE(q1.empty());
}

TEST(QueueTest, FrontBack) {
  s21::queue<int> q;
  q.push(100);
  q.push(200);
  q.push(300);

  EXPECT_EQ(q.front(), 100);
  EXPECT_EQ(q.back(), 300);
}

TEST(QueueTest, Push) {
  s21::queue<int> q;
  q.push(1);
  q.push(2);
  q.push(3);

  EXPECT_EQ(q.size(), 3);
  EXPECT_EQ(q.front(), 1);
  EXPECT_EQ(q.back(), 3);
}

TEST(QueueTest, Pop) {
  s21::queue<int> q;
  q.push(5);
  q.push(10);
  q.push(15);

  q.pop();
  EXPECT_EQ(q.size(), 2);
  EXPECT_EQ(q.front(), 10);

  q.pop();
  EXPECT_EQ(q.size(), 1);
  EXPECT_EQ(q.front(), 15);

  q.pop();
  EXPECT_TRUE(q.empty());
}

TEST(QueueTest, Empty) {
  s21::queue<int> q;

  EXPECT_TRUE(q.empty());

  q.push(1);
  EXPECT_FALSE(q.empty());

  q.pop();
  EXPECT_TRUE(q.empty());
}

TEST(QueueTest, Size) {
  s21::queue<int> q;

  EXPECT_EQ(q.size(), 0);

  q.push(42);
  EXPECT_EQ(q.size(), 1);

  q.push(88);
  EXPECT_EQ(q.size(), 2);

  q.pop();
  EXPECT_EQ(q.size(), 1);
}

TEST(QueueTest, Swap) {
  s21::queue<int> q1 = {1, 2, 3};
  s21::queue<int> q2 = {4, 5};

  q1.swap(q2);

  EXPECT_EQ(q1.size(), 2);
  EXPECT_EQ(q1.front(), 4);
  EXPECT_EQ(q1.back(), 5);

  EXPECT_EQ(q2.size(), 3);
  EXPECT_EQ(q2.front(), 1);
  EXPECT_EQ(q2.back(), 3);
}

TEST(QueueTest, InsertManyBackEmpty) {
  s21::queue<int> q;

  q.insert_many_back();

  EXPECT_EQ(q.size(), 0);
  EXPECT_TRUE(q.empty());
}

TEST(QueueTest, InsertManyBackMultipleElements) {
  s21::queue<int> q;
  q.insert_many_back(1, 2, 3, 4, 5);

  EXPECT_EQ(q.size(), 5);
  EXPECT_EQ(q.front(), 1);
  EXPECT_EQ(q.back(), 5);

  q.pop();
  EXPECT_EQ(q.front(), 2);
  q.pop();
  EXPECT_EQ(q.front(), 3);
  q.pop();
  EXPECT_EQ(q.front(), 4);
  q.pop();
  EXPECT_EQ(q.front(), 5);
  q.pop();

  EXPECT_TRUE(q.empty());
}