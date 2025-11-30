#include "tests.h"
using namespace s21;

// Тест конструктора по умолчанию
TEST(RBTreeTest, DefaultConstructor) {
  RBTree<int> tree;
  EXPECT_TRUE(tree.size() == 0);
  EXPECT_TRUE(tree.find(42) == nullptr);
}

// Тест вставки элемента
TEST(RBTreeTest, Insert) {
  RBTree<int> tree;
  tree.insert(10);
  tree.insert(20);
  tree.insert(30);

  EXPECT_TRUE(tree.size() == 3);
  EXPECT_TRUE(tree.find(10) != nullptr);
  EXPECT_TRUE(tree.find(20) != nullptr);
  EXPECT_TRUE(tree.find(30) != nullptr);
  EXPECT_TRUE(tree.find(40) == nullptr);
}

// Тест поиска элемента
TEST(RBTreeTest, Find) {
  RBTree<int> tree;
  tree.insert(5);
  tree.insert(15);
  tree.insert(25);

  auto* node = tree.find(15);
  EXPECT_TRUE(node != nullptr);
  EXPECT_EQ(node->data, 15);

  node = tree.find(100);
  EXPECT_TRUE(node == nullptr);
}

// Тест проверки балансировки дерева
TEST(RBTreeTest, BalanceAfterInsert) {
  RBTree<int> tree;
  tree.insert(10);
  tree.insert(20);
  tree.insert(30);
  tree.insert(40);
  tree.insert(50);

  EXPECT_TRUE(tree.find(10)->color == Color::BLACK);
}

// Тест удаления элемента
TEST(RBTreeTest, Erase) {
  RBTree<int> tree;
  tree.insert(10);
  tree.insert(20);
  tree.insert(30);

  EXPECT_TRUE(tree.size() == 3);
  EXPECT_TRUE(tree.find(20) != nullptr);

  tree.erase(20);

  EXPECT_TRUE(tree.size() == 2);
  EXPECT_TRUE(tree.find(20) == nullptr);
}

// Тест очистки дерева
TEST(RBTreeTest, Clear) {
  RBTree<int> tree;
  tree.insert(10);
  tree.insert(20);
  tree.insert(30);

  EXPECT_TRUE(tree.size() == 3);
  tree.clear();

  EXPECT_TRUE(tree.size() == 0);
  EXPECT_TRUE(tree.find(10) == nullptr);
}

// Тест на дубликаты
TEST(RBTreeTest, Duplicates) {
  RBTree<int> tree;
  tree.insert(10);
  tree.insert(10);

  EXPECT_TRUE(tree.size() == 1);
  EXPECT_TRUE(tree.find(10) != nullptr);
}

// Тест на вставку большого количества элементов
TEST(RBTreeTest, LargeInsert) {
  RBTree<int> tree;
  for (int i = 0; i < 1000; ++i) {
    tree.insert(i);
  }

  EXPECT_TRUE(tree.size() == 1000);
  EXPECT_TRUE(tree.find(500) != nullptr);
  EXPECT_TRUE(tree.find(1000) == nullptr);
}

// Тест функции contains
TEST(RBTreeTest, Contains) {
  RBTree<int> tree;
  tree.insert(15);
  tree.insert(25);
  EXPECT_TRUE(tree.contains(15));
  EXPECT_TRUE(tree.contains(25));
  EXPECT_FALSE(tree.contains(10));
}

// Тест удаления несуществующего элемента
TEST(RBTreeTest, EraseNonExistent) {
  RBTree<int> tree;
  tree.insert(10);
  tree.insert(20);
  size_t oldSize = tree.size();
  tree.erase(100);
  EXPECT_EQ(tree.size(), oldSize);
}

// Тест очистки пустого дерева
TEST(RBTreeTest, ClearEmptyTree) {
  RBTree<int> tree;
  tree.clear();
  EXPECT_EQ(tree.size(), 0);
}

