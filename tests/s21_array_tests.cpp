#include <gtest/gtest.h>

#include <array>

#include "../array/s21_array.h"

TEST(ArrayMetods, at) {
  s21::array<int, 6> arr_test{10, 20, 30, 40};
  std::array<int, 6> arr_original{10, 20, 30, 40};

  auto res_test = arr_test.at(2);
  auto res_original = arr_original.at(2);

  ASSERT_TRUE(res_test == res_original);
}

TEST(ArrayMetods, at_exception) {
  s21::array<int, 6> arr_test{10, 20, 30, 40};
  std::array<int, 6> arr_original{10, 20, 30, 40};

  std::string exception_original;

  try {
    arr_original.at(9);
  } catch (const std::out_of_range& e) {
    exception_original = e.what();
  }

  try {
    arr_test.at(9);
  } catch (const std::out_of_range& e) {
    EXPECT_EQ(std::string(e.what()), exception_original);
  }
}

TEST(ArrayMetods, front) {
  s21::array<int, 6> arr_test{10, 20, 30, 40};
  std::array<int, 6> arr_original{10, 20, 30, 40};

  auto res_test = arr_test.front();
  auto res_original = arr_original.front();

  ASSERT_TRUE(res_test == res_original);
}

TEST(ArrayMetods, back) {
  s21::array<int, 6> arr_test{10, 20, 30, 40};
  std::array<int, 6> arr_original{10, 20, 30, 40};

  auto res_test = arr_test.back();
  auto res_original = arr_original.back();

  ASSERT_TRUE(res_test == res_original);
}

TEST(ArrayMetods, swap) {
  s21::array<int, 6> arr_test_one{10, 20, 30, 40};
  s21::array<int, 6> arr_test_two{876, 875, 874};
  std::array<int, 6> arr_original_one{10, 20, 30, 40};
  std::array<int, 6> arr_original_two{876, 875, 874};

  arr_test_one.swap(arr_test_two);
  arr_original_one.swap(arr_original_two);

  auto count = 0;
  if (arr_test_one.size() != arr_original_one.size()) {
    count++;
  }
  for (int i = 0; i < (int)arr_test_one.size(); i++) {
    if (arr_test_one[i] != arr_original_one[i]) {
      count++;
    }
  }

  if (arr_test_two.size() != arr_original_two.size()) {
    count++;
  }
  for (int i = 0; i < (int)arr_test_two.size(); i++) {
    if (arr_test_two[i] != arr_original_two[i]) {
      count++;
    }
  }

  ASSERT_TRUE(count == 0);
}

TEST(ArrayMetods, fill) {
  s21::array<int, 6> arr_test{10, 20, 30, 40};
  std::array<int, 6> arr_original{10, 20, 30, 40};

  arr_test.fill(88);
  arr_original.fill(88);

  auto count = 0;
  if (arr_test.size() != arr_original.size()) {
    count++;
  }
  for (int i = 0; i < (int)arr_test.size(); i++) {
    if (arr_test[i] != arr_original[i]) {
      count++;
    }
  }

  ASSERT_TRUE(count == 0);
}

TEST(ArrayMetods, empty) {
  s21::array<int, 0> arr_test;
  std::array<int, 0> arr_original;

  auto res_test = arr_test.empty();
  auto res_original = arr_original.empty();

  ASSERT_TRUE(res_test == res_original);
}

TEST(ArrayMetods, size) {
  s21::array<int, 6> arr_test{10, 20, 30, 40};
  std::array<int, 6> arr_original{10, 20, 30, 40};

  auto res_test = arr_test.size();
  auto res_original = arr_original.size();

  ASSERT_TRUE(res_test == res_original);
}

TEST(ArrayMetods, max_size) {
  s21::array<int, 6> arr_test{10, 20, 30, 40};
  std::array<int, 6> arr_original{10, 20, 30, 40};

  auto res_test = arr_test.max_size();
  auto res_original = arr_original.max_size();

  ASSERT_TRUE(res_test == res_original);
}

