#include "tests.h"

using namespace s21;

// Тест конструктора по умолчанию
TEST(MultisetTest, DefaultConstructor) {
  multiset<int> ms;
  std::multiset<int> std_ms;
  EXPECT_TRUE(ms.empty());
  EXPECT_EQ(ms.size(), std_ms.size());
}

// Тест конструктора с initializer_list
TEST(MultisetTest, InitializerListConstructor) {
  multiset<int> ms{1, 2, 2, 3};
  std::multiset<int> std_ms{1, 2, 2, 3};
  EXPECT_FALSE(ms.empty());
  EXPECT_EQ(ms.size(), std_ms.size());
  EXPECT_EQ(ms.count(2), std_ms.count(2));
}

// Тест конструктора копирования
TEST(MultisetTest, CopyConstructor) {
  multiset<int> original{1, 2, 2, 3};
  std::multiset<int> std_original{1, 2, 2, 3};
  multiset<int> copy(original);
  std::multiset<int> std_copy(std_original);
  EXPECT_EQ(copy.size(), std_copy.size());
  EXPECT_EQ(copy.count(2), std_copy.count(2));
}

// Тест конструктора перемещения
TEST(MultisetTest, MoveConstructor) {
  multiset<int> original = {1, 2, 2, 3};
  std::multiset<int> std_original = {1, 2, 2, 3};
  multiset<int> moved(std::move(original));
  std::multiset<int> std_moved(std::move(std_original));
  EXPECT_EQ(moved.size(), std_moved.size());
  EXPECT_EQ(original.size(), std_original.size());
}

// Тест вставки элемента
TEST(MultisetTest, Insert) {
  multiset<int> ms;
  std::multiset<int> std_ms;
  ms.insert(5);
  std_ms.insert(5);
  EXPECT_EQ(ms.size(), std_ms.size());
  EXPECT_EQ(ms.count(5), std_ms.count(5));

  ms.insert(5);
  std_ms.insert(5);
  EXPECT_EQ(ms.size(), std_ms.size());
  EXPECT_EQ(ms.count(5), std_ms.count(5));

  ms.insert(10);
  std_ms.insert(10);
  EXPECT_EQ(ms.size(), std_ms.size());
  EXPECT_EQ(ms.count(10), std_ms.count(10));
}

// Тест поиска элемента
TEST(MultisetTest, Find) {
  multiset<int> ms{1, 2, 2, 3};
  std::multiset<int> std_ms{1, 2, 2, 3};
  EXPECT_EQ(*ms.find(2), *std_ms.find(2));
  EXPECT_EQ(ms.find(4) == ms.end(), std_ms.find(4) == std_ms.end());
}

// Тест удаления элемента
TEST(MultisetTest, Erase) {
  multiset<int> ms{1, 2, 2, 3};
  std::multiset<int> std_ms{1, 2, 2, 3};
  ms.erase(ms.find(2));
  std_ms.erase(std_ms.find(2));
  EXPECT_EQ(ms.size(), std_ms.size());
  EXPECT_EQ(ms.count(2), std_ms.count(2));

  ms.erase(ms.find(1));
  std_ms.erase(std_ms.find(1));
  EXPECT_EQ(ms.size(), std_ms.size());
  EXPECT_EQ(ms.count(1), std_ms.count(1));
}

// Тест на пустоту контейнера
TEST(MultisetTest, Empty) {
  multiset<int> ms;
  std::multiset<int> std_ms;
  EXPECT_EQ(ms.empty(), std_ms.empty());
  ms.insert(10);
  std_ms.insert(10);
  EXPECT_EQ(ms.empty(), std_ms.empty());
}

// Тест очистки контейнера
TEST(MultisetTest, Clear) {
  multiset<int> ms{1, 2, 2, 3};
  std::multiset<int> std_ms{1, 2, 2, 3};
  ms.clear();
  std_ms.clear();
  EXPECT_EQ(ms.empty(), std_ms.empty());
  EXPECT_EQ(ms.size(), std_ms.size());
}