// Тест повторного использования после очистки
TEST(RBTreeTest, MultipleClear) {
  RBTree<int> tree;
  tree.insert(1);
  tree.insert(2);
  tree.insert(3);
  tree.clear();
  EXPECT_EQ(tree.size(), 0);
  tree.insert(4);
  tree.insert(5);
  EXPECT_EQ(tree.size(), 2);
  EXPECT_TRUE(tree.contains(4));
  EXPECT_TRUE(tree.contains(5));
}

// Тест удаления узла с двумя детьми
TEST(RBTreeTest, EraseNodeWithTwoChildren) {
  RBTree<int> tree;
  tree.insert(20);
  tree.insert(10);
  tree.insert(30);
  tree.insert(5);
  tree.insert(15);
  EXPECT_TRUE(tree.contains(10));
  tree.erase(10);
  EXPECT_FALSE(tree.contains(10));
  EXPECT_EQ(tree.size(), 4);
}

// Тест удаления листа
TEST(RBTreeTest, EraseLeaf) {
  RBTree<int> tree;
  tree.insert(20);
  tree.insert(10);
  tree.insert(30);
  tree.insert(5);
  tree.insert(15);
  EXPECT_TRUE(tree.contains(5));
  tree.erase(5);
  EXPECT_FALSE(tree.contains(5));
  EXPECT_EQ(tree.size(), 4);
}
// Тест на удаление корневого узла с двумя детьми, где преемник имеет правого
// потомка
TEST(RBTreeTest, EraseRoot1) {
  RBTree<int> tree;
  tree.insert(50);
  tree.insert(30);
  tree.insert(70);
  tree.insert(20);
  tree.insert(40);
  tree.insert(60);
  tree.insert(80);
  tree.insert(35);
  tree.insert(45);

  tree.erase(50);

  EXPECT_FALSE(tree.contains(50));
  EXPECT_EQ(tree.size(), 8);

  EXPECT_TRUE(tree.contains(20));
  EXPECT_TRUE(tree.contains(30));
  EXPECT_TRUE(tree.contains(35));
  EXPECT_TRUE(tree.contains(40));
  EXPECT_TRUE(tree.contains(45));
  EXPECT_TRUE(tree.contains(60));
  EXPECT_TRUE(tree.contains(70));
  EXPECT_TRUE(tree.contains(80));
}

// Тест удаления корневого узла
TEST(RBTreeTest, EraseRoot) {
  RBTree<int> tree;
  tree.insert(20);
  tree.insert(10);
  tree.insert(30);
  EXPECT_TRUE(tree.contains(20));
  tree.erase(20);
  EXPECT_FALSE(tree.contains(20));
  EXPECT_EQ(tree.size(), 2);
}

// Тест последовательных вставок и удалений
TEST(RBTreeTest, SequentialInsertErase) {
  RBTree<int> tree;
  const int n = 100;
  for (int i = 0; i < n; i++) {
    tree.insert(i);
  }
  EXPECT_EQ(tree.size(), n);
  for (int i = 0; i < n; i += 2) {
    tree.erase(i);
  }
  EXPECT_EQ(tree.size(), n / 2);
  for (int i = 0; i < n; i += 2) {
    EXPECT_FALSE(tree.contains(i));
  }
  for (int i = 1; i < n; i += 2) {
    EXPECT_TRUE(tree.contains(i));
  }
}
// Тест удаления всех элементов по очереди
TEST(RBTreeTest, EraseAllElementsSequentially) {
  RBTree<int> tree;
  tree.insert(10);
  tree.insert(20);
  tree.insert(30);
  tree.insert(40);
  tree.insert(50);

  EXPECT_EQ(tree.size(), 5);

  tree.erase(10);
  EXPECT_EQ(tree.size(), 4);
  EXPECT_FALSE(tree.contains(10));

  tree.erase(20);
  EXPECT_EQ(tree.size(), 3);
  EXPECT_FALSE(tree.contains(20));

  tree.erase(30);
  EXPECT_EQ(tree.size(), 2);
  EXPECT_FALSE(tree.contains(30));

  tree.erase(40);
  EXPECT_EQ(tree.size(), 1);
  EXPECT_FALSE(tree.contains(40));

  tree.erase(50);
  EXPECT_EQ(tree.size(), 0);
  EXPECT_FALSE(tree.contains(50));
}

