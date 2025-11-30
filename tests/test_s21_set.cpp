
#include "tests.h"

using namespace s21;

// Тест конструктора по умолчанию
TEST(SetTest, DefaultConstructor) {
  set<int> s;
  std::set<int> std_s;
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), std_s.size());
}

// Тест конструктора с initializer_list
TEST(SetTest, InitializerListConstructor) {
  set<int> s{1, 2, 3};
  std::set<int> std_s{1, 2, 3};
  EXPECT_FALSE(s.empty());
  EXPECT_EQ(s.size(), std_s.size());
}

// Тест конструктора копирования
TEST(SetTest, CopyConstructor) {
  set<int> original{1, 2, 3};
  std::set<int> std_original{1, 2, 3};
  set<int> copy(original);
  std::set<int> std_copy(std_original);
  EXPECT_EQ(copy.size(), std_copy.size());
  EXPECT_EQ(copy.find(1) != copy.end(), std_copy.find(1) != std_copy.end());
  EXPECT_EQ(copy.find(2) != copy.end(), std_copy.find(2) != std_copy.end());
  EXPECT_EQ(copy.find(3) != copy.end(), std_copy.find(3) != std_copy.end());
}

// Тест конструктора перемещения
TEST(SetTest, MoveConstructor) {
  set<int> original = {1, 2, 3};
  std::set<int> std_original = {1, 2, 3};
  set<int> moved(std::move(original));
  std::set<int> std_moved(std::move(std_original));
  EXPECT_EQ(moved.size(), std_moved.size());
  EXPECT_EQ(original.size(), std_original.size());
}

// Тест вставки элемента
TEST(SetTest, Insert) {
  set<int> s;
  std::set<int> std_s;
  auto result1 = s.insert(5);
  auto std_result1 = std_s.insert(5);
  EXPECT_EQ(result1.second, std_result1.second);
  EXPECT_EQ(s.size(), std_s.size());

  auto result2 = s.insert(5);
  auto std_result2 = std_s.insert(5);
  EXPECT_EQ(result2.second, std_result2.second);
  EXPECT_EQ(s.size(), std_s.size());

  auto result3 = s.insert(10);
  auto std_result3 = std_s.insert(10);
  EXPECT_EQ(result3.second, std_result3.second);
  EXPECT_EQ(s.size(), std_s.size());
}

// Тест поиска элемента
TEST(SetTest, Find) {
  set<int> s{1, 2, 3};
  std::set<int> std_s{1, 2, 3};
  EXPECT_EQ(*s.find(2), *std_s.find(2));
  EXPECT_EQ(s.find(4) == s.end(), std_s.find(4) == std_s.end());
}

// Тест удаления элемента
TEST(SetTest, Erase) {
  set<int> s{1, 2, 3, 4};
  std::set<int> std_s{1, 2, 3, 4};
  s.erase(s.find(2));
  std_s.erase(std_s.find(2));
  EXPECT_EQ(s.size(), std_s.size());
  EXPECT_EQ(s.find(2) == s.end(), std_s.find(2) == std_s.end());

  s.erase(s.find(1));
  std_s.erase(std_s.find(1));
  EXPECT_EQ(s.size(), std_s.size());
  EXPECT_EQ(s.find(1) == s.end(), std_s.find(1) == std_s.end());
}

// Тест на пустоту контейнера
TEST(SetTest, Empty) {
  set<int> s;
  std::set<int> std_s;
  EXPECT_EQ(s.empty(), std_s.empty());
  s.insert(10);
  std_s.insert(10);
  EXPECT_EQ(s.empty(), std_s.empty());
}

// Тест очистки контейнера
TEST(SetTest, Clear) {
  set<int> s{1, 2, 3, 4};
  std::set<int> std_s{1, 2, 3, 4};
  s.clear();
  std_s.clear();
  EXPECT_EQ(s.empty(), std_s.empty());
  EXPECT_EQ(s.size(), std_s.size());
}

// Тест метода swap
TEST(SetTest, Swap) {
  set<int> s1{1, 2, 3};
  set<int> s2{4, 5, 6};
  std::set<int> std_s1{1, 2, 3};
  std::set<int> std_s2{4, 5, 6};

  s1.swap(s2);
  std_s1.swap(std_s2);

  EXPECT_EQ(s1.size(), std_s1.size());
  EXPECT_EQ(s2.size(), std_s2.size());
  EXPECT_EQ(*s1.find(4), *std_s1.find(4));
  EXPECT_EQ(*s2.find(1), *std_s2.find(1));
}