// Тест метода swap
TEST(MultisetTest, Swap) {
  multiset<int> ms1{1, 2, 2};
  multiset<int> ms2{3, 4, 4};
  std::multiset<int> std_ms1{1, 2, 2};
  std::multiset<int> std_ms2{3, 4, 4};

  ms1.swap(ms2);
  std_ms1.swap(std_ms2);

  EXPECT_EQ(ms1.size(), std_ms1.size());
  EXPECT_EQ(ms2.size(), std_ms2.size());
  EXPECT_EQ(*ms1.find(3), *std_ms1.find(3));
  EXPECT_EQ(*ms2.find(1), *std_ms2.find(1));
}

// Тест метода merge
TEST(MultisetTest, Merge) {
  multiset<int> ms1{1, 2, 2};
  multiset<int> ms2{2, 3, 3};
  std::multiset<int> std_ms1{1, 2, 2};
  std::multiset<int> std_ms2{2, 3, 3};

  ms1.merge(ms2);
  std_ms1.merge(std_ms2);

  EXPECT_EQ(ms1.size(), std_ms1.size());
  EXPECT_EQ(ms2.size(), std_ms2.size());
  EXPECT_EQ(ms1.count(2), std_ms1.count(2));
  EXPECT_EQ(ms2.count(2), std_ms2.count(2));
}

// Тест метода contains
TEST(MultisetTest, Contains) {
  multiset<int> ms{1, 2, 2, 3};
  EXPECT_TRUE(ms.contains(2));
  EXPECT_FALSE(ms.contains(4));
}

// Тест метода max_size
TEST(MultisetTest, MaxSize) {
  multiset<int> ms;
  std::multiset<int> std_ms;
  EXPECT_GT(ms.max_size(), 0);
  EXPECT_GT(std_ms.max_size(), 0);
  EXPECT_LT(ms.max_size(), std_ms.max_size() * 2);
}

// Тест константных итераторов
TEST(MultisetTest, ConstIterator) {
  const multiset<int> ms{1, 2, 2, 3};
  const std::multiset<int> std_ms{1, 2, 2, 3};

  auto it = ms.begin();
  auto std_it = std_ms.begin();

  EXPECT_EQ(*it, *std_it);
  ++it;
  ++std_it;
  EXPECT_EQ(*it, *std_it);
}
TEST(MultisetTest, Count) {
  multiset<int> ms{1, 2, 2, 3};
  EXPECT_EQ(ms.count(2), 2);
  EXPECT_EQ(ms.count(1), 1);
  EXPECT_EQ(ms.count(4), 0);
}

// Тест на удаление всех элементов
TEST(MultisetTest, EraseAllElements) {
  multiset<int> ms{1, 2, 2, 3, 3, 3};
  std::multiset<int> std_ms{1, 2, 2, 3, 3, 3};

  while (!ms.empty()) {
    ms.erase(ms.begin());
    std_ms.erase(std_ms.begin());
  }

  EXPECT_TRUE(ms.empty());
  EXPECT_EQ(ms.size(), std_ms.size());
}

// Тест на метод equal_range
TEST(MultisetTest, EqualRange) {
  multiset<int> ms{1, 2, 2, 3, 3, 3};
  std::multiset<int> std_ms{1, 2, 2, 3, 3, 3};

  auto range = ms.equal_range(2);
  auto std_range = std_ms.equal_range(2);

  EXPECT_EQ(*range.first, *std_range.first);
  EXPECT_EQ(*range.second, *std_range.second);

  int count = 0;
  for (auto it = range.first; it != range.second; ++it) {
    ++count;
  }
  EXPECT_EQ(count, 2);
}

