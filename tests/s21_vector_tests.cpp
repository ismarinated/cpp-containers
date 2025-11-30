#include <gtest/gtest.h>

#include <vector>

#include "../vector/s21_vector.h"

TEST(VectorIterator, begin) {
  s21::vector<int> vec_test{10, 20, 30, 40};
  std::vector<int> vec_original{10, 20, 30, 40};

  auto it_test = vec_test.begin();
  auto it_original = vec_original.begin();

  ASSERT_TRUE(*it_test == *it_original);
}

TEST(VectorIterator, end) {
  s21::vector<int> vec_test{10, 20, 30, 40};
  std::vector<int> vec_original{10, 20, 30, 40};

  auto it_test = vec_test.end() - 1;
  auto it_original = vec_original.end() - 1;

  ASSERT_TRUE(*it_test == *it_original);
}

TEST(VectorIterator, iterator_operator_plusplus) {
  s21::vector<int> vec_test{10, 20, 30, 40};
  std::vector<int> vec_original{10, 20, 30, 40};

  auto it_test = vec_test.begin();
  auto it_original = vec_original.begin();

  it_test++;
  it_original++;

  ASSERT_TRUE(*it_test == *it_original);
}

TEST(VectorIterator, iterator_operator_minusminus) {
  s21::vector<int> vec_test{10, 20, 30, 40};
  std::vector<int> vec_original{10, 20, 30, 40};

  auto it_test = vec_test.end();
  auto it_original = vec_original.end();

  it_test--;
  it_original--;

  ASSERT_TRUE(*it_test == *it_original);
}

TEST(VectorIterator, iterator_operator_equallequall) {
  s21::vector<int> vec_test{10, 20, 30, 40};

  auto it_test_one = vec_test.begin();
  auto it_test_two = vec_test.begin();

  ASSERT_TRUE(it_test_one == it_test_two);
}

TEST(VectorIterator, iterator_operator_min_or_equal) {
  s21::vector<int> vec_test{10, 20, 30, 40};

  auto it_test_b = vec_test.begin();
  auto it_test_e = vec_test.end();

  ASSERT_TRUE(it_test_b <= it_test_e);
}

TEST(VectorIterator, const_iterator) {
  s21::vector<int> vec_test{10, 20, 30, 40};
  std::vector<int> vec_original{10, 20, 30, 40};

  s21::vector<int>::const_iterator it_test(vec_test.data());
  std::vector<int>::const_iterator it_original(vec_original.data());

  ASSERT_TRUE(*it_test == *it_original);
}

TEST(VectorIterator, const_iterator_operator_plus_minus) {
  s21::vector<int> vec_test{10, 20, 30, 40};
  std::vector<int> vec_original{10, 20, 30, 40};

  s21::vector<int>::const_iterator it_test(vec_test.data());
  std::vector<int>::const_iterator it_original(vec_original.data());

  it_test++;
  it_original++;

  it_test--;
  it_original--;

  it_test = it_test + 2;
  it_original = it_original + 2;

  it_test = it_test - 1;
  it_original = it_original - 1;

  ASSERT_TRUE(*it_test == *it_original);
}

TEST(VectorIterator, const_iterator_operator_equallequall) {
  s21::vector<int> vec_test{10, 20, 30, 40};
  s21::vector<int>::const_iterator it_test_one(vec_test.data());
  s21::vector<int>::const_iterator it_test_two(vec_test.data());

  ASSERT_TRUE(it_test_one == it_test_two);
}

TEST(VectorIterator, const_iterator_operator_no_equall) {
  s21::vector<int> vec_test{10, 20, 30, 40};
  s21::vector<int>::const_iterator it_test_one(vec_test.data());
  s21::vector<int>::const_iterator it_test_two(vec_test.data());
  it_test_two++;
  ASSERT_TRUE(it_test_one != it_test_two);
}

TEST(VectorIterator, const_iterator_operator_small_or_equal) {
  s21::vector<int> vec_test{10, 20, 30, 40};

  s21::vector<int>::const_iterator it_test_one(vec_test.data());
  s21::vector<int>::const_iterator it_test_two(vec_test.data());
  it_test_two++;

  ASSERT_TRUE(it_test_one <= it_test_two);
}