// Тест метода merge
TEST(SetTest, Merge) {
  set<int> s1{1, 2, 3};
  set<int> s2{3, 4, 5};
  std::set<int> std_s1{1, 2, 3};
  std::set<int> std_s2{3, 4, 5};

  s1.merge(s2);
  std_s1.merge(std_s2);

  EXPECT_EQ(s1.size(), std_s1.size());
  EXPECT_EQ(s2.size(), std_s2.size());
  EXPECT_EQ(*s1.find(4), *std_s1.find(4));
  EXPECT_EQ(s2.find(3) == s2.end(), std_s2.find(3) == std_s2.end());
}

// Тест метода contains
TEST(SetTest, Contains) {
  set<int> s{1, 2, 3};
  EXPECT_TRUE(s.contains(2));
  EXPECT_FALSE(s.contains(4));
}

// Тест метода max_size
TEST(SetTest, MaxSize) {
  set<int> s;
  std::set<int> std_s;
  EXPECT_GT(s.max_size(), 0);
  EXPECT_GT(std_s.max_size(), 0);
}

// Тест константных итераторов
TEST(SetTest, ConstIterator) {
  const set<int> s{1, 2, 3};
  const std::set<int> std_s{1, 2, 3};

  auto it = s.begin();
  auto std_it = std_s.begin();

  EXPECT_EQ(*it, *std_it);
  ++it;
  ++std_it;
  EXPECT_EQ(*it, *std_it);
}

// Тест с пользовательским типом данных

// Тест на вставку дубликатов
TEST(SetTest, InsertDuplicate) {
  set<int> s;
  std::set<int> std_s;

  s.insert(1);
  std_s.insert(1);

  EXPECT_EQ(s.size(), std_s.size());

  s.insert(1);
  std_s.insert(1);

  EXPECT_EQ(s.size(), std_s.size());
}

// Тест на корректность итераторов после перемещения
TEST(SetTest, IteratorValidityAfterMove) {
  set<int> s{1, 2, 3};
  std::set<int> std_s{1, 2, 3};

  auto it = s.find(2);
  auto std_it = std_s.find(2);

  set<int> moved(std::move(s));
  std::set<int> std_moved(std::move(std_s));

  EXPECT_EQ(*it, *std_it);
}

// Тест на корректность итераторов после слияния
TEST(SetTest, IteratorValidityAfterMerge) {
  set<int> s1{1, 2, 3};
  set<int> s2{4, 5, 6};
  std::set<int> std_s1{1, 2, 3};
  std::set<int> std_s2{4, 5, 6};

  auto it = s1.find(2);
  auto std_it = std_s1.find(2);

  s1.merge(s2);
  std_s1.merge(std_s2);

  EXPECT_EQ(*it, *std_it);
}

// Тест на корректность итераторов после удаления
TEST(SetTest, IteratorValidityAfterErase) {
  set<int> s{1, 2, 3, 4, 5};
  std::set<int> std_s{1, 2, 3, 4, 5};

  auto it = s.find(3);
  auto std_it = std_s.find(3);

  s.erase(s.find(2));
  std_s.erase(std_s.find(2));

  s.erase(s.find(4));
  std_s.erase(std_s.find(4));

  EXPECT_EQ(*it, *std_it);
}

// Тест на корректность итераторов после обмена
TEST(SetTest, IteratorValidityAfterSwap) {
  set<int> s1{1, 2, 3};
  set<int> s2{4, 5, 6};
  std::set<int> std_s1{1, 2, 3};
  std::set<int> std_s2{4, 5, 6};

  auto it1 = s1.find(2);
  auto it2 = s2.find(5);
  auto std_it1 = std_s1.find(2);
  auto std_it2 = std_s2.find(5);

  s1.swap(s2);
  std_s1.swap(std_s2);

  EXPECT_EQ(*it1, *std_it1);
  EXPECT_EQ(*it2, *std_it2);
}

