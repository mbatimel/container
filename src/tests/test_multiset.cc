#include <gtest/gtest.h>

#include "test_headers.h"

TEST(MultisetTest, DefaultConstructor) {
  s21::multiset<int> test;
  EXPECT_TRUE(test.empty());
}

TEST(MultisetTest, CopyConstructor) {
  s21::multiset<int> original = {1, 2, 2, 3, 3, 3};
  s21::multiset<int> copy(original);
  EXPECT_EQ(original.size(), copy.size());
  EXPECT_EQ(original.size(), copy.size());
  EXPECT_TRUE(copy.contains(1));
  EXPECT_TRUE(copy.contains(2));
  EXPECT_TRUE(copy.contains(3));
}

TEST(MultisetTest, MoveConstructor) {
  s21::multiset<int> original = {1, 2, 3, 1};

  s21::multiset<int> moved(std::move(original));

  EXPECT_TRUE(original.empty());

  EXPECT_TRUE(moved.contains(1));
  EXPECT_TRUE(moved.contains(2));
  EXPECT_TRUE(moved.contains(3));
}

TEST(MultisetTest, MoveAssignmentOperator) {
  s21::multiset<int> source;
  source.insert(1);
  source.insert(2);
  source.insert(2);

  s21::multiset<int> destination;
  destination.insert(3);

  destination = std::move(source);

  EXPECT_EQ(source.size(), 0u);
  EXPECT_FALSE(source.contains(1));
  EXPECT_FALSE(source.contains(2));

  EXPECT_EQ(destination.size(), 3u);
  EXPECT_TRUE(destination.contains(1));
  EXPECT_TRUE(destination.contains(2));
  EXPECT_FALSE(destination.contains(3));
}

TEST(MultisetTest, InsertMethod) {
  s21::multiset<int> test;
  test.insert(1);
  EXPECT_FALSE(test.empty());
  EXPECT_EQ(test.size(), 1u);
  test.insert(2);
  EXPECT_EQ(test.size(), 2u);
  test.insert(2);
  EXPECT_EQ(test.size(), 3u);
  test.insert(2);
  EXPECT_EQ(test.size(), 4u);
}

TEST(MultisetTest, InitializerListConstructor) {
  s21::multiset<int> test_set = {1, 2, 2, 3, 3, 3};

  EXPECT_EQ(test_set.size(), 6u);

  EXPECT_TRUE(test_set.contains(1));
  EXPECT_TRUE(test_set.contains(2));
  EXPECT_TRUE(test_set.contains(3));
  EXPECT_FALSE(test_set.contains(0));
  EXPECT_FALSE(test_set.contains(4));
}

TEST(MultisetTest, FindMethod) {
  s21::multiset<int> test_set = {1, 2, 2, 3, 3, 3};

  auto it1 = test_set.find(1);
  auto it2 = test_set.find(2);
  auto it3 = test_set.find(3);
  auto it4 = test_set.find(4);

  EXPECT_TRUE(it1.getKey() != test_set.end().getKey());
  EXPECT_TRUE(it2.getKey() != test_set.end().getKey());
  EXPECT_TRUE(it3.getKey() == test_set.end().getKey());
  EXPECT_TRUE(it4.iter_is_nullptr());
}

TEST(MultisetTest, ContainsMethod) {
  s21::multiset<int> test_set = {1, 2, 2, 3, 3, 3};

  EXPECT_TRUE(test_set.contains(1));
  EXPECT_TRUE(test_set.contains(2));
  EXPECT_TRUE(test_set.contains(3));
  EXPECT_FALSE(test_set.contains(0));
  EXPECT_FALSE(test_set.contains(4));
}

TEST(MultisetTest, BeginMethod) {
  s21::multiset<int> test_set;
  test_set.insert(1);
  test_set.insert(2);
  test_set.insert(3);
  int i = 1;
  for (auto it = test_set.begin(); it != test_set.end(); ++it, ++i) {
    EXPECT_EQ(*it, i);
  }
}

TEST(MultisetTest, SizeMethod) {
  s21::multiset<int> test_set;
  EXPECT_EQ(test_set.size(), 0u);

  test_set.insert(1);
  test_set.insert(2);
  test_set.insert(2);
  test_set.insert(3);

  EXPECT_EQ(test_set.size(), 4u);
}

TEST(MultisetTest, MaxSizeMethod) {
  s21::multiset<int> test_set;
  EXPECT_TRUE(0 == test_set.size());

  for (int i = 0; i < 1000; ++i) {
    test_set.insert(i);
  }

  EXPECT_TRUE(1000 == test_set.size());
}