TEST(VectorIterator, const_iterator_operator_big_or_equal) {
  s21::vector<int> vec_test{10, 20, 30, 40};

  s21::vector<int>::const_iterator it_test_one(vec_test.data());
  s21::vector<int>::const_iterator it_test_two(vec_test.data());
  it_test_two++;

  ASSERT_TRUE(it_test_two >= it_test_one);
}

TEST(VectorIterator, const_iterator_operator_small) {
  s21::vector<int> vec_test{10, 20, 30, 40};

  s21::vector<int>::const_iterator it_test_one(vec_test.data());
  s21::vector<int>::const_iterator it_test_two(vec_test.data());
  it_test_two++;

  ASSERT_TRUE(it_test_one < it_test_two);
}

TEST(VectorIterator, const_iterator_operator_big) {
  s21::vector<int> vec_test{10, 20, 30, 40};

  s21::vector<int>::const_iterator it_test_one(vec_test.data());
  s21::vector<int>::const_iterator it_test_two(vec_test.data());
  it_test_two++;

  ASSERT_TRUE(it_test_two > it_test_one);
}

TEST(VectorAccessToElements, at) {
  s21::vector<int> vec_test{10, 20, 30, 40};
  std::vector<int> vec_original{10, 20, 30, 40};

  auto res_test = vec_test.at(2);
  auto res_original = vec_original.at(2);

  ASSERT_TRUE(res_test == res_original);
}

TEST(VectorAccessToElements, at_exception) {
  s21::vector<int> vec_test{10, 20, 30, 40};
  std::vector<int> vec_original{10, 20, 30, 40};

  std::string exception_original;

  try {
    vec_original.at(9);
  } catch (const std::out_of_range& e) {
    exception_original = e.what();
  }

  try {
    vec_test.at(9);
  } catch (const std::out_of_range& e) {
    EXPECT_EQ(std::string(e.what()), exception_original);
  }
}

TEST(VectorAccessToElements, front) {
  s21::vector<int> vec_test{10, 20, 30, 40};
  std::vector<int> vec_original{10, 20, 30, 40};

  auto res_test = vec_test.front();
  auto res_original = vec_original.front();

  ASSERT_TRUE(res_test == res_original);
}

TEST(VectorAccessToElements, back) {
  s21::vector<int> vec_test{10, 20, 30, 40};
  std::vector<int> vec_original{10, 20, 30, 40};

  auto res_test = vec_test.back();
  auto res_original = vec_original.back();

  ASSERT_TRUE(res_test == res_original);
}

TEST(VectorAccessToElements, operator) {
  s21::vector<int> vec_test{10, 20, 30, 40};
  std::vector<int> vec_original{10, 20, 30, 40};

  auto res_test = vec_test[2];
  auto res_original = vec_original[2];

  ASSERT_TRUE(res_test == res_original);
}

TEST(VectorChanges, clear) {
  s21::vector<int> vec_test{10, 20, 30, 40};
  std::vector<int> vec_original{10, 20, 30, 40};

  vec_test.clear();
  vec_original.clear();

  auto count = 0;
  if (vec_test.size() != vec_original.size()) {
    count++;
  }
  for (int i = 0; i < (int)vec_test.size(); i++) {
    if (vec_test[i] != vec_original[i]) {
      count++;
    }
  }

  ASSERT_TRUE(count == 0);
}

TEST(VectorChanges, erase) {
  s21::vector<int> vec_test{10, 20, 30, 40};
  std::vector<int> vec_original{10, 20, 30, 40};

  auto it_test = vec_test.begin() + 2;
  auto it_original = vec_original.begin() + 2;

  vec_test.erase(it_test);
  vec_original.erase(it_original);

  auto count = 0;
  if (vec_test.size() != vec_original.size()) {
    count++;
  }
  for (int i = 0; i < (int)vec_test.size(); i++) {
    if (vec_test[i] != vec_original[i]) {
      count++;
    }
  }

  ASSERT_TRUE(count == 0);
}