// Тест удаления корневого узла с двумя детьми
TEST(RBTreeTest, EraseRootWithTwo) {
  RBTree<int> tree;
  tree.insert(20);
  tree.insert(10);
  tree.insert(30);
  tree.insert(5);
  tree.insert(15);
  tree.insert(25);
  tree.insert(35);

  EXPECT_TRUE(tree.contains(20));
  tree.erase(20);
  EXPECT_FALSE(tree.contains(20));
  EXPECT_EQ(tree.find(15)->color, Color::RED);
  EXPECT_EQ(tree.find(5)->color, Color::RED);
  EXPECT_EQ(tree.find(35)->color, Color::RED);
  EXPECT_EQ(tree.find(10)->color, Color::BLACK);
  EXPECT_EQ(tree.size(), 6);
}

TEST(RBTreeTest, EraseNodeWithBlackSiblingAndBlackChildren) {
  RBTree<int> tree;
  tree.insert(50);
  tree.insert(30);
  tree.insert(70);
  tree.insert(20);
  tree.insert(40);
  tree.insert(60);
  tree.insert(80);

  tree.erase(60);

  EXPECT_FALSE(tree.contains(60));
  EXPECT_EQ(tree.size(), 6);

  EXPECT_TRUE(tree.contains(20));
  EXPECT_TRUE(tree.contains(30));
  EXPECT_TRUE(tree.contains(40));
  EXPECT_TRUE(tree.contains(50));
  EXPECT_TRUE(tree.contains(70));
  EXPECT_TRUE(tree.contains(80));
  EXPECT_EQ(tree.find(20)->color, Color::RED);
  EXPECT_EQ(tree.find(30)->color, Color::BLACK);
  EXPECT_EQ(tree.find(40)->color, Color::RED);
  EXPECT_EQ(tree.find(50)->color, Color::BLACK);
  EXPECT_EQ(tree.find(70)->color, Color::BLACK);
  EXPECT_EQ(tree.find(80)->color, Color::RED);
}
TEST(RBTreeTest, EraseNodeWithBlackSiblingAndRedChild) {
  RBTree<int> tree;
  tree.insert(50);
  tree.insert(30);
  tree.insert(70);
  tree.insert(20);
  tree.insert(40);
  tree.insert(60);
  tree.insert(80);
  tree.insert(55);
  tree.erase(70);

  EXPECT_FALSE(tree.contains(70));
  EXPECT_EQ(tree.size(), 7);
  EXPECT_TRUE(tree.contains(20));
  EXPECT_TRUE(tree.contains(30));
  EXPECT_TRUE(tree.contains(40));
  EXPECT_TRUE(tree.contains(50));
  EXPECT_TRUE(tree.contains(55));
  EXPECT_TRUE(tree.contains(60));
  EXPECT_TRUE(tree.contains(80));
  EXPECT_EQ(tree.find(20)->color, Color::RED);
  EXPECT_EQ(tree.find(30)->color, Color::BLACK);
  EXPECT_EQ(tree.find(40)->color, Color::RED);
  EXPECT_EQ(tree.find(50)->color, Color::BLACK);
  EXPECT_EQ(tree.find(80)->color, Color::BLACK);
}
TEST(RBTreeTest, FixDeleteCase2) {
  RBTree<int> tree;
  tree.insert(100);
  tree.insert(50);
  tree.insert(150);
  tree.insert(25);
  tree.insert(75);
  tree.insert(125);
  tree.insert(175);
  tree.insert(10);
  tree.insert(30);
  tree.insert(60);
  tree.insert(90);
  tree.insert(110);
  tree.insert(140);
  tree.insert(160);
  tree.insert(190);
  tree.insert(20);

  tree.erase(25);

  EXPECT_TRUE(tree.contains(50));
  EXPECT_EQ(tree.find(10)->color, Color::BLACK);
  EXPECT_EQ(tree.find(20)->color, Color::RED);
}