// Тест на метод lower_bound
TEST(MultisetTest, LowerBound) {
  multiset<int> ms{1, 2, 2, 3, 4, 4, 5};
  std::multiset<int> std_ms{1, 2, 2, 3, 4, 4, 5};

  auto it = ms.lower_bound(3);
  auto std_it = std_ms.lower_bound(3);

  EXPECT_EQ(*it, *std_it);

  it = ms.lower_bound(6);
  std_it = std_ms.lower_bound(6);
  EXPECT_EQ(it == ms.end(), std_it == std_ms.end());
}

// Тест на метод upper_bound
TEST(MultisetTest, UpperBound) {
  multiset<int> ms{1, 2, 2, 3, 4, 4, 5};
  std::multiset<int> std_ms{1, 2, 2, 3, 4, 4, 5};

  auto it = ms.upper_bound(3);
  auto std_it = std_ms.upper_bound(3);

  EXPECT_EQ(*it, *std_it);

  it = ms.upper_bound(5);
  std_it = std_ms.upper_bound(5);
  EXPECT_EQ(it == ms.end(), std_it == std_ms.end());
}

// Тест на итераторы
TEST(MultisetTest, Iterators) {
  multiset<int> ms{1, 2, 2, 3};
  std::multiset<int> std_ms{1, 2, 2, 3};

  auto it = ms.begin();
  auto std_it = std_ms.begin();

  while (it != ms.end() && std_it != std_ms.end()) {
    EXPECT_EQ(*it, *std_it);
    ++it;
    ++std_it;
  }

  EXPECT_EQ(it == ms.end(), std_it == std_ms.end());
}

// Тест на константные итераторы
TEST(MultisetTest, ConstIterators) {
  const multiset<int> ms{1, 2, 2, 3};
  const std::multiset<int> std_ms{1, 2, 2, 3};

  auto it = ms.begin();
  auto std_it = std_ms.begin();

  while (it != ms.end() && std_it != std_ms.end()) {
    EXPECT_EQ(*it, *std_it);
    ++it;
    ++std_it;
  }

  EXPECT_EQ(it == ms.end(), std_it == std_ms.end());
}

TEST(MultisetTest, MoveAssignmentOperator) {
  multiset<int> a;
  a.insert(1);
  a.insert(2);
  a.insert(3);

  multiset<int> b;
  b.insert(4);
  b.insert(5);

  b = std::move(a);

  EXPECT_EQ(b.size(), 3);
  EXPECT_TRUE(b.contains(1));
  EXPECT_TRUE(b.contains(2));
  EXPECT_TRUE(b.contains(3));

  EXPECT_TRUE(a.empty());
}

TEST(MultisetTest, CopyAssignmentOperator) {
  multiset<int> a;
  a.insert(1);
  a.insert(2);
  a.insert(3);

  multiset<int> b;
  b.insert(4);
  b.insert(5);

  b = a;

  EXPECT_EQ(b.size(), 3);
  EXPECT_TRUE(b.contains(1));
  EXPECT_TRUE(b.contains(2));
  EXPECT_TRUE(b.contains(3));

  EXPECT_EQ(a.size(), 3);
  EXPECT_TRUE(a.contains(1));
  EXPECT_TRUE(a.contains(2));
  EXPECT_TRUE(a.contains(3));
}
// Тест на метод max_size
TEST(MultisetTest, MaxSizeComparison) {
  multiset<int> ms;
  std::multiset<int> std_ms;

  EXPECT_GT(ms.max_size(), 0);
  EXPECT_GT(std_ms.max_size(), 0);
}

// Тест на метод swap с пустыми контейнерами
TEST(MultisetTest, SwapEmpty) {
  multiset<int> ms1;
  multiset<int> ms2;
  std::multiset<int> std_ms1;
  std::multiset<int> std_ms2;

  ms1.swap(ms2);
  std_ms1.swap(std_ms2);

  EXPECT_TRUE(ms1.empty());
  EXPECT_TRUE(ms2.empty());
}