// Тест на корректность итераторов после копирования
TEST(SetTest, IteratorValidityAfterCopy) {
  set<int> s1{1, 2, 3};
  std::set<int> std_s1{1, 2, 3};

  auto it = s1.find(2);
  auto std_it = std_s1.find(2);

  set<int> s2(s1);
  std::set<int> std_s2(std_s1);

  EXPECT_EQ(*it, *std_it);
}

// Тест на корректность итераторов после присваивания
TEST(SetTest, IteratorValidityAfterAssignment) {
  set<int> s1{1, 2, 3};
  set<int> s2;
  std::set<int> std_s1{1, 2, 3};
  std::set<int> std_s2;

  auto it = s1.find(2);
  auto std_it = std_s1.find(2);

  s2 = s1;
  std_s2 = std_s1;

  EXPECT_EQ(*it, *std_it);
}

// Тест на корректность итераторов после вставки
TEST(SetTest, IteratorValidityAfterInsert) {
  set<int> s{1, 2, 3};
  std::set<int> std_s{1, 2, 3};

  auto it = s.find(2);
  auto std_it = std_s.find(2);

  s.insert(4);
  std_s.insert(4);

  EXPECT_EQ(*it, *std_it);
}

// Тест на корректность итераторов после удаления всех элементов
TEST(SetTest, IteratorValidityAfterEraseAll) {
  set<int> s{1, 2, 3};
  std::set<int> std_s{1, 2, 3};

  s.erase(s.find(1));
  std_s.erase(std_s.find(1));

  s.erase(s.find(2));
  std_s.erase(std_s.find(2));

  s.erase(s.find(3));
  std_s.erase(std_s.find(3));

  // Проверяем, что контейнеры пусты
  EXPECT_TRUE(s.empty());
  EXPECT_TRUE(std_s.empty());
}

// Тест на корректность итераторов после перемещения с помощью std::move
TEST(SetTest, IteratorValidityAfterStdMove) {
  set<int> s1{1, 2, 3};
  std::set<int> std_s1{1, 2, 3};

  auto it = s1.find(2);
  auto std_it = std_s1.find(2);

  set<int> s2(std::move(s1));
  std::set<int> std_s2(std::move(std_s1));

  EXPECT_EQ(*it, *std_it);
}

// Тест на корректность итераторов после слияния с пустым контейнером
TEST(SetTest, IteratorValidityAfterMergeWithEmpty) {
  set<int> s1{1, 2, 3};
  set<int> s2;
  std::set<int> std_s1{1, 2, 3};
  std::set<int> std_s2;

  auto it = s1.find(2);
  auto std_it = std_s1.find(2);

  s1.merge(s2);
  std_s1.merge(std_s2);

  EXPECT_EQ(*it, *std_it);
}

// Тест на корректность итераторов после слияния с контейнером, содержащим
// дубликаты
TEST(SetTest, IteratorValidityAfterMergeWithDuplicates) {
  set<int> s1{1, 2, 3};
  set<int> s2{2, 3, 4};
  std::set<int> std_s1{1, 2, 3};
  std::set<int> std_s2{2, 3, 4};

  auto it = s1.find(2);
  auto std_it = std_s1.find(2);

  s1.merge(s2);
  std_s1.merge(std_s2);

  EXPECT_EQ(*it, *std_it);
}

// Тесты на проверку InsertMany
TEST(SetTest, InsertManyUnique) {
  set<int> s;
  auto results = s.insert_many(1, 2, 3);

  EXPECT_EQ(results.size(), 3);
  EXPECT_TRUE(results[0].second);
  EXPECT_TRUE(results[1].second);
  EXPECT_TRUE(results[2].second);

  EXPECT_EQ(s.size(), 3);
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(2));
  EXPECT_TRUE(s.contains(3));
}

TEST(SetTest, InsertManyDuplicates) {
  set<int> s;
  s.insert(2);

  auto results = s.insert_many(1, 2, 3);

  EXPECT_EQ(results.size(), 3);
  EXPECT_TRUE(results[0].second);
  EXPECT_FALSE(results[1].second);
  EXPECT_TRUE(results[2].second);

  EXPECT_EQ(s.size(), 3);
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(2));
  EXPECT_TRUE(s.contains(3));
}