// Тест для проверки балансировки дерева
TEST(RBTreeTest, BalanceAfterInsertAndDelete1) {
  s21::RBTree<int> tree;
  tree.insert(6746);
  tree.insert(5018);
  tree.insert(6789);
  tree.insert(9389);
  tree.insert(9072);
  tree.insert(5888);
  tree.insert(9756);
  tree.insert(7896);
  tree.insert(9709);
  tree.insert(6824);
  tree.insert(734);
  tree.insert(8821);
  tree.insert(4634);
  tree.insert(8775);
  tree.insert(5949);
  tree.insert(2754);
  tree.insert(6931);
  tree.insert(1332);
  tree.insert(1564);
  tree.insert(5475);
  tree.insert(9506);
  tree.insert(7799);
  tree.insert(5830);
  tree.insert(1410);
  tree.insert(2892);
  tree.insert(9489);
  tree.insert(3816);
  tree.insert(5501);
  tree.insert(1678);
  tree.insert(1997);
  tree.insert(2603);
  tree.insert(4776);
  tree.insert(7015);
  tree.insert(9393);
  tree.insert(518);
  tree.insert(6087);
  tree.insert(1633);
  tree.insert(274);
  tree.insert(335);
  tree.insert(1343);
  tree.insert(3450);
  tree.insert(1069);
  tree.insert(6516);
  tree.insert(8085);
  tree.insert(6197);
  tree.insert(8817);
  tree.insert(7191);
  tree.insert(3128);
  tree.insert(149);
  tree.insert(5107);
  tree.insert(8603);
  tree.insert(6008);
  tree.insert(2906);
  tree.insert(4433);
  tree.insert(3770);
  tree.insert(2151);
  tree.insert(275);
  tree.insert(7586);
  tree.insert(7652);
  tree.insert(1953);
  tree.insert(9583);
  tree.insert(6607);
  tree.insert(6729);
  tree.insert(6598);
  tree.insert(6000);
  tree.insert(3599);
  tree.insert(9037);
  tree.insert(7634);
  tree.insert(3874);
  tree.insert(9372);
  tree.insert(5329);
  tree.insert(7324);
  tree.insert(6794);
  tree.insert(8197);
  tree.insert(1761);
  tree.insert(2991);
  tree.insert(7014);
  tree.insert(5304);
  tree.insert(2471);
  tree.insert(3516);
  tree.insert(412);
  tree.insert(1074);
  tree.insert(9524);
  tree.insert(9670);
  tree.insert(1859);
  tree.insert(3294);
  tree.insert(1821);
  tree.insert(2134);
  tree.insert(7232);
  tree.insert(5825);
  tree.insert(439);
  tree.insert(3167);
  tree.insert(2433);
  tree.insert(3521);
  tree.insert(9765);
  tree.insert(8433);
  tree.insert(7120);
  tree.insert(5154);
  tree.insert(2419);
  tree.insert(7346);
  tree.insert(878);
  tree.insert(4100);
  tree.insert(4671);
  tree.insert(7672);
  tree.insert(2297);
  tree.insert(2784);
  tree.insert(7015);
  tree.insert(5664);
  tree.insert(8089);
  tree.insert(9486);
  tree.insert(9180);
  tree.insert(8501);
  tree.insert(6912);
  tree.insert(8704);
  tree.insert(8171);
  tree.insert(8772);
  tree.insert(8350);
  tree.insert(6345);
  tree.insert(7258);
  tree.insert(1934);
  tree.insert(2170);
  tree.insert(4050);
  tree.insert(5101);
  tree.insert(4603);
  tree.insert(3923);
  tree.insert(1218);
  tree.insert(9389);
  tree.insert(1043);
  tree.insert(6372);
  tree.insert(8160);
  tree.insert(4742);
  tree.insert(3602);
  tree.insert(2261);
  tree.insert(9413);
  tree.insert(1275);
  tree.insert(910);
  tree.insert(8549);
  tree.insert(4642);
  tree.insert(6574);
  tree.insert(6638);
  tree.insert(4129);
  tree.insert(5754);
  tree.insert(1491);
  tree.insert(1041);
  tree.insert(810);
  tree.insert(6015);
  tree.insert(6165);
  tree.insert(5512);
  tree.insert(2360);
  tree.insert(9776);
  tree.insert(7446);
  tree.insert(4530);
  tree.insert(3826);
  tree.insert(2547);
  tree.insert(5486);
  tree.insert(7749);
  tree.insert(3765);
  tree.insert(4875);
  tree.insert(5144);
  tree.insert(6489);
  tree.insert(9387);
  tree.insert(9886);
  tree.insert(92);
  tree.insert(1648);
  tree.insert(5651);
  tree.insert(7719);
  tree.insert(2559);
  tree.insert(4201);
  tree.insert(2361);
  tree.insert(5485);
  tree.insert(839);
  tree.insert(6490);
  tree.insert(7592);
  tree.insert(8683);
  tree.insert(3884);
  tree.insert(8402);
  tree.insert(4698);
  tree.insert(49);
  tree.insert(267);
  tree.insert(7058);
  tree.insert(9825);
  tree.insert(7713);
  tree.insert(7940);
  tree.insert(3);
  tree.insert(6613);
  tree.insert(3426);
  tree.insert(4104);
  tree.insert(6730);
  tree.insert(4653);
  tree.insert(9249);
  tree.insert(3220);
  tree.insert(4041);
  tree.insert(9135);
  tree.insert(9664);
  tree.insert(5689);
  tree.insert(1139);
  tree.insert(3735);
  tree.insert(4600);
  tree.insert(5340);
  tree.insert(6096);
  tree.erase(8160);
  tree.erase(6746);
  tree.erase(5154);
  tree.erase(4129);
  tree.erase(6824);
  tree.erase(9486);
  tree.erase(8704);
  tree.erase(7015);
  tree.erase(2361);
  tree.erase(2784);
  tree.erase(6008);
  tree.erase(6489);
  tree.erase(2419);
  tree.erase(1491);
  tree.erase(5888);
  tree.erase(6000);
  tree.erase(3884);
  tree.erase(8603);
  tree.erase(4634);
  tree.erase(2547);
  tree.erase(3923);
  tree.erase(3167);
  tree.erase(4671);
  tree.erase(2892);
  tree.erase(4201);
  tree.erase(7258);
  tree.erase(2261);
  tree.erase(275);
  tree.erase(1564);
  tree.erase(5651);
  tree.erase(5486);
  tree.erase(335);
  tree.erase(9765);
  tree.erase(6516);
  tree.erase(5485);
  tree.erase(1218);
  tree.erase(6372);
  tree.erase(8089);
  tree.erase(7652);
  tree.erase(810);
  tree.erase(3521);
  tree.erase(8817);
  tree.erase(4050);
  tree.erase(5512);
  tree.erase(5949);
  tree.erase(6015);
  tree.erase(9506);
  tree.erase(3602);
  tree.erase(7672);
  tree.erase(7896);
  tree.erase(9413);
  tree.erase(2991);
  tree.erase(6165);
  tree.erase(1139);
  tree.erase(8350);
  tree.erase(2754);
  tree.erase(3);
  tree.erase(3128);
  tree.erase(878);
  tree.erase(4100);
  tree.erase(7014);
  tree.erase(7015);
  tree.erase(1821);
  tree.erase(8197);
  tree.erase(8772);
  tree.erase(3765);
  tree.erase(5304);
  tree.erase(6096);
  tree.erase(7634);
  tree.erase(8501);
  tree.erase(149);
  tree.erase(1633);
  tree.erase(2170);
  tree.erase(8433);
  tree.erase(2297);
  tree.erase(3735);
  tree.erase(2559);
  tree.erase(9524);
  tree.erase(6729);
  tree.erase(5754);
  tree.erase(7940);
  tree.erase(6789);
  tree.erase(6730);
  tree.erase(5501);
  tree.erase(5664);
  tree.erase(4600);
  tree.erase(734);
  tree.erase(6574);
  tree.erase(5340);
  tree.erase(9886);
  tree.erase(8085);
  tree.erase(2151);
  tree.erase(7058);
  tree.erase(1761);
  tree.erase(1343);
  tree.erase(7799);
  tree.erase(1953);
  tree.erase(7749);
  tree.erase(3516);
  tree.erase(2134);
  EXPECT_FALSE(tree.contains(8160));
  EXPECT_FALSE(tree.contains(6746));
  EXPECT_FALSE(tree.contains(5154));
  EXPECT_FALSE(tree.contains(4129));
  EXPECT_FALSE(tree.contains(6824));
  EXPECT_FALSE(tree.contains(9486));
  EXPECT_FALSE(tree.contains(8704));
  EXPECT_FALSE(tree.contains(7015));
  EXPECT_FALSE(tree.contains(2361));
  EXPECT_FALSE(tree.contains(2784));
  EXPECT_FALSE(tree.contains(6008));
  EXPECT_FALSE(tree.contains(6489));
  EXPECT_FALSE(tree.contains(2419));
  EXPECT_FALSE(tree.contains(1491));
  EXPECT_FALSE(tree.contains(5888));
  EXPECT_FALSE(tree.contains(6000));
  EXPECT_FALSE(tree.contains(3884));
  EXPECT_FALSE(tree.contains(8603));
  EXPECT_FALSE(tree.contains(4634));
  EXPECT_FALSE(tree.contains(2547));
  EXPECT_FALSE(tree.contains(3923));
  EXPECT_FALSE(tree.contains(3167));
  EXPECT_FALSE(tree.contains(4671));
  EXPECT_FALSE(tree.contains(2892));
  EXPECT_FALSE(tree.contains(4201));
  EXPECT_FALSE(tree.contains(7258));
  EXPECT_FALSE(tree.contains(2261));
  EXPECT_FALSE(tree.contains(275));
  EXPECT_FALSE(tree.contains(1564));
  EXPECT_FALSE(tree.contains(5651));
  EXPECT_FALSE(tree.contains(5486));
  EXPECT_FALSE(tree.contains(335));
  EXPECT_FALSE(tree.contains(9765));
  EXPECT_FALSE(tree.contains(6516));
  EXPECT_FALSE(tree.contains(5485));
  EXPECT_FALSE(tree.contains(1218));
  EXPECT_FALSE(tree.contains(6372));
  EXPECT_FALSE(tree.contains(8089));
  EXPECT_FALSE(tree.contains(7652));
  EXPECT_FALSE(tree.contains(810));
  EXPECT_FALSE(tree.contains(3521));
  EXPECT_FALSE(tree.contains(8817));
  EXPECT_FALSE(tree.contains(4050));
  EXPECT_FALSE(tree.contains(5512));
  EXPECT_FALSE(tree.contains(5949));
  EXPECT_FALSE(tree.contains(6015));
  EXPECT_FALSE(tree.contains(9506));
  EXPECT_FALSE(tree.contains(3602));
  EXPECT_FALSE(tree.contains(7672));
  EXPECT_FALSE(tree.contains(7896));
  EXPECT_FALSE(tree.contains(9413));
  EXPECT_FALSE(tree.contains(2991));
  EXPECT_FALSE(tree.contains(6165));
  EXPECT_FALSE(tree.contains(1139));
  EXPECT_FALSE(tree.contains(8350));
  EXPECT_FALSE(tree.contains(2754));
  EXPECT_FALSE(tree.contains(3));
  EXPECT_FALSE(tree.contains(3128));
  EXPECT_FALSE(tree.contains(878));
  EXPECT_FALSE(tree.contains(4100));
  EXPECT_FALSE(tree.contains(7014));
  EXPECT_FALSE(tree.contains(7015));
  EXPECT_FALSE(tree.contains(1821));
  EXPECT_FALSE(tree.contains(8197));
  EXPECT_FALSE(tree.contains(8772));
  EXPECT_FALSE(tree.contains(3765));
  EXPECT_FALSE(tree.contains(5304));
  EXPECT_FALSE(tree.contains(6096));
  EXPECT_FALSE(tree.contains(7634));
  EXPECT_FALSE(tree.contains(8501));
  EXPECT_FALSE(tree.contains(149));
  EXPECT_FALSE(tree.contains(1633));
  EXPECT_FALSE(tree.contains(2170));
  EXPECT_FALSE(tree.contains(8433));
  EXPECT_FALSE(tree.contains(2297));
  EXPECT_FALSE(tree.contains(3735));
  EXPECT_FALSE(tree.contains(2559));
  EXPECT_FALSE(tree.contains(9524));
  EXPECT_FALSE(tree.contains(6729));
  EXPECT_FALSE(tree.contains(5754));
  EXPECT_FALSE(tree.contains(7940));
  EXPECT_FALSE(tree.contains(6789));
  EXPECT_FALSE(tree.contains(6730));
  EXPECT_FALSE(tree.contains(5501));
  EXPECT_FALSE(tree.contains(5664));
  EXPECT_FALSE(tree.contains(4600));
  EXPECT_FALSE(tree.contains(734));
  EXPECT_FALSE(tree.contains(6574));
  EXPECT_FALSE(tree.contains(5340));
  EXPECT_FALSE(tree.contains(9886));
  EXPECT_FALSE(tree.contains(8085));
  EXPECT_FALSE(tree.contains(2151));
  EXPECT_FALSE(tree.contains(7058));
  EXPECT_FALSE(tree.contains(1761));
  EXPECT_FALSE(tree.contains(1343));
  EXPECT_FALSE(tree.contains(7799));
  EXPECT_FALSE(tree.contains(1953));
  EXPECT_FALSE(tree.contains(7749));
  EXPECT_FALSE(tree.contains(3516));
  EXPECT_FALSE(tree.contains(2134));
}