TEST(VectorChanges, insert_iterator) {
  s21::vector<int> vec_test{10, 20, 30, 40};
  std::vector<int> vec_original{10, 20, 30, 40};

  auto it_test = vec_test.begin() + 2;
  auto it_original = vec_original.begin() + 2;

  it_test = vec_test.insert(it_test, 888);
  it_original = vec_original.insert(it_original, 888);

  ASSERT_TRUE(*it_test == *it_original);
}

TEST(VectorChanges, insert) {
  s21::vector<int> vec_test{10, 20, 30, 40};
  std::vector<int> vec_original{10, 20, 30, 40};

  auto it_test = vec_test.begin() + 2;
  auto it_original = vec_original.begin() + 2;

  vec_test.insert(it_test, 888);
  vec_original.insert(it_original, 888);

  auto count = 0;
  if (vec_test.size() != vec_original.size()) {
    count++;
  }
  for (int i = 0; i < (int)vec_test.size(); i++) {
    if (vec_test[i] != vec_original[i]) {
      count++;
    }
  }

  ASSERT_TRUE(count == 0);
}

TEST(VectorChanges, insert_back) {
  s21::vector<int> vec_test{10, 20, 30, 40};
  std::vector<int> vec_original{10, 20, 30, 40};

  auto it_test = vec_test.end();
  auto it_original = vec_original.end();

  vec_test.insert(it_test, 888);
  vec_original.insert(it_original, 888);

  auto count = 0;
  if (vec_test.size() != vec_original.size()) {
    count++;
  }
  for (int i = 0; i < (int)vec_test.size(); i++) {
    if (vec_test[i] != vec_original[i]) {
      count++;
    }
  }

  ASSERT_TRUE(count == 0);
}

TEST(VectorChanges, push_back) {
  s21::vector<int> vec_test{10, 20, 30, 40};
  std::vector<int> vec_original{10, 20, 30, 40};

  vec_test.push_back(88);
  vec_original.push_back(88);

  auto count = 0;
  if (vec_test.size() != vec_original.size()) {
    count++;
  }
  for (int i = 0; i < (int)vec_test.size(); i++) {
    if (vec_test[i] != vec_original[i]) {
      count++;
    }
  }

  ASSERT_TRUE(count == 0);
}

TEST(VectorChanges, push_back_empty_vector) {
  s21::vector<int> vec_test;
  std::vector<int> vec_original;

  vec_test.push_back(88);
  vec_original.push_back(88);

  auto count = 0;
  if (vec_test.size() != vec_original.size()) {
    count++;
  }
  for (int i = 0; i < (int)vec_test.size(); i++) {
    if (vec_test[i] != vec_original[i]) {
      count++;
    }
  }

  ASSERT_TRUE(count == 0);
}

TEST(VectorChanges, pop_back) {
  s21::vector<int> vec_test{10, 20, 30, 40};
  std::vector<int> vec_original{10, 20, 30, 40};

  vec_test.pop_back();
  vec_original.pop_back();

  auto count = 0;
  if (vec_test.size() != vec_original.size()) {
    count++;
  }
  for (int i = 0; i < (int)vec_test.size(); i++) {
    if (vec_test[i] != vec_original[i]) {
      count++;
    }
  }

  ASSERT_TRUE(count == 0);
}

TEST(VectorChanges, pop_back_two) {
  s21::vector<int> vec_test;
  vec_test.pop_back();
  auto count = 0;
  if (vec_test.size() != 0) {
    count++;
  }
  ASSERT_TRUE(count == 0);
}

TEST(VectorChanges, swap) {
  s21::vector<int> vec_test_one{10, 20, 30, 40};
  s21::vector<int> vec_test_two(3);
  std::vector<int> vec_original_one{10, 20, 30, 40};
  std::vector<int> vec_original_two(3);

  vec_test_one.swap(vec_test_two);
  vec_original_one.swap(vec_original_two);

  auto count = 0;
  if (vec_test_one.size() != vec_original_one.size()) {
    count++;
  }
  for (int i = 0; i < (int)vec_test_one.size(); i++) {
    if (vec_test_one[i] != vec_original_one[i]) {
      count++;
    }
  }

  if (vec_test_two.size() != vec_original_two.size()) {
    count++;
  }
  for (int i = 0; i < (int)vec_test_two.size(); i++) {
    if (vec_test_two[i] != vec_original_two[i]) {
      count++;
    }
  }

  ASSERT_TRUE(count == 0);
}