TEST(SetTest, InsertManyEmpty) {
  set<int> s;
  auto results = s.insert_many();

  EXPECT_TRUE(results.empty());
  EXPECT_TRUE(s.empty());
}
TEST(SetTest, InsertManyLarge) {
  set<int> s;
  std::vector<int> elements = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  auto results = s.insert_many(
      elements[0], elements[1], elements[2], elements[3], elements[4],
      elements[5], elements[6], elements[7], elements[8], elements[9]);

  EXPECT_EQ(results.size(), 10);
  for (const auto& result : results) {
    EXPECT_TRUE(result.second);
  }

  EXPECT_EQ(s.size(), 10);
  for (const auto& element : elements) {
    EXPECT_TRUE(s.contains(element));
  }
}

TEST(SetTest, InsertManyDifferentTypes) {
  set<std::string> s;
  auto results = s.insert_many("apple", "banana", "cherry");

  EXPECT_EQ(results.size(), 3);
  EXPECT_TRUE(results[0].second);
  EXPECT_TRUE(results[1].second);
  EXPECT_TRUE(results[2].second);

  EXPECT_EQ(s.size(), 3);
  EXPECT_TRUE(s.contains("apple"));
  EXPECT_TRUE(s.contains("banana"));
  EXPECT_TRUE(s.contains("cherry"));
}
TEST(SetTest, MoveAssignmentOperator) {
  set<int> a;
  a.insert(1);
  a.insert(2);
  a.insert(3);

  set<int> b;
  b.insert(4);
  b.insert(5);

  b = std::move(a);

  EXPECT_EQ(b.size(), 3);
  EXPECT_TRUE(b.contains(1));
  EXPECT_TRUE(b.contains(2));
  EXPECT_TRUE(b.contains(3));

  EXPECT_TRUE(a.empty());
}
// const ==
TEST(SetTest, ConstIteratorEqualityOperator) {
  set<int> a;
  a.insert(10);
  a.insert(20);
  a.insert(30);

  const set<int>& const_a = a;

  auto it1 = const_a.begin();
  auto it2 = const_a.begin();
  auto it3 = it1;
  auto it4 = ++const_a.begin();
  EXPECT_TRUE(it1 == it2);
  EXPECT_TRUE(it1 == it3);
  EXPECT_FALSE(it1 == it4);

  set<int> b;
  b.insert(10);
  const set<int>& const_b = b;
  auto it5 = const_b.begin();

  EXPECT_FALSE(it1 == it5);
}
TEST(SetTest, FindExistingElement) {
  set<int> s;
  s.insert(10);
  s.insert(20);
  s.insert(30);

  auto it = s.find(20);

  EXPECT_NE(it, s.end());
  EXPECT_EQ(*it, 20);
}
TEST(SetTest, InsertManyRvalue) {
  set<std::string> s;
  auto results = s.insert_many(std::string("apple"), std::string("banana"),
                               std::string("cherry"));

  EXPECT_EQ(results.size(), 3);
  EXPECT_TRUE(results[0].second);
  EXPECT_TRUE(results[1].second);
  EXPECT_TRUE(results[2].second);

  EXPECT_EQ(s.size(), 3);
  EXPECT_TRUE(s.contains("apple"));
  EXPECT_TRUE(s.contains("banana"));
  EXPECT_TRUE(s.contains("cherry"));
}

TEST(SetTest, InsertManyLvalue) {
  set<int> s;
  int a = 1, b = 2, c = 3;
  auto results = s.insert_many(a, b, c);

  EXPECT_EQ(results.size(), 3);
  EXPECT_TRUE(results[0].second);
  EXPECT_TRUE(results[1].second);
  EXPECT_TRUE(results[2].second);

  EXPECT_EQ(s.size(), 3);
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(2));
  EXPECT_TRUE(s.contains(3));
}

TEST(SetTest, InsertManyMixed) {
  set<std::string> s;
  std::string apple = "apple";
  auto results = s.insert_many(apple, std::string("banana"), "cherry");

  EXPECT_EQ(results.size(), 3);
  EXPECT_TRUE(results[0].second);
  EXPECT_TRUE(results[1].second);
  EXPECT_TRUE(results[2].second);

  EXPECT_EQ(s.size(), 3);
  EXPECT_TRUE(s.contains("apple"));
  EXPECT_TRUE(s.contains("banana"));
  EXPECT_TRUE(s.contains("cherry"));
}
struct Point {
  int x, y;

  // Оператор сравнения для упорядочивания
  bool operator<(const Point& other) const {
    return x < other.x || (x == other.x && y < other.y);
  }

