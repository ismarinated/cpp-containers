#include <gtest/gtest.h>

#include "../stack/s21_stack.h"

TEST(StackTest, DefaultConstructor) {
  s21::stack<int> s;

  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0);
}

TEST(StackTest, InitializerListConstructor) {
  s21::stack<int> s = {1, 2, 3, 4, 5};

  EXPECT_EQ(s.size(), 5);
  EXPECT_EQ(s.top(), 5);
}

TEST(StackTest, CopyConstructor) {
  s21::stack<int> s1 = {10, 20, 30};
  s21::stack<int> s2(s1);

  EXPECT_EQ(s2.size(), s1.size());
  EXPECT_EQ(s2.top(), s1.top());

  s1.pop();

  EXPECT_NE(s1.size(), s2.size());
}

TEST(StackTest, MoveConstructor) {
  s21::stack<int> s1 = {100, 200, 300};
  s21::stack<int> s2(std::move(s1));

  EXPECT_EQ(s2.size(), 3);
  EXPECT_EQ(s2.top(), 300);
  EXPECT_TRUE(s1.empty());
}

TEST(StackTest, MoveAssignment) {
  s21::stack<int> s1 = {5, 15, 25};
  s21::stack<int> s2;

  s2 = std::move(s1);

  EXPECT_EQ(s2.size(), 3);
  EXPECT_EQ(s2.top(), 25);
  EXPECT_TRUE(s1.empty());
}

TEST(StackTest, Top) {
  s21::stack<int> s;

  s.push(42);

  EXPECT_EQ(s.top(), 42);

  s.push(100);

  EXPECT_EQ(s.top(), 100);
}

TEST(StackTest, Push) {
  s21::stack<int> s;

  s.push(1);

  EXPECT_EQ(s.top(), 1);
  EXPECT_EQ(s.size(), 1);

  s.push(2);

  EXPECT_EQ(s.top(), 2);
  EXPECT_EQ(s.size(), 2);
}

TEST(StackTest, Pop) {
  s21::stack<int> s = {10, 20, 30};

  EXPECT_EQ(s.top(), 30);

  s.pop();

  EXPECT_EQ(s.top(), 20);

  s.pop();

  EXPECT_EQ(s.top(), 10);

  s.pop();

  EXPECT_TRUE(s.empty());
}

TEST(StackTest, Swap) {
  s21::stack<int> s1 = {1, 2, 3};
  s21::stack<int> s2 = {10, 20};

  s1.swap(s2);

  EXPECT_EQ(s1.size(), 2);
  EXPECT_EQ(s1.top(), 20);
  EXPECT_EQ(s2.size(), 3);
  EXPECT_EQ(s2.top(), 3);
}

TEST(StackTest, Empty) {
  s21::stack<int> s;

  EXPECT_TRUE(s.empty());

  s.push(5);

  EXPECT_FALSE(s.empty());

  s.pop();

  EXPECT_TRUE(s.empty());
}

TEST(StackTest, Size) {
  s21::stack<int> s;

  EXPECT_EQ(s.size(), 0);

  s.push(1);
  s.push(2);
  s.push(3);

  EXPECT_EQ(s.size(), 3);

  s.pop();

  EXPECT_EQ(s.size(), 2);
}

TEST(StackTest, InsertManyBack) {
  s21::stack<int> s;

  s.insert_many_back(1, 2, 3, 4, 5);

  EXPECT_EQ(s.size(), 5);
  EXPECT_EQ(s.top(), 5);
  s.pop();
  EXPECT_EQ(s.top(), 4);
  s.pop();
  EXPECT_EQ(s.top(), 3);
  s.pop();
  EXPECT_EQ(s.top(), 2);
  s.pop();
  EXPECT_EQ(s.top(), 1);
  s.pop();
  EXPECT_TRUE(s.empty());
}

TEST(StackTest, InsertManyBackEmpty) {
  s21::stack<int> s;

  s.insert_many_back();

  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
}

TEST(StackTest, InsertManyBackMixedElements) {
  s21::stack<int> s;

  s.insert_many_back(1, 2);
  s.insert_many_back(3, 4, 5);

  EXPECT_EQ(s.size(), 5);

  EXPECT_EQ(s.top(), 5);
  s.pop();
  EXPECT_EQ(s.top(), 4);
  s.pop();
  EXPECT_EQ(s.top(), 3);
  s.pop();
  EXPECT_EQ(s.top(), 2);
  s.pop();
  EXPECT_EQ(s.top(), 1);
  s.pop();
  EXPECT_TRUE(s.empty());
}