TEST(VectorConstructors, move) {
  s21::vector<int> vec_for_move_test{10, 20, 30, 40};
  s21::vector<int> vec_test = std::move(vec_for_move_test);

  std::vector<int> vec_for_move_original{10, 20, 30, 40};
  std::vector<int> vec_original = std::move(vec_for_move_original);

  auto count = 0;
  if (!vec_for_move_test.empty() && !vec_for_move_original.empty()) {
    count++;
  }
  if (vec_test.size() != vec_original.size()) {
    count++;
  }
  for (int i = 0; i < (int)vec_test.size(); i++) {
    if (vec_test[i] != vec_original[i]) {
      count++;
    }
  }

  ASSERT_TRUE(count == 0);
}

TEST(VectorConstructors, move_operator) {
  s21::vector<int> vec_for_move_test{10, 20, 30, 40};
  s21::vector<int> vec_test{100, 200, 300};
  vec_test = std::move(vec_for_move_test);

  std::vector<int> vec_for_move_original{10, 20, 30, 40};
  std::vector<int> vec_original{100, 200, 300};
  vec_original = std::move(vec_for_move_original);

  auto count = 0;
  if (!vec_for_move_test.empty() && !vec_for_move_original.empty()) {
    count++;
  }
  if (vec_test.size() != vec_original.size()) {
    count++;
  }
  for (int i = 0; i < (int)vec_test.size(); i++) {
    if (vec_test[i] != vec_original[i]) {
      count++;
    }
  }

  ASSERT_TRUE(count == 0);
}