TEST(ArrayMetods, data) {
  s21::array<int, 6> arr_test{10, 20, 30, 40};
  std::array<int, 6> arr_original{10, 20, 30, 40};

  auto res_test = arr_test.data();
  auto res_original = arr_original.data();

  ASSERT_TRUE(*res_test == *res_original);
}

TEST(ArrayConstructors, copy) {
  s21::array<int, 6> arr_test_one{10, 20, 30, 40};
  s21::array<int, 6> arr_test_two(arr_test_one);
  std::array<int, 6> arr_original_one{10, 20, 30, 40};
  std::array<int, 6> arr_original_two(arr_original_one);

  auto count = 0;
  if (arr_test_one.size() != arr_original_one.size()) {
    count++;
  }
  for (int i = 0; i < (int)arr_test_one.size(); i++) {
    if (arr_test_one[i] != arr_original_one[i]) {
      count++;
    }
  }

  if (arr_test_two.size() != arr_original_two.size()) {
    count++;
  }
  for (int i = 0; i < (int)arr_test_two.size(); i++) {
    if (arr_test_two[i] != arr_original_two[i]) {
      count++;
    }
  }

  ASSERT_TRUE(count == 0);
}

TEST(ArrayConstructors, move) {
  s21::array<int, 6> arr_test_one{10, 20, 30, 40};
  s21::array<int, 6> arr_test_two = std::move(arr_test_one);
  std::array<int, 6> arr_original_one{10, 20, 30, 40};
  std::array<int, 6> arr_original_two = std::move(arr_original_one);

  auto count = 0;
  if (arr_test_one.size() != arr_original_one.size()) {
    count++;
  }
  for (int i = 0; i < (int)arr_test_one.size(); i++) {
    if (arr_test_one[i] != arr_original_one[i]) {
      count++;
    }
  }

  if (arr_test_two.size() != arr_original_two.size()) {
    count++;
  }
  for (int i = 0; i < (int)arr_test_two.size(); i++) {
    if (arr_test_two[i] != arr_original_two[i]) {
      count++;
    }
  }

  ASSERT_TRUE(count == 0);
}

TEST(ArrayConstructors, move_operator) {
  s21::array<int, 6> arr_test_one{10, 20, 30, 40};
  s21::array<int, 6> arr_test_two{8, 7, 6};
  std::array<int, 6> arr_original_one{10, 20, 30, 40};
  std::array<int, 6> arr_original_two{8, 7, 6};

  arr_test_two = std::move(arr_test_one);
  arr_original_two = std::move(arr_original_one);

  auto count = 0;
  if (arr_test_one.size() != arr_original_one.size()) {
    count++;
  }
  for (int i = 0; i < (int)arr_test_one.size(); i++) {
    if (arr_test_one[i] != arr_original_one[i]) {
      count++;
    }
  }

  if (arr_test_two.size() != arr_original_two.size()) {
    count++;
  }
  for (int i = 0; i < (int)arr_test_two.size(); i++) {
    if (arr_test_two[i] != arr_original_two[i]) {
      count++;
    }
  }

  ASSERT_TRUE(count == 0);
}

TEST(ArrayConstructors, list_exception) {
  try {
    s21::array<int, 3> arr_test{10, 20, 30, 40};
  } catch (const std::invalid_argument& e) {
    EXPECT_EQ(std::string(e.what()), "too many initializers for array");
  }
}

TEST(ArrayIterator, begin) {
  s21::array<int, 6> arr_test{10, 20, 30, 40};
  std::array<int, 6> arr_original{10, 20, 30, 40};

  auto res_test = arr_test.begin();
  auto res_original = arr_original.begin();

  ASSERT_TRUE(*res_test == *res_original);
}

TEST(ArrayIterator, end) {
  s21::array<int, 4> arr_test{10, 20, 30, 40};
  std::array<int, 4> arr_original{10, 20, 30, 40};

  auto res_test = arr_test.end() - 1;
  auto res_original = arr_original.end() - 1;

  ASSERT_TRUE(*res_test == *res_original);
}