  // Оператор равенства
  bool operator==(const Point& other) const {
    return x == other.x && y == other.y;
  }
};
// Тест с пользовательским типом данных
TEST(SetTest, CustomType) {
  set<Point> s{{1, 2}, {3, 4}};
  std::set<Point> std_s{{1, 2}, {3, 4}};

  EXPECT_EQ(s.size(), std_s.size());
  EXPECT_TRUE(s.contains({1, 2}));
  EXPECT_FALSE(s.contains({2, 3}));
}
TEST(SetTest, CustomType_InsertAndContains) {
  set<Point> s;
  std::set<Point> std_s;

  // Вставляем точки
  s.insert({1, 2});
  s.insert({3, 4});
  s.insert({2, 3});
  s.insert({5, 6});
  s.insert({4, 5});

  std_s.insert({1, 2});
  std_s.insert({3, 4});
  std_s.insert({2, 3});
  std_s.insert({5, 6});
  std_s.insert({4, 5});

  EXPECT_EQ(s.size(), std_s.size());

  // Проверяем наличие элементов
  EXPECT_TRUE(s.contains({1, 2}));
  EXPECT_TRUE(s.contains({3, 4}));
  EXPECT_TRUE(s.contains({2, 3}));
  EXPECT_TRUE(s.contains({5, 6}));
  EXPECT_TRUE(s.contains({4, 5}));
  EXPECT_FALSE(s.contains({0, 0}));
  EXPECT_FALSE(s.contains({6, 7}));
}

TEST(SetTest, CustomType_Erase) {
  set<Point> s{{1, 2}, {3, 4}, {2, 3}, {5, 6}, {4, 5}};
  std::set<Point> std_s{{1, 2}, {3, 4}, {2, 3}, {5, 6}, {4, 5}};

  // Используем итераторы для удаления элементов
  auto it = s.find({3, 4});
  if (it != s.end()) {
    s.erase(it);
  }
  auto std_it = std_s.find({3, 4});
  if (std_it != std_s.end()) {
    std_s.erase(std_it);
  }
  EXPECT_EQ(s.size(), std_s.size());

  it = s.find({1, 2});
  if (it != s.end()) {
    s.erase(it);
  }
  std_it = std_s.find({1, 2});
  if (std_it != std_s.end()) {
    std_s.erase(std_it);
  }
  EXPECT_EQ(s.size(), std_s.size());

  it = s.find({4, 5});
  if (it != s.end()) {
    s.erase(it);
  }
  std_it = std_s.find({4, 5});
  if (std_it != std_s.end()) {
    std_s.erase(std_it);
  }
  EXPECT_EQ(s.size(), std_s.size());

  EXPECT_FALSE(s.contains({3, 4}));
  EXPECT_FALSE(s.contains({1, 2}));
  EXPECT_FALSE(s.contains({4, 5}));
}
TEST(SetTest, CustomType_OrderCheck) {
  set<Point> s{{4, 5}, {2, 3}, {5, 6}, {1, 2}, {3, 4}};
  std::set<Point> std_s{{4, 5}, {2, 3}, {5, 6}, {1, 2}, {3, 4}};

  auto it = s.begin();
  auto std_it = std_s.begin();

  while (it != s.end() && std_it != std_s.end()) {
    EXPECT_EQ(*it, *std_it);
    ++it;
    ++std_it;
  }
}
TEST(SetTest, CustomType_RotationCheck) {
  set<Point> s;

  s.insert({1, 1});
  s.insert({2, 2});
  s.insert({3, 3});

  EXPECT_TRUE(s.contains({1, 1}));
  EXPECT_TRUE(s.contains({2, 2}));
  EXPECT_TRUE(s.contains({3, 3}));

  set<Point> s2;
  s2.insert({3, 3});
  s2.insert({2, 2});
  s2.insert({1, 1});

  EXPECT_TRUE(s2.contains({1, 1}));
  EXPECT_TRUE(s2.contains({2, 2}));
  EXPECT_TRUE(s2.contains({3, 3}));
}