TEST(VectorDopMetods, insert_many_back_one) {
  s21::vector<int> vec_test{10, 20, 30, 40};
  s21::vector<int> vec_expectation{10, 20, 30, 40, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  vec_test.insert_many_back(1, 2, 3, 4, 5, 6, 7, 8, 9);

  auto count = 0;
  if (vec_test.size() != vec_expectation.size()) {
    count++;
  }
  for (int i = 0; i < (int)vec_test.size(); i++) {
    if (vec_test[i] != vec_expectation[i]) {
      count++;
    }
  }

  ASSERT_TRUE(count == 0);
}

TEST(VectorDopMetods, insert_many_back_two) {
  s21::vector<int> vec_test;
  s21::vector<int> vec_expectation{1, 2, 3, 4, 5};

  vec_test.insert_many_back(1, 2, 3, 4, 5);

  auto count = 0;
  if (vec_test.size() != vec_expectation.size()) {
    count++;
  }
  for (int i = 0; i < (int)vec_test.size(); i++) {
    if (vec_test[i] != vec_expectation[i]) {
      count++;
    }
  }

  ASSERT_TRUE(count == 0);
}

TEST(VectorDopMetods, insert_many_one) {
  s21::vector<int> vec_test{10, 20, 30, 40};
  s21::vector<int> vec_expectation{10, 20, 1, 2, 3, 4, 5, 30, 40};

  s21::vector<int>::const_iterator it = vec_test.cbegin() + 2;

  vec_test.insert_many(it, 1, 2, 3, 4, 5);

  auto count = 0;
  if (vec_test.size() != vec_expectation.size()) {
    count++;
  }
  for (int i = 0; i < (int)vec_test.size(); i++) {
    if (vec_test[i] != vec_expectation[i]) {
      count++;
    }
  }

  ASSERT_TRUE(count == 0);
}

TEST(VectorDopMetods, insert_many_two) {
  s21::vector<int> vec_test{10, 20, 30, 40};
  s21::vector<int> vec_expectation{10, 20, 30, 40};

  s21::vector<int>::const_iterator it = vec_test.cbegin();

  vec_test.insert_many(it);

  auto count = 0;
  if (vec_test.size() != vec_expectation.size()) {
    count++;
  }
  for (int i = 0; i < (int)vec_test.size(); i++) {
    if (vec_test[i] != vec_expectation[i]) {
      count++;
    }
  }

  ASSERT_TRUE(count == 0);
}

TEST(VectorDopMetods, insert_many_exception) {
  s21::vector<int> vec_test{10, 20, 30, 40};
  s21::vector<int>::const_iterator it = vec_test.cbegin() + 7;

  try {
    vec_test.insert_many(it);
  } catch (const std::out_of_range& e) {
    EXPECT_EQ(std::string(e.what()), "pos is out of vector");
  }
}

TEST(VectorFilling, private_data) {
  s21::vector<int> vec_test{10, 20, 30, 40};
  std::vector<int> vec_expected{10, 20, 30, 40};

  auto res_test = vec_test.data();
  auto res_expected = vec_expected.data();

  int count = 0;
  for (int i = 0; i < (int)vec_test.size(); i++) {
    if (res_test[i] != res_expected[i]) {
      count++;
    }
  }

  ASSERT_TRUE(count == 0);
}

TEST(VectorFilling, private_size) {
  s21::vector<int> vec_test{10, 20, 30, 40};
  std::vector<int> vec_expected{10, 20, 30, 40};

  auto res_test = vec_test.size();
  auto res_expected = vec_expected.size();

  ASSERT_TRUE(res_test == res_expected);
}

TEST(VectorFilling, private_capacity_one) {
  s21::vector<int> vec_test{10, 20, 30, 40};
  std::vector<int> vec_expected{10, 20, 30, 40};

  auto res_test = vec_test.capacity();
  auto res_expected = vec_expected.capacity();

  ASSERT_TRUE(res_test == res_expected);
}

TEST(VectorFilling, private_capacity_two) {
  s21::vector<int> vec_test{10, 20, 30, 40};
  std::vector<int> vec_expected{10, 20, 30, 40};

  vec_test.push_back(88);
  vec_expected.push_back(88);

  auto res_test = vec_test.capacity();
  auto res_expected = vec_expected.capacity();

  ASSERT_TRUE(res_test == res_expected);
}

TEST(VectorFilling, private_capacity_three) {
  s21::vector<std::string> vec_test;
  std::vector<std::string> vec_expected;

  auto res_test = vec_test.capacity();
  auto res_expected = vec_expected.capacity();

  ASSERT_TRUE(res_test == res_expected);
}

TEST(VectorFilling, max_size_one) {
  s21::vector<std::string> vec_test;
  std::vector<std::string> vec_expected;

  auto res_test = vec_test.max_size();
  auto res_expected = vec_expected.max_size();

  ASSERT_TRUE(res_test == res_expected);
}

TEST(VectorFilling, max_size_two) {
  s21::vector<double> vec_test{10, 20, 30, 40};
  std::vector<double> vec_expected{10, 20, 30, 40};

  auto res_test = vec_test.max_size();
  auto res_expected = vec_expected.max_size();

  ASSERT_TRUE(res_test == res_expected);
}

TEST(VectorFilling, reserve_one) {
  s21::vector<int> vec_test{10, 20, 30, 40};
  std::vector<int> vec_expected{10, 20, 30, 40};

  vec_test.reserve(24);
  vec_expected.reserve(24);

  auto res_test = vec_test.capacity();
  auto res_expected = vec_expected.capacity();

  ASSERT_TRUE(res_test == res_expected);
}

TEST(VectorFilling, reserve_two) {
  s21::vector<int> vec_test{10, 20, 30, 40};
  std::vector<int> vec_expected{10, 20, 30, 40};

  vec_test.reserve(2);
  vec_expected.reserve(2);

  auto res_test = vec_test.capacity();
  auto res_expected = vec_expected.capacity();

  ASSERT_TRUE(res_test == res_expected);
}

TEST(VectorFilling, shrink_to_fit) {
  s21::vector<int> vec_test{10, 20, 30, 40};
  std::vector<int> vec_expected{10, 20, 30, 40};

  vec_test.push_back(88);
  vec_expected.push_back(88);

  vec_test.shrink_to_fit();
  vec_expected.shrink_to_fit();

  auto res_test = vec_test.capacity();
  auto res_expected = vec_expected.capacity();

  ASSERT_TRUE(res_test == res_expected);
}