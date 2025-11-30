#include <gtest/gtest.h>

#include "../list/s21_list.h"

TEST(ListTest, DefaultConstructor) {
  s21::list<int> lst;
  EXPECT_EQ(lst.size(), 0);
  EXPECT_TRUE(lst.empty());
}

TEST(ListTest, PushBackAndFront) {
  s21::list<int> lst;
  lst.push_back(1);
  lst.push_back(2);
  lst.push_front(0);

  EXPECT_EQ(lst.size(), 3);
  EXPECT_EQ(lst.front(), 0);
  EXPECT_EQ(lst.back(), 2);
}

TEST(ListTest, PopBack) {
  s21::list<int> lst;
  lst.push_back(1);
  lst.push_back(2);
  lst.pop_back();

  EXPECT_EQ(lst.size(), 1);
  EXPECT_EQ(lst.back(), 1);
}

TEST(ListTest, PopFront) {
  s21::list<int> lst;
  lst.push_back(1);
  lst.push_back(2);
  lst.pop_front();

  EXPECT_EQ(lst.size(), 1);
  EXPECT_EQ(lst.front(), 2);
}

TEST(ListTest, InitializerListConstructor) {
  s21::list<int> lst = {1, 2, 3, 4, 5};

  EXPECT_EQ(lst.size(), 5);
  EXPECT_EQ(lst.front(), 1);
  EXPECT_EQ(lst.back(), 5);
}

TEST(ListTest, CopyConstructor) {
  s21::list<int> lst1;
  lst1.push_back(1);
  lst1.push_back(2);
  s21::list<int> lst2 = lst1;

  EXPECT_EQ(lst2.size(), 2);
  EXPECT_EQ(lst2.front(), 1);
  EXPECT_EQ(lst2.back(), 2);
}

TEST(ListTest, MoveConstructor) {
  s21::list<int> lst1;
  lst1.push_back(1);
  lst1.push_back(2);
  s21::list<int> lst2 = std::move(lst1);

  EXPECT_EQ(lst2.size(), 2);
  EXPECT_EQ(lst2.front(), 1);
  EXPECT_EQ(lst2.back(), 2);
  EXPECT_TRUE(lst1.empty());
}

TEST(ListTest, MoveAssignmentOperator) {
  s21::list<int> lst1;
  lst1.push_back(1);
  lst1.push_back(2);
  s21::list<int> lst2;
  lst2 = std::move(lst1);

  EXPECT_EQ(lst2.size(), 2);
  EXPECT_EQ(lst2.front(), 1);
  EXPECT_EQ(lst2.back(), 2);
  EXPECT_TRUE(lst1.empty());
}

TEST(ListTest, Iterator) {
  s21::list<int> lst;
  lst.push_back(1);
  lst.push_back(2);
  lst.push_back(3);

  s21::list<int>::iterator it = lst.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(it, lst.end());
}

TEST(ListTest, IteratorDecrement) {
  s21::list<int> lst = {10, 20, 30, 40, 50};

  s21::list<int>::iterator it = lst.begin();
  ++it;
  ++it;

  EXPECT_EQ(*it, 30);

  --it;
  EXPECT_EQ(*it, 20);
}

TEST(ListTest, IteratorEquality) {
  s21::list<int> lst = {10, 20, 30};
  s21::list<int>::iterator it1 = lst.begin();
  s21::list<int>::iterator it2 = lst.begin();

  EXPECT_TRUE(it1 == it2);

  ++it2;
  EXPECT_FALSE(it1 == it2);
  EXPECT_TRUE(it1 != it2);
}

TEST(ListTest, ConstIterator) {
  s21::list<int> lst;
  lst.push_back(1);
  lst.push_back(2);
  lst.push_back(3);

  const s21::list<int>& const_lst = lst;
  s21::list<int>::const_iterator const_it = const_lst.begin();

  EXPECT_EQ(*const_it, 1);
  ++const_it;
  EXPECT_EQ(*const_it, 2);
  ++const_it;
  EXPECT_EQ(*const_it, 3);
  ++const_it;
  EXPECT_EQ(const_it, const_lst.end());
}

TEST(ListTest, ConstIteratorDecrement) {
  const s21::list<int> lst = {10, 20, 30, 40, 50};

  s21::list<int>::const_iterator const_it = lst.begin();
  ++const_it;
  ++const_it;

  EXPECT_EQ(*const_it, 30);

  --const_it;
  EXPECT_EQ(*const_it, 20);
}