TEST(SetTest, CustomType_RedUncleHandling) {
  set<Point> s;

  s.insert({5, 5});
  s.insert({3, 3});
  s.insert({7, 7});
  s.insert({6, 6});
  s.insert({8, 8});

  EXPECT_TRUE(s.contains({5, 5}));
  EXPECT_TRUE(s.contains({3, 3}));
  EXPECT_TRUE(s.contains({7, 7}));
  EXPECT_TRUE(s.contains({6, 6}));
  EXPECT_TRUE(s.contains({8, 8}));
}

TEST(SetTest, CustomType_BlackUncleHandling) {
  set<Point> s;

  s.insert({10, 10});
  s.insert({5, 5});
  s.insert({15, 15});
  s.insert({12, 12});
  s.insert({17, 17});
  s.insert({11, 11});

  EXPECT_TRUE(s.contains({10, 10}));
  EXPECT_TRUE(s.contains({5, 5}));
  EXPECT_TRUE(s.contains({15, 15}));
  EXPECT_TRUE(s.contains({12, 12}));
  EXPECT_TRUE(s.contains({17, 17}));
  EXPECT_TRUE(s.contains({11, 11}));
}

TEST(SetTest, CustomType_TreeStructureAfterInsert) {
  set<Point> s{{4, 4}, {2, 2}, {6, 6}, {1, 1}, {3, 3}, {5, 5}, {7, 7}};

  std::vector<Point> expected_order{{1, 1}, {2, 2}, {3, 3}, {4, 4},
                                    {5, 5}, {6, 6}, {7, 7}};

  auto it = s.begin();
  for (const auto& expected : expected_order) {
    EXPECT_EQ(*it, expected);
    ++it;
  }
}

TEST(SetTest, CustomType_TreeStructureAfterErase) {
  set<Point> s{{4, 4}, {2, 2}, {6, 6}, {1, 1}, {3, 3}, {5, 5}, {7, 7}};

  auto it = s.find({3, 3});
  if (it != s.end()) {
    s.erase(it);
  }
  it = s.find({4, 4});
  if (it != s.end()) {
    s.erase(it);
  }
  it = s.find({6, 6});
  if (it != s.end()) {
    s.erase(it);
  }

  std::vector<Point> expected_order{{1, 1}, {2, 2}, {5, 5}, {7, 7}};

  it = s.begin();
  for (const auto& expected : expected_order) {
    EXPECT_EQ(*it, expected);
    ++it;
  }

  EXPECT_FALSE(s.contains({3, 3}));
  EXPECT_FALSE(s.contains({6, 6}));
  EXPECT_FALSE(s.contains({4, 4}));
}

TEST(SetTest, LeftRotation) {
  set<Point> s;

  s.insert({1, 1});
  s.insert({2, 2});
  s.insert({3, 3});

  EXPECT_TRUE(s.contains({1, 1}));
  EXPECT_TRUE(s.contains({2, 2}));
  EXPECT_TRUE(s.contains({3, 3}));
}

TEST(SetTest, RightRotation) {
  set<Point> s;

  s.insert({3, 3});
  s.insert({2, 2});
  s.insert({1, 1});

  EXPECT_TRUE(s.contains({1, 1}));
  EXPECT_TRUE(s.contains({2, 2}));
  EXPECT_TRUE(s.contains({3, 3}));
}

TEST(SetTest, RedUncleHandling) {
  set<Point> s;

  s.insert({5, 5});
  s.insert({3, 3});
  s.insert({7, 7});
  s.insert({6, 6});
  s.insert({8, 8});  // Дядя 8 красный

  EXPECT_TRUE(s.contains({5, 5}));
  EXPECT_TRUE(s.contains({3, 3}));
  EXPECT_TRUE(s.contains({7, 7}));
  EXPECT_TRUE(s.contains({6, 6}));
  EXPECT_TRUE(s.contains({8, 8}));
}
TEST(SetTest, BlackUncleHandling) {
  set<Point> s;

  s.insert({10, 10});
  s.insert({5, 5});
  s.insert({15, 15});
  s.insert({12, 12});
  s.insert({17, 17});
  s.insert({11, 11});

  EXPECT_TRUE(s.contains({10, 10}));
  EXPECT_TRUE(s.contains({5, 5}));
  EXPECT_TRUE(s.contains({15, 15}));
  EXPECT_TRUE(s.contains({12, 12}));
  EXPECT_TRUE(s.contains({17, 17}));
  EXPECT_TRUE(s.contains({11, 11}));
}