// Тест на метод merge с пустым контейнером
TEST(MultisetTest, MergeEmpty) {
  multiset<int> ms1{1, 2, 2};
  multiset<int> ms2;
  std::multiset<int> std_ms1{1, 2, 2};
  std::multiset<int> std_ms2;

  ms1.merge(ms2);
  std_ms1.merge(std_ms2);

  EXPECT_EQ(ms1.size(), std_ms1.size());
  EXPECT_TRUE(ms2.empty());
}

// Тест на метод insert с дубликатами
TEST(MultisetTest, InsertDuplicates) {
  multiset<int> ms;
  std::multiset<int> std_ms;

  for (int i = 0; i < 10; ++i) {
    ms.insert(2);
    std_ms.insert(2);
  }
  for (int i = 0; i < 10; ++i) {
    ms.insert(5);
    std_ms.insert(5);
  }
  EXPECT_EQ(ms.size(), std_ms.size());
  EXPECT_EQ(ms.count(5), std_ms.count(5));
  EXPECT_EQ(ms.count(2), std_ms.count(2));
}
struct Point {
  int x, y;

  bool operator==(const Point& other) const {
    return x == other.x && y == other.y;
  }

  bool operator<(const Point& other) const {
    if (x != other.x) return x < other.x;
    return y < other.y;
  }

  bool operator>(const Point& other) const {
    if (x != other.x) return x > other.x;
    return y > other.y;
  }

  bool operator<=(const Point& other) const {
    return *this < other || *this == other;
  }

  bool operator>=(const Point& other) const {
    return *this > other || *this == other;
  }

  bool operator!=(const Point& other) const { return !(*this == other); }
};

TEST(MultisetTest, RightRotation) {
  multiset<Point> ms;

  ms.insert({3, 3});
  ms.insert({2, 2});
  ms.insert({1, 1});

  EXPECT_TRUE(ms.contains({1, 1}));
  EXPECT_TRUE(ms.contains({2, 2}));
  EXPECT_TRUE(ms.contains({3, 3}));
}

TEST(MultisetTest, RedUncleHandling) {
  multiset<Point> ms;

  ms.insert({5, 5});
  ms.insert({3, 3});
  ms.insert({7, 7});
  ms.insert({6, 6});
  ms.insert({8, 8});

  EXPECT_TRUE(ms.contains({5, 5}));
  EXPECT_TRUE(ms.contains({3, 3}));
  EXPECT_TRUE(ms.contains({7, 7}));
  EXPECT_TRUE(ms.contains({6, 6}));
  EXPECT_TRUE(ms.contains({8, 8}));
}

TEST(MultisetTest, FixInsertLeftCase) {
  multiset<Point> ms;

  ms.insert({10, 10});
  ms.insert({5, 5});
  ms.insert({15, 15});
  ms.insert({12, 12});
  ms.insert({17, 17});
  ms.insert({11, 11});

  EXPECT_TRUE(ms.contains({10, 10}));
  EXPECT_TRUE(ms.contains({5, 5}));
  EXPECT_TRUE(ms.contains({15, 15}));
  EXPECT_TRUE(ms.contains({12, 12}));
  EXPECT_TRUE(ms.contains({17, 17}));
  EXPECT_TRUE(ms.contains({11, 11}));
}

TEST(MultisetTest, BlackUncleHandling) {
  multiset<Point> ms;

  ms.insert({20, 20});
  ms.insert({10, 10});
  ms.insert({30, 30});
  ms.insert({5, 5});
  ms.insert({15, 15});
  ms.insert({25, 25});
  ms.insert({35, 35});
  ms.insert({12, 12});

  EXPECT_TRUE(ms.contains({20, 20}));
  EXPECT_TRUE(ms.contains({10, 10}));
  EXPECT_TRUE(ms.contains({30, 30}));
  EXPECT_TRUE(ms.contains({5, 5}));
  EXPECT_TRUE(ms.contains({15, 15}));
  EXPECT_TRUE(ms.contains({25, 25}));
  EXPECT_TRUE(ms.contains({35, 35}));
  EXPECT_TRUE(ms.contains({12, 12}));
}