// Тест для rotateRight в обычном дереве (Lb0)
TEST(RBTreeTest, RotateRight) {
  RBTree<int, false> tree;
  tree.insert(30);
  tree.insert(20);
  tree.insert(10);

  EXPECT_TRUE(tree.contains(10));
  EXPECT_TRUE(tree.contains(20));
  EXPECT_TRUE(tree.contains(30));
}

// Тест для rotateRight в мультисете (Lb1)
TEST(RBTreeMultisetTest, RotateRight) {
  RBTree<int, true> tree;
  tree.insert(30);
  tree.insert(20);
  tree.insert(20);
  tree.insert(10);

  EXPECT_TRUE(tree.contains(10));
  EXPECT_TRUE(tree.contains(20));
  EXPECT_TRUE(tree.contains(30));
  EXPECT_EQ(tree.count(20), 2);
}

// Тест для handleBlackUncleLeft в обычном дереве
TEST(RBTreeTest, HandleBlackUncleLeft) {
  RBTree<int, false> tree;
  tree.insert(50);
  tree.insert(30);
  tree.insert(70);
  tree.insert(10);
  tree.insert(40);
  tree.insert(35);

  EXPECT_TRUE(tree.contains(35));
}

// Тест для handleBlackUncleLeft в мультисете
TEST(RBTreeMultisetTest, HandleBlackUncleLeft) {
  RBTree<int, true> tree;
  tree.insert(50);
  tree.insert(30);
  tree.insert(30);
  tree.insert(70);
  tree.insert(10);
  tree.insert(40);
  tree.insert(35);

  EXPECT_TRUE(tree.contains(35));
  EXPECT_EQ(tree.count(30), 2);
}
// Тесты для RBTree<std::string, false> (без дубликатов)
TEST(RBTreeTest, RotateRightStringNoDuplicates) {
  RBTree<std::string, false> tree;
  tree.insert("apple");
  tree.insert("banana");
  tree.insert("cherry");

  EXPECT_TRUE(tree.contains("apple"));
  EXPECT_TRUE(tree.contains("banana"));
  EXPECT_TRUE(tree.contains("cherry"));
  EXPECT_EQ(tree.size(), 3);
}