TEST(ListTest, ConstIteratorEquality) {
  const s21::list<int> l = {10, 20, 30};
  s21::list<int>::const_iterator it1 = l.begin();
  s21::list<int>::const_iterator it2 = l.begin();

  EXPECT_TRUE(it1 == it2);

  ++it2;
  EXPECT_FALSE(it1 == it2);
  EXPECT_TRUE(it1 != it2);
}

TEST(ListTest, IteratorsSameList) {
  s21::list<int> lst = {1, 2, 3, 4, 5};
  const s21::list<int>& const_lst = lst;

  s21::list<int>::iterator it = lst.begin();
  s21::list<int>::const_iterator const_it = const_lst.begin();

  EXPECT_EQ(*it, *const_it);
  ++it;
  ++const_it;
  EXPECT_EQ(*it, *const_it);
}

TEST(ListTest, Merge) {
  s21::list<int> lst1;
  lst1.push_back(1);
  lst1.push_back(3);

  s21::list<int> lst2;
  lst2.push_back(2);
  lst2.push_back(4);

  lst1.merge(lst2);

  EXPECT_EQ(lst1.size(), 4);
  EXPECT_EQ(lst1.front(), 1);
  EXPECT_EQ(lst1.back(), 4);
}

TEST(ListTest, Reverse) {
  s21::list<int> lst;
  lst.push_back(1);
  lst.push_back(2);
  lst.push_back(3);

  lst.reverse();

  EXPECT_EQ(lst.front(), 3);
  EXPECT_EQ(lst.back(), 1);
}

TEST(ListTest, Unique) {
  s21::list<int> lst;
  lst.push_back(1);
  lst.push_back(1);
  lst.push_back(2);
  lst.push_back(2);

  lst.unique();

  EXPECT_EQ(lst.size(), 2);
  EXPECT_EQ(lst.front(), 1);
  EXPECT_EQ(lst.back(), 2);
}

TEST(ListTest, Sort) {
  s21::list<int> lst;
  lst.push_back(3);
  lst.push_back(1);
  lst.push_back(2);

  lst.sort();

  EXPECT_EQ(lst.front(), 1);
  EXPECT_EQ(lst.back(), 3);
}

TEST(ListTest, IntType) {
  s21::list<int> lst;
  lst.push_back(10);
  lst.push_back(20);
  lst.push_back(30);

  EXPECT_EQ(lst.size(), 3);
  EXPECT_EQ(lst.front(), 10);
  EXPECT_EQ(lst.back(), 30);
}

TEST(ListTest, DoubleType) {
  s21::list<double> lst;
  lst.push_back(10.5);
  lst.push_back(20.75);
  lst.push_back(30.3);

  EXPECT_EQ(lst.size(), 3);
  EXPECT_DOUBLE_EQ(lst.front(), 10.5);
  EXPECT_DOUBLE_EQ(lst.back(), 30.3);
}

TEST(ListTest, StringType) {
  s21::list<std::string> lst;
  lst.push_back("Hello");
  lst.push_back("World");
  lst.push_back("!");

  EXPECT_EQ(lst.size(), 3);
  EXPECT_EQ(lst.front(), "Hello");
  EXPECT_EQ(lst.back(), "!");
}

struct Person {
  std::string name;
  int age;
};

TEST(ListTest, CustomType) {
  s21::list<Person> lst;
  lst.push_back({"John", 30});
  lst.push_back({"Alice", 25});
  lst.push_back({"Bob", 35});

  EXPECT_EQ(lst.size(), 3);
  EXPECT_EQ(lst.front().name, "John");
  EXPECT_EQ(lst.back().name, "Bob");
}

TEST(ListTest, EmptyList) {
  s21::list<int> lst;

  EXPECT_TRUE(lst.empty());
  EXPECT_EQ(lst.size(), 0);
}

TEST(ListTest, SingleElementList) {
  s21::list<int> lst;
  lst.push_back(42);

  EXPECT_FALSE(lst.empty());
  EXPECT_EQ(lst.size(), 1);
  EXPECT_EQ(lst.front(), 42);
  EXPECT_EQ(lst.back(), 42);

  lst.pop_back();

  EXPECT_TRUE(lst.empty());
  EXPECT_EQ(lst.size(), 0);
}

TEST(ListTest, SortEmptyAndSingleElement) {
  s21::list<int> empty_lst;

  empty_lst.sort();

  EXPECT_EQ(empty_lst.size(), 0);

  s21::list<int> single_elem_lst;
  single_elem_lst.push_back(5);

  single_elem_lst.sort();

  EXPECT_EQ(single_elem_lst.size(), 1);
  EXPECT_EQ(single_elem_lst.front(), 5);
}