TEST(MultisetTest, ClearMethod) {
  s21::multiset<int> test_set = {1, 2, 2, 3, 3, 3};
  EXPECT_EQ(test_set.size(), 6u);

  test_set.clear();

  EXPECT_EQ(test_set.size(), 0u);
  EXPECT_TRUE(test_set.empty());
}

TEST(MultisetTest, EraseMethod) {
  s21::multiset<int> test_set = {1, 2, 2, 3, 3, 3};
  EXPECT_TRUE(test_set.size() == 6);

  auto it = test_set.find(2);
  test_set.erase(it);

  EXPECT_EQ(test_set.size(), 5u);
}

TEST(MultisetTest, SwapMethod) {
  s21::multiset<int> test_set1 = {1, 2, 2, 3, 3, 3};
  s21::multiset<int> test_set2 = {4, 5, 6};

  EXPECT_EQ(test_set1.size(), 6u);
  EXPECT_EQ(test_set2.size(), 3u);

  test_set1.swap(test_set2);
  EXPECT_EQ(test_set1.size(), 3u);
  EXPECT_EQ(test_set2.size(), 6u);
  EXPECT_TRUE(test_set1.contains(4));
  EXPECT_TRUE(test_set2.contains(1));
}

TEST(MultisetTest, MergeMethod) {
  s21::multiset<int> test_set1 = {1, 2, 2, 3, 3, 3};
  s21::multiset<int> test_set2 = {4, 5, 6};
  int arr_key[] = {1, 2, 2, 3, 3, 3, 4, 5, 6};
  test_set1.merge(test_set2);
  EXPECT_TRUE(test_set1.size() == 9);
  auto it = test_set1.begin();
  for (int i = 0; i < 9; i++) {
    ASSERT_TRUE(it.getKey() == arr_key[i]);
    ++it;
  }
}

TEST(MultisetTest, CountMethod) {
  s21::multiset<int> multiset = {1, 2, 2, 3, 2, 4, 4, 4, 5};
  std::multiset<int> multiset2 = {1, 2, 2, 3, 2, 4, 4, 4, 5};
  EXPECT_EQ(multiset.count(1), multiset2.count(1));
  EXPECT_EQ(multiset.count(2), multiset.count(2));
  EXPECT_EQ(multiset.count(3), multiset.count(3));
  EXPECT_EQ(multiset.count(4), multiset.count(4));
  EXPECT_EQ(multiset.count(5), multiset.count(5));
  EXPECT_EQ(multiset.count(6), multiset.count(6));
}

TEST(MultisetTest, TestLowerBound) {
  s21::multiset<int> my = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
  auto lb1 = my.lower_bound(2);
  EXPECT_EQ(lb1.getKey(), 2);
  auto lb2 = my.lower_bound(5);
  EXPECT_EQ(lb2, my.end());
  auto lb3 = my.lower_bound(0);
  EXPECT_EQ(lb3, my.begin());
}

TEST(MultisetTest, TestUpperBound) {
  s21::multiset<int> my = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
  auto lb1 = my.upper_bound(1);
  EXPECT_EQ((lb1).getKey(), 2);
  auto lb2 = my.upper_bound(5);
  EXPECT_EQ(lb2, my.end());
  auto lb3 = my.upper_bound(0);
  EXPECT_EQ(lb3, my.begin());
}

TEST(MultisetTest, TestEqualRange) {
  s21::multiset<int> myMultiset = {1, 2, 2, 3, 4, 4, 5};
  auto range1 = myMultiset.equal_range(2);
  EXPECT_EQ(range1.first, myMultiset.lower_bound(2));
  auto ub1 = myMultiset.upper_bound(2);
  EXPECT_EQ(range1.second, ub1);

  auto range2 = myMultiset.equal_range(4);
  EXPECT_EQ(range2.first, myMultiset.lower_bound(4));
  auto ub2 = myMultiset.upper_bound(4);
  EXPECT_EQ(range2.second, ub2);
}

TEST(MultisetTest, InsertMany) {
  s21::multiset<int> test({1, 2, 3, 3, 3, 4, 5});
  test.insert_many(3, 6, 5);
  int resultat[] = {1, 2, 3, 3, 3, 3, 4, 5, 5, 6};

  EXPECT_TRUE(test.size() == 10);
  auto it = test.begin();
  for (int i = 0; i < 10; i++) {
    ASSERT_TRUE(it.getKey() == resultat[i]);
    ++it;
  }
}