// Тест с пользовательским типом данных
TEST(MultisetTest, CustomType) {
  multiset<Point> ms{{1, 2}, {1, 2}, {3, 4}};
  std::multiset<Point> std_ms{{1, 2}, {1, 2}, {3, 4}};

  EXPECT_EQ(ms.size(), std_ms.size());
  EXPECT_EQ(ms.count({1, 2}), std_ms.count({1, 2}));
  EXPECT_FALSE(ms.contains({2, 3}));
}
// Тест на вставку большого количества элементов
TEST(MultisetTest, InsertManyElements) {
  multiset<int> ms;
  std::multiset<int> std_ms;

  for (int i = 0; i < 1000; ++i) {
    ms.insert(i % 10);
    std_ms.insert(i % 10);
  }

  EXPECT_EQ(ms.size(), std_ms.size());
  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(ms.count(i), std_ms.count(i));
  }
}
// Тесты на проверку InsertMany
TEST(MultisetTest, InsertManyUnique) {
  multiset<int> s;
  auto results = s.insert_many(1, 2, 3);

  EXPECT_EQ(results.size(), 3);
  EXPECT_EQ(s.size(), 3);
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(2));
  EXPECT_TRUE(s.contains(3));
}

TEST(MultisetTest, InsertManyDuplicates) {
  multiset<int> s;
  s.insert(2);

  auto results = s.insert_many(1, 2, 3);

  EXPECT_EQ(results.size(), 3);
  EXPECT_EQ(s.size(), 4);
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(2));
  EXPECT_TRUE(s.contains(3));
}

TEST(MultisetTest, InsertManyEmpty) {
  multiset<int> s;
  auto results = s.insert_many();

  EXPECT_TRUE(results.empty());
  EXPECT_TRUE(s.empty());
}

TEST(MultisetTest, InsertManyLarge) {
  multiset<int> s;
  std::vector<int> elements = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  auto results = s.insert_many(
      elements[0], elements[1], elements[2], elements[3], elements[4],
      elements[5], elements[6], elements[7], elements[8], elements[9]);

  EXPECT_EQ(results.size(), 10);
  EXPECT_EQ(s.size(), 10);
  for (const auto& element : elements) {
    EXPECT_TRUE(s.contains(element));
  }
}

TEST(MultisetTest, InsertManyDifferentTypes) {
  multiset<std::string> s;
  auto results = s.insert_many("apple", "banana", "cherry");

  EXPECT_EQ(results.size(), 3);
  EXPECT_EQ(s.size(), 3);
  EXPECT_TRUE(s.contains("apple"));
  EXPECT_TRUE(s.contains("banana"));
  EXPECT_TRUE(s.contains("cherry"));
}

TEST(MultisetTest, InsertManyRvalue) {
  multiset<std::string> s;
  auto results = s.insert_many(std::string("apple"), std::string("banana"),
                               std::string("cherry"));

  EXPECT_EQ(results.size(), 3);
  EXPECT_EQ(s.size(), 3);
  EXPECT_TRUE(s.contains("apple"));
  EXPECT_TRUE(s.contains("banana"));
  EXPECT_TRUE(s.contains("cherry"));
}

TEST(MultisetTest, InsertManyLvalue) {
  multiset<int> s;
  int a = 1, b = 2, c = 3;
  auto results = s.insert_many(a, b, c);

  EXPECT_EQ(results.size(), 3);
  EXPECT_EQ(s.size(), 3);
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(2));
  EXPECT_TRUE(s.contains(3));
}

TEST(MultisetTest, InsertManyMixed) {
  multiset<std::string> s;
  std::string apple = "apple";
  auto results = s.insert_many(apple, std::string("banana"), "cherry");

  EXPECT_EQ(results.size(), 3);
  EXPECT_EQ(s.size(), 3);
  EXPECT_TRUE(s.contains("apple"));
  EXPECT_TRUE(s.contains("banana"));
  EXPECT_TRUE(s.contains("cherry"));
}