TEST(ListTest, MergeEmptyList) {
  s21::list<int> lst1;
  s21::list<int> lst2;

  lst1.merge(lst2);

  EXPECT_EQ(lst1.size(), 0);
  EXPECT_EQ(lst2.size(), 0);
}

TEST(ListTest, Splice) {
  s21::list<int> lst1;
  lst1.push_back(1);
  lst1.push_back(2);
  lst1.push_back(3);

  s21::list<int> lst2;
  lst2.push_back(4);
  lst2.push_back(5);

  const s21::list<int>& const_lst = lst1;
  s21::list<int>::const_iterator pos = const_lst.begin();

  lst1.splice(pos, lst2);

  EXPECT_EQ(lst1.size(), 5);
  EXPECT_EQ(lst1.front(), 4);
  EXPECT_EQ(lst1.back(), 3);
  EXPECT_EQ(lst2.size(), 0);

  s21::list<int>::const_iterator const_it = const_lst.begin();

  EXPECT_EQ(*const_it, 4);
  ++const_it;
  EXPECT_EQ(*const_it, 5);
  ++const_it;
  EXPECT_EQ(*const_it, 1);
  ++const_it;
  EXPECT_EQ(*const_it, 2);
  ++const_it;
  EXPECT_EQ(*const_it, 3);
  ++const_it;
  EXPECT_EQ(const_it, const_lst.end());
}

TEST(ListTest, MaxSize) {
  s21::list<int> lst;

  size_t m_size = lst.max_size();

  ASSERT_GT(m_size, 0);
  ASSERT_LE(m_size, std::numeric_limits<size_t>::max());
}

TEST(ListTest, Insert) {
  s21::list<int> lst = {1, 3, 4};

  s21::list<int>::iterator it = lst.begin();
  ++it;

  lst.insert(it, 2);

  EXPECT_EQ(lst.size(), 4);

  it = lst.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 4);
}

TEST(ListTest, EraseLastElement) {
  s21::list<int> lst = {1, 2, 3};

  s21::list<int>::iterator it = lst.begin();

  int flag = 0;
  while (!flag && it != lst.end()) {
    s21::list<int>::iterator next_it = it;
    ++next_it;
    if (next_it == lst.end())
      flag = 1;
    else
      ++it;
  }

  lst.erase(it);

  EXPECT_EQ(lst.size(), 2);
  EXPECT_EQ(lst.back(), 2);
}

TEST(ListTest, EraseFirstElement) {
  s21::list<int> lst = {1, 2, 3};

  s21::list<int>::iterator it = lst.begin();

  lst.erase(it);

  EXPECT_EQ(lst.size(), 2);
  EXPECT_EQ(lst.front(), 2);
}

TEST(ListTest, EraseMiddleElement) {
  s21::list<int> lst = {1, 2, 3, 4, 5};

  s21::list<int>::iterator it = lst.begin();

  ++it;
  ++it;
  lst.erase(it);

  EXPECT_EQ(lst.size(), 4);
  EXPECT_EQ(lst.front(), 1);
  EXPECT_EQ(lst.back(), 5);
}

TEST(ListTest, InsertManyAtBegin) {
  s21::list<int> lst;
  lst.push_back(1);
  lst.push_back(2);
  lst.push_back(6);

  const s21::list<int>& const_lst = lst;
  s21::list<int>::const_iterator it = const_lst.begin();

  lst.insert_many(it, 3, 4, 5);

  EXPECT_EQ(lst.size(), 6);

  const s21::list<int>& const_lst2 = lst;
  s21::list<int>::const_iterator check_it = const_lst2.begin();

  EXPECT_EQ(*check_it, 3);
  ++check_it;
  EXPECT_EQ(*check_it, 4);
  ++check_it;
  EXPECT_EQ(*check_it, 5);
  ++check_it;
  EXPECT_EQ(*check_it, 1);
  ++check_it;
  EXPECT_EQ(*check_it, 2);
  ++check_it;
  EXPECT_EQ(*check_it, 6);
  ++check_it;
  EXPECT_EQ(check_it, const_lst2.end());
}