TEST(RBTreeTest, HandleRedUncleStringNoDuplicates) {
  RBTree<std::string, false> tree;
  tree.insert("apple");
  tree.insert("banana");
  tree.insert("cherry");
  tree.insert("date");

  EXPECT_TRUE(tree.contains("apple"));
  EXPECT_TRUE(tree.contains("banana"));
  EXPECT_TRUE(tree.contains("cherry"));
  EXPECT_TRUE(tree.contains("date"));
  EXPECT_EQ(tree.size(), 4);
}

TEST(RBTreeTest, FixInsertLeftCaseStringNoDuplicates) {
  RBTree<std::string, false> tree;
  tree.insert("cherry");
  tree.insert("banana");
  tree.insert("apple");

  EXPECT_TRUE(tree.contains("cherry"));
  EXPECT_TRUE(tree.contains("banana"));
  EXPECT_TRUE(tree.contains("apple"));
  EXPECT_EQ(tree.size(), 3);
}

TEST(RBTreeTest, HandleBlackUncleLeftStringNoDuplicates) {
  RBTree<std::string, false> tree;
  tree.insert("apple");
  tree.insert("cherry");
  tree.insert("banana");

  EXPECT_TRUE(tree.contains("apple"));
  EXPECT_TRUE(tree.contains("cherry"));
  EXPECT_TRUE(tree.contains("banana"));
  EXPECT_EQ(tree.size(), 3);
}

// Тесты для RBTree<std::string, true> (с дубликатами)
TEST(RBTreeTest, RotateRightStringWithDuplicates) {
  RBTree<std::string, true> tree;
  tree.insert("apple");
  tree.insert("banana");
  tree.insert("cherry");
  tree.insert("apple");

  EXPECT_TRUE(tree.contains("apple"));
  EXPECT_TRUE(tree.contains("banana"));
  EXPECT_TRUE(tree.contains("cherry"));
  EXPECT_EQ(tree.size(), 4);
}

TEST(RBTreeTest, HandleRedUncleStringWithDuplicates) {
  RBTree<std::string, true> tree;
  tree.insert("apple");
  tree.insert("banana");
  tree.insert("cherry");
  tree.insert("date");
  tree.insert("apple");

  EXPECT_TRUE(tree.contains("apple"));
  EXPECT_TRUE(tree.contains("banana"));
  EXPECT_TRUE(tree.contains("cherry"));
  EXPECT_TRUE(tree.contains("date"));
  EXPECT_EQ(tree.size(), 5);
}

TEST(RBTreeTest, FixInsertLeftCaseStringWithDuplicates) {
  RBTree<std::string, true> tree;
  tree.insert("cherry");
  tree.insert("banana");
  tree.insert("apple");
  tree.insert("cherry");

  EXPECT_TRUE(tree.contains("cherry"));
  EXPECT_TRUE(tree.contains("banana"));
  EXPECT_TRUE(tree.contains("apple"));
  EXPECT_EQ(tree.size(), 4);
}

TEST(RBTreeTest, HandleBlackUncleLeftStringWithDuplicates) {
  RBTree<std::string, true> tree;
  tree.insert("apple");
  tree.insert("cherry");
  tree.insert("banana");
  tree.insert("apple");

  EXPECT_TRUE(tree.contains("apple"));
  EXPECT_TRUE(tree.contains("cherry"));
  EXPECT_TRUE(tree.contains("banana"));
  EXPECT_EQ(tree.size(), 4);
}