TEST(ListTest, InsertManyInMiddle) {
  s21::list<int> lst;
  lst.push_back(1);
  lst.push_back(2);
  lst.push_back(6);

  const s21::list<int>& const_lst = lst;
  s21::list<int>::const_iterator it = const_lst.begin();

  ++it;

  lst.insert_many(it, 3, 4, 5);

  EXPECT_EQ(lst.size(), 6);

  const s21::list<int>& const_lst2 = lst;
  s21::list<int>::const_iterator check_it = const_lst2.begin();

  EXPECT_EQ(*check_it, 1);
  ++check_it;
  EXPECT_EQ(*check_it, 3);
  ++check_it;
  EXPECT_EQ(*check_it, 4);
  ++check_it;
  EXPECT_EQ(*check_it, 5);
  ++check_it;
  EXPECT_EQ(*check_it, 2);
  ++check_it;
  EXPECT_EQ(*check_it, 6);
  ++check_it;
  EXPECT_EQ(check_it, const_lst2.end());
}

TEST(ListTest, InsertManyAtEnd) {
  s21::list<int> lst;
  lst.push_back(1);
  lst.push_back(2);
  lst.push_back(6);

  const s21::list<int>& const_lst = lst;
  s21::list<int>::const_iterator it = const_lst.end();

  lst.insert_many(it, 3, 4, 5);

  EXPECT_EQ(lst.size(), 6);

  const s21::list<int>& const_lst2 = lst;
  s21::list<int>::const_iterator check_it = const_lst2.begin();

  EXPECT_EQ(*check_it, 1);
  ++check_it;
  EXPECT_EQ(*check_it, 2);
  ++check_it;
  EXPECT_EQ(*check_it, 6);
  ++check_it;
  EXPECT_EQ(*check_it, 3);
  ++check_it;
  EXPECT_EQ(*check_it, 4);
  ++check_it;
  EXPECT_EQ(*check_it, 5);
  ++check_it;
  EXPECT_EQ(check_it, const_lst2.end());
}

TEST(ListTest, InsertManyZeroElements) {
  s21::list<int> lst;
  lst.push_back(1);
  lst.push_back(2);
  lst.push_back(6);

  const s21::list<int>& const_lst = lst;
  s21::list<int>::const_iterator it = const_lst.begin();
  ++it;

  lst.insert_many(it);

  EXPECT_EQ(lst.size(), 3);

  const s21::list<int>& const_lst2 = lst;
  s21::list<int>::const_iterator check_it = const_lst2.begin();

  EXPECT_EQ(*check_it, 1);
  ++check_it;
  EXPECT_EQ(*check_it, 2);
  ++check_it;
  EXPECT_EQ(*check_it, 6);
  ++check_it;
  EXPECT_EQ(check_it, const_lst2.end());
}

TEST(ListTest, InsertManyIntoEmptyList) {
  s21::list<int> lst;

  const s21::list<int>& const_lst = lst;
  s21::list<int>::const_iterator it = const_lst.begin();

  lst.insert_many(it, 3, 4, 5);

  EXPECT_EQ(lst.size(), 3);

  const s21::list<int>& const_lst2 = lst;
  s21::list<int>::const_iterator check_it = const_lst2.begin();

  EXPECT_EQ(*check_it, 3);
  ++check_it;
  EXPECT_EQ(*check_it, 4);
  ++check_it;
  EXPECT_EQ(*check_it, 5);
  ++check_it;
  EXPECT_EQ(check_it, const_lst2.end());
}

TEST(ListTest, InsertManyIntoSingleElementList) {
  s21::list<int> lst;
  lst.push_back(1);

  const s21::list<int>& const_lst = lst;
  s21::list<int>::const_iterator it = const_lst.begin();

  lst.insert_many(it, 3, 4, 5);

  EXPECT_EQ(lst.size(), 4);

  const s21::list<int>& const_lst2 = lst;
  s21::list<int>::const_iterator check_it = const_lst2.begin();

  EXPECT_EQ(*check_it, 3);
  ++check_it;
  EXPECT_EQ(*check_it, 4);
  ++check_it;
  EXPECT_EQ(*check_it, 5);
  ++check_it;
  EXPECT_EQ(*check_it, 1);
  ++check_it;
  EXPECT_EQ(check_it, const_lst2.end());
}

TEST(ListTest, InsertManyBack) {
  s21::list<int> lst;
  lst.push_back(1);
  lst.push_back(2);
  lst.push_back(6);

  const s21::list<int>& const_lst = lst;
  s21::list<int>::const_iterator it = const_lst.begin();
  ++it;

  lst.insert_many_back(3, 4, 5);

  EXPECT_EQ(lst.size(), 6);

  const s21::list<int>& const_lst2 = lst;
  s21::list<int>::const_iterator check_it = const_lst2.begin();

  EXPECT_EQ(*check_it, 1);
  ++check_it;
  EXPECT_EQ(*check_it, 2);
  ++check_it;
  EXPECT_EQ(*check_it, 6);
  ++check_it;
  EXPECT_EQ(*check_it, 3);
  ++check_it;
  EXPECT_EQ(*check_it, 4);
  ++check_it;
  EXPECT_EQ(*check_it, 5);
  ++check_it;
  EXPECT_EQ(check_it, const_lst2.end());
}

TEST(ListTest, InsertManyBackZeroElements) {
  s21::list<int> lst;
  lst.push_back(1);
  lst.push_back(2);
  lst.push_back(6);

  const s21::list<int>& const_lst = lst;
  s21::list<int>::const_iterator it = const_lst.begin();
  ++it;

  lst.insert_many_back();

  EXPECT_EQ(lst.size(), 3);

  const s21::list<int>& const_lst2 = lst;
  s21::list<int>::const_iterator check_it = const_lst2.begin();

  EXPECT_EQ(*check_it, 1);
  ++check_it;
  EXPECT_EQ(*check_it, 2);
  ++check_it;
  EXPECT_EQ(*check_it, 6);
  ++check_it;
  EXPECT_EQ(check_it, const_lst2.end());
}

TEST(ListTest, InsertManyBackSingleElement) {
  s21::list<int> lst;
  lst.push_back(1);

  lst.insert_many_back(2, 3, 4);

  EXPECT_EQ(lst.size(), 4);

  const s21::list<int>& const_lst2 = lst;
  s21::list<int>::const_iterator check_it = const_lst2.begin();

  EXPECT_EQ(*check_it, 1);
  ++check_it;
  EXPECT_EQ(*check_it, 2);
  ++check_it;
  EXPECT_EQ(*check_it, 3);
  ++check_it;
  EXPECT_EQ(*check_it, 4);
  ++check_it;
  EXPECT_EQ(check_it, const_lst2.end());
}

TEST(ListTest, InsertManyFront) {
  s21::list<int> lst;
  lst.push_back(1);
  lst.push_back(2);
  lst.push_back(6);

  const s21::list<int>& const_lst = lst;
  s21::list<int>::const_iterator it = const_lst.begin();
  ++it;

  lst.insert_many_front(3, 4, 5);

  EXPECT_EQ(lst.size(), 6);

  const s21::list<int>& const_lst2 = lst;
  s21::list<int>::const_iterator check_it = const_lst2.begin();

  EXPECT_EQ(*check_it, 3);
  ++check_it;
  EXPECT_EQ(*check_it, 4);
  ++check_it;
  EXPECT_EQ(*check_it, 5);
  ++check_it;
  EXPECT_EQ(*check_it, 1);
  ++check_it;
  EXPECT_EQ(*check_it, 2);
  ++check_it;
  EXPECT_EQ(*check_it, 6);
  ++check_it;
  EXPECT_EQ(check_it, const_lst2.end());
}

TEST(ListTest, InsertManyFrontZeroElements) {
  s21::list<int> lst;
  lst.push_back(1);
  lst.push_back(2);
  lst.push_back(6);

  const s21::list<int>& const_lst = lst;
  s21::list<int>::const_iterator it = const_lst.begin();
  ++it;

  lst.insert_many_front();

  EXPECT_EQ(lst.size(), 3);

  const s21::list<int>& const_lst2 = lst;
  s21::list<int>::const_iterator check_it = const_lst2.begin();

  EXPECT_EQ(*check_it, 1);
  ++check_it;
  EXPECT_EQ(*check_it, 2);
  ++check_it;
  EXPECT_EQ(*check_it, 6);
  ++check_it;
  EXPECT_EQ(check_it, const_lst2.end());
}

TEST(ListTest, InsertManyFrontSingleElement) {
  s21::list<int> lst;
  lst.push_back(1);

  lst.insert_many_front(2, 3, 4);

  EXPECT_EQ(lst.size(), 4);

  const s21::list<int>& const_lst2 = lst;
  s21::list<int>::const_iterator check_it = const_lst2.begin();

  EXPECT_EQ(*check_it, 2);
  ++check_it;
  EXPECT_EQ(*check_it, 3);
  ++check_it;
  EXPECT_EQ(*check_it, 4);
  ++check_it;
  EXPECT_EQ(*check_it, 1);
  ++check_it;
  EXPECT_EQ(check_it, const_lst2.end());
}