#include <gtest/gtest.h>

#include <algorithm>
#include <map>

#include "test_headers.h"

TEST(test_map, map_test_1) {
  s21::map<int, int> my_map;
  int arr_key[] = {3,  534, 1, 45,   264,  63,  7, 72,
                   54, 75,  4, 3563, 7543, 542, 12};
  int arr_value[] = {14,   34, 122, 445, 13264, 53, 77, 772,
                     1334, 95, 74,  363, 73,    42, 2};
  std::pair<typename s21::map<int, int>::MapIterator, bool> res;
  std::pair<typename s21::map<int, int>::MapIterator, bool> res1;
  for (int i = 0; i < 15; i++) {
    res = my_map.insert(arr_key[i], arr_value[i]);
    ASSERT_TRUE(res.second);
    ASSERT_TRUE(res.first.getKey() == arr_key[i]);
  }
  res = my_map.insert(arr_key[0], 322);
  ASSERT_TRUE(!res.second);
  ASSERT_TRUE(res.first.getKey() == arr_key[0]);
  ASSERT_TRUE(res.first.getValue() == arr_value[0]);
}

TEST(test_map, map_iter_test) {
  s21::map<int, int> my_map;
  int arr_key[] = {3,  534, 1, 45,   264,  63,  7, 72,
                   54, 75,  4, 3563, 7543, 542, 12};
  int arr_value[] = {14,   34, 122, 445, 13264, 53, 77, 772,
                     1334, 95, 74,  363, 73,    42, 2};
  for (int i = 0; i < 15; i++) {
    my_map.insert(arr_key[i], arr_value[i]);
  }
  ASSERT_TRUE(my_map.begin().getKey() == 1);
  ASSERT_TRUE(my_map.end().getKey() == 7543);
}

TEST(test_map, map_iter2_test) {
  s21::map<int, int> my_map;
  ASSERT_TRUE(my_map.begin().iter_is_nullptr());
  ASSERT_TRUE(my_map.end().iter_is_nullptr());
}

TEST(test_map, map_test_contains) {
  s21::map<int, int> my_map;
  my_map.insert(1, 1);
  ASSERT_TRUE(my_map.contains(1));
  ASSERT_TRUE(!my_map.contains(2));
}

TEST(test_map, map_test_empty) {
  s21::map<int, int> my_map;
  ASSERT_TRUE(my_map.empty());
  my_map.insert(1, 1);
  ASSERT_TRUE(!my_map.empty());
}

TEST(test_map, map_test_size) {
  s21::map<int, int> my_map;
  ASSERT_TRUE(my_map.size() == 0);
  int arr_key[] = {3,  534, 1, 45,   264,  63,  7, 72,
                   54, 75,  4, 3563, 7543, 542, 12};
  int arr_value[] = {14,   34, 122, 445, 13264, 53, 77, 772,
                     1334, 95, 74,  363, 73,    42, 2};
  for (int i = 0; i < 15; i++) {
    my_map.insert(arr_key[i], arr_value[i]);
  }
  ASSERT_TRUE(my_map.size() == 15);
}

TEST(test_map, map_test_size1) {
  s21::map<int, int> my_map;
  my_map.insert(1, 1);
  ASSERT_TRUE(my_map.size() == 1);
  my_map.insert(1, 2);
  ASSERT_TRUE(my_map.size() == 1);
  my_map.insert(2, 1);
  ASSERT_TRUE(my_map.size() == 2);
}

TEST(test_map, map_test_3) {
  s21::map<int, int> my_map;
  int arr_key[] = {3,  534, 1, 45,   264,  63,  7, 72,
                   54, 75,  4, 3563, 7543, 542, 12};
  int arr_value[] = {14,   34, 122, 445, 13264, 53, 77, 772,
                     1334, 95, 74,  363, 73,    42, 2};
  std::pair<typename s21::map<int, int>::MapIterator, bool> res;
  for (int i = 0; i < 15; i++) {
    res = my_map.insert(std::make_pair(arr_key[i], arr_value[i]));
    ASSERT_TRUE(res.second);
    ASSERT_TRUE(res.first.getKey() == arr_key[i]);
  }
}

TEST(test_map, map_test_4) {
  s21::map<int, int> my_map;
  int arr_key[] = {3,  534, 1, 45,   264,  63,  7, 72,
                   54, 75,  4, 3563, 7543, 542, 12};
  int arr_value[] = {14,   34, 122, 445, 13264, 53, 77, 772,
                     1334, 95, 74,  363, 73,    42, 2};
  std::pair<typename s21::map<int, int>::MapIterator, bool> res;
  for (int i = 0; i < 15; i++) {
    res = my_map.insert(std::make_pair(arr_key[i], arr_value[i]));
  }
  ASSERT_TRUE(my_map[3] == 14);
  my_map[3] = 1;
  ASSERT_TRUE(my_map[3] == 1);
  my_map[7777] = 1;
  ASSERT_TRUE(my_map[7777] == 1);
}

TEST(test_map, map_test_5) {
  s21::map<int, int> my_map;
  int arr_key[] = {3,  534, 1, 45,   264,  63,  7, 72,
                   54, 75,  4, 3563, 7543, 542, 12};
  int arr_value[] = {14,   34, 122, 445, 13264, 53, 77, 772,
                     1334, 95, 74,  363, 73,    42, 2};
  std::pair<typename s21::map<int, int>::MapIterator, bool> res;
  for (int i = 0; i < 15; i++) {
    res = my_map.insert(std::make_pair(arr_key[i], arr_value[i]));
  }
  ASSERT_TRUE(my_map.at(3) == 14);
  my_map.at(3) = 1;
  ASSERT_TRUE(my_map.at(3) == 1);
  EXPECT_THROW(my_map.at(7777), std::out_of_range);
  EXPECT_THROW(my_map.at(122), std::out_of_range);
}

TEST(test_map, map_test_insert_or_assign) {
  s21::map<int, int> my_map;
  int arr_key[] = {3,  534, 1, 45,   264,  63,  7, 72,
                   54, 75,  4, 3563, 7543, 542, 12};
  int arr_value[] = {14,   34, 122, 445, 13264, 53, 77, 772,
                     1334, 95, 74,  363, 73,    42, 2};
  std::pair<typename s21::map<int, int>::MapIterator, bool> res;
  for (int i = 0; i < 15; i++) {
    res = my_map.insert_or_assign(arr_key[i], arr_value[i]);
    ASSERT_TRUE(res.second);
    ASSERT_TRUE(res.first.getKey() == arr_key[i]);
  }
  res = my_map.insert_or_assign(534, 999);
  ASSERT_TRUE(res.second);
  ASSERT_TRUE(res.first.getKey() == 534);
  ASSERT_TRUE(res.first.getValue() == 999);
}

TEST(test_map, map_test_clear) {
  s21::map<int, int> my_map;
  int arr_key[] = {3,  534, 1, 45,   264,  63,  7, 72,
                   54, 75,  4, 3563, 7543, 542, 12};
  int arr_value[] = {14,   34, 122, 445, 13264, 53, 77, 772,
                     1334, 95, 74,  363, 73,    42, 2};
  ASSERT_TRUE(my_map.empty());
  for (int i = 0; i < 15; i++) {
    my_map.insert_or_assign(arr_key[i], arr_value[i]);
  }
  ASSERT_TRUE(!my_map.empty());
  my_map.clear();
  ASSERT_TRUE(my_map.empty());
  my_map.clear();
  ASSERT_TRUE(my_map.empty());
}

// удаленеи когда нет предков
TEST(test_map, map_test_earse1) {
  s21::map<int, int> map;
  int arr_key[] = {3,  534, 1, 45,   264,  63,  7, 72,
                   54, 75,  4, 3563, 7543, 542, 12};
  int arr_value[] = {3,  534, 1, 45,   264,  63,  7, 72,
                     54, 75,  4, 3563, 7543, 542, 12};
  for (int i = 0; i < 15; i++) {
    arr_value[i] = ((arr_value[i] + 3) * 3 + 4) / 2;
    map.insert(arr_key[i], arr_value[i]);
  }
  std::sort(std::begin(arr_key), std::end(arr_key));
  s21::map<int, int>::MapIterator it = map.begin();
  map.erase(it);
  it = map.begin();
  for (int i = 1; i < 15; i++) {
    ASSERT_TRUE(it.getKey() == arr_key[i]);
    ++it;
  }
}

// удаление когда только один предок
TEST(test_map, map_test_earse2) {
  s21::map<int, int> map;
  int arr_key[] = {3,  534, 1, 45,   264,  63,  7, 72,
                   54, 75,  4, 3563, 7543, 542, 12};
  int arr_value[] = {3,  534, 1, 45,   264,  63,  7, 72,
                     54, 75,  4, 3563, 7543, 542, 12};
  for (int i = 0; i < 15; i++) {
    arr_value[i] = ((arr_value[i] + 3) * 3 + 4) / 2;
    map.insert(arr_key[i], arr_value[i]);
  }
  std::sort(std::begin(arr_key), std::end(arr_key));
  s21::map<int, int>::MapIterator it(map.find1(72));
  map.erase(it);
  it = map.begin();
  int arr_key_res[] = {1,  3,  4,   7,   12,  45,   54,
                       63, 75, 264, 534, 542, 3563, 7543};
  for (int i = 0; i < 14; i++) {
    ASSERT_TRUE(it.getKey() == arr_key_res[i]);
    ++it;
  }
}

// удаление когда два предка
TEST(test_map, map_test_earse3) {
  s21::map<int, int> map;
  int arr_key[] = {3,  534, 1, 45,   264,  63,  7, 72,
                   54, 75,  4, 3563, 7543, 542, 12};
  int arr_value[] = {3,  534, 1, 45,   264,  63,  7, 72,
                     54, 75,  4, 3563, 7543, 542, 12};
  for (int i = 0; i < 15; i++) {
    arr_value[i] = ((arr_value[i] + 3) * 3 + 4) / 2;
    map.insert(arr_key[i], arr_value[i]);
  }
  std::sort(std::begin(arr_key), std::end(arr_key));
  s21::map<int, int>::MapIterator it(map.find1(45));
  map.erase(it);
  it = map.begin();
  int arr_key_res[] = {1,  3,  4,   7,   12,  54,   63,
                       72, 75, 264, 534, 542, 3563, 7543};
  for (int i = 0; i < 14; i++) {
    ASSERT_TRUE(it.getKey() == arr_key_res[i]);
    ++it;
  }
}

TEST(test_map, map_test_initlist) {
  s21::map<int, int> map({std::make_pair(1, 1), std::make_pair(2, 2),
                          std::make_pair(3, 3), std::make_pair(9, 1),
                          std::make_pair(5, 2)});
  ASSERT_TRUE(!map.empty());
  int arr_key[] = {1, 2, 3, 5, 9};
  s21::map<int, int>::MapIterator it = map.begin();
  for (int i = 0; i < 5; i++) {
    ASSERT_TRUE(it.getKey() == arr_key[i]);
    ++it;
  }
}

TEST(test_map, map_test_copy) {
  s21::map<int, int> map({std::make_pair(1, 1), std::make_pair(2, 2),
                          std::make_pair(3, 3), std::make_pair(9, 1),
                          std::make_pair(5, 2)});
  ASSERT_TRUE(!map.empty());
  int arr_key[] = {1, 2, 3, 5, 9};
  s21::map<int, int> map1(map);
  map.clear();
  ASSERT_TRUE(map.empty());
  ASSERT_TRUE(!map1.empty());
  s21::map<int, int>::MapIterator it = map1.begin();
  for (int i = 0; i < 5; i++) {
    ASSERT_TRUE(it.getKey() == arr_key[i]);
    ++it;
  }
}

TEST(test_map, map_test_swap) {
  s21::map<int, int> map({std::make_pair(1, 1), std::make_pair(2, 2),
                          std::make_pair(3, 3), std::make_pair(9, 1),
                          std::make_pair(5, 2)});
  s21::map<int, int> map1;
  ASSERT_TRUE(!map.empty());
  ASSERT_TRUE(map1.empty());
  int arr_key[] = {1, 2, 3, 5, 9};
  map1.swap(map);
  ASSERT_TRUE(map.empty());
  s21::map<int, int>::MapIterator it = map1.begin();
  for (int i = 0; i < 5; i++) {
    ASSERT_TRUE(it.getKey() == arr_key[i]);
    ++it;
  }
}

TEST(test_map, map_test_copy_prisvaivan) {
  s21::map<int, int> map({std::make_pair(1, 1), std::make_pair(2, 2),
                          std::make_pair(3, 3), std::make_pair(9, 1),
                          std::make_pair(5, 2)});
  s21::map<int, int> map1;
  ASSERT_TRUE(!map.empty());
  ASSERT_TRUE(map1.empty());
  int arr_key[] = {1, 2, 3, 5, 9};
  map1 = map;
  ASSERT_TRUE(!map.empty());
  ASSERT_TRUE(!map1.empty());
  s21::map<int, int>::MapIterator it = map.begin();
  s21::map<int, int>::MapIterator it1 = map1.begin();
  for (int i = 0; i < 5; i++) {
    ASSERT_TRUE(it.getKey() == arr_key[i]);
    ASSERT_TRUE(it1.getKey() == arr_key[i]);
    ++it;
    ++it1;
  }
}

TEST(test_map, map_test_move) {
  s21::map<int, int> map({std::make_pair(1, 1), std::make_pair(2, 2),
                          std::make_pair(3, 3), std::make_pair(9, 1),
                          std::make_pair(5, 2)});
  s21::map<int, int> map1({std::make_pair(9, 8), std::make_pair(8, 9)});
  ASSERT_TRUE(!map.empty());
  ASSERT_TRUE(!map1.empty());
  int arr_key[] = {1, 2, 3, 5, 9};
  map1 = std::move(map);
  ASSERT_TRUE(map.empty());
  ASSERT_TRUE(!map1.empty());
  s21::map<int, int>::MapIterator it = map1.begin();
  for (int i = 0; i < 5; i++) {
    ASSERT_TRUE(it.getKey() == arr_key[i]);
    ++it;
  }
}

TEST(test_map, map_test_iterator) {
  s21::map<int, int> map({std::make_pair(1, 1), std::make_pair(2, 2),
                          std::make_pair(3, 3), std::make_pair(9, 1),
                          std::make_pair(5, 2)});
  int arr_key[] = {1, 2, 3, 5, 9};
  s21::map<int, int>::MapIterator it = map.begin();

  for (int i = 0; i < 5; i++) {
    ASSERT_TRUE(it.getKey() == arr_key[i]);
    ASSERT_TRUE((*it).first == arr_key[i]);
    ++it;
  }
}

TEST(test_map, map_test_merge) {
  int arr_key[] = {3,  534, 1, 45,   264,  63,  7, 72,
                   54, 75,  4, 3563, 7543, 542, 12};
  int arr_value[] = {14,   34, 122, 445, 13264, 53, 77, 772,
                     1334, 95, 74,  363, 73,    42, 2};
  s21::map<int, int> map;
  s21::map<int, int> map1;
  for (int i = 0; i < 7; i++) {
    map.insert(arr_key[i], arr_value[i]);
  }
  for (int i = 7; i < 15; i++) {
    map1.insert(arr_key[i], arr_value[i]);
  }
  std::sort(std::begin(arr_key), std::end(arr_key));
  map.merge(map1);
  s21::map<int, int>::MapIterator it = map.begin();
  for (int i = 0; i < 15; i++) {
    ASSERT_TRUE(it.getKey() == arr_key[i]);
    ++it;
  }
}

TEST(test_map, map_test_many_insert) {
  s21::map<int, int> map;
  map.insert_many(std::make_pair(1, 1), std::make_pair(2, 2),
                  std::make_pair(3, 3), std::make_pair(4, 4),
                  std::make_pair(5, 5));
  s21::map<int, int>::MapIterator it = map.begin();
  for (int i = 1; i < 6; i++) {
    ASSERT_TRUE(it.getKey() == i);
    ++it;
  }
}

TEST(test_map, map_test_max_size) {
  s21::map<int, int> map;
  std::map<int, int> map_real;
  ASSERT_TRUE(map.max_size() == map_real.max_size());
}
// сравнение с реальной map

TEST(test_map, map_test_realmap_1) {
  s21::map<int, int> map{std::make_pair(9, 1), std::make_pair(999, 2),
                         std::make_pair(1, 3), std::make_pair(333, 1),
                         std::make_pair(52, 2)};
  std::map<int, int> map_real{std::make_pair(9, 1), std::make_pair(999, 2),
                              std::make_pair(1, 3), std::make_pair(333, 1),
                              std::make_pair(52, 2)};
  ASSERT_TRUE(map.at(9) == map_real.at(9));
  ASSERT_THROW(map.at(14), std::out_of_range);
  ASSERT_THROW(map_real.at(14), std::out_of_range);
  ASSERT_TRUE(map[9] == map_real[9]);
  map[11] = 2;
  map_real[11] = 2;
  ASSERT_TRUE(map[11] == map_real[11]);
}

TEST(test_map, map_test_realmap_2) {
  s21::map<int, int> map{std::make_pair(9, 1), std::make_pair(999, 2),
                         std::make_pair(1, 3), std::make_pair(333, 1),
                         std::make_pair(52, 2)};
  std::map<int, int> map_real{std::make_pair(9, 1), std::make_pair(999, 2),
                              std::make_pair(1, 3), std::make_pair(333, 1),
                              std::make_pair(52, 2)};
  auto it_real = map_real.begin();
  s21::map<int, int>::MapIterator it = map.begin();
  ASSERT_TRUE((*it_real).first == (*it).first);
  ASSERT_TRUE((*it_real).second == (*it).second);
  it_real = map_real.end();
  it = map.end();
  it_real--;
  ASSERT_TRUE((*it_real).first == (*it).first);
  ASSERT_TRUE((*it_real).second == (*it).second);
  ASSERT_TRUE(map.empty() == map_real.empty());
  ASSERT_TRUE(map.size() == map_real.size());
  ASSERT_TRUE(map.contains(9) == true);
  map.clear();
  map_real.clear();
  ASSERT_TRUE(map.empty() == map_real.empty());
  ASSERT_TRUE(map.contains(9) == false);
}

TEST(test_map, map_test_realmap_3) {
  s21::map<int, int> map{std::make_pair(9, 1), std::make_pair(999, 2),
                         std::make_pair(1, 3), std::make_pair(333, 1),
                         std::make_pair(52, 2)};
  std::map<int, int> map_real{std::make_pair(9, 1), std::make_pair(999, 2),
                              std::make_pair(1, 3), std::make_pair(333, 1),
                              std::make_pair(52, 2)};
  auto it_real = map_real.insert(std::make_pair(999, 2));
  std::pair<typename s21::map<int, int>::MapIterator, bool> res =
      map.insert(std::make_pair(999, 2));
  ASSERT_TRUE(it_real.second == res.second);
  it_real = map_real.insert(std::make_pair(99, 2));
  res = map.insert(std::make_pair(99, 2));
  ASSERT_TRUE(it_real.second == res.second);
  ASSERT_TRUE((*it_real.first).first == (*res.first).first);
  res = map.insert(99, 2);
  ASSERT_TRUE(false == res.second);
  it_real.first++;
  map_real.erase(it_real.first);
  res.first++;
  map.erase(res.first);
  it_real = map_real.insert(std::make_pair(333, 2));
  res = map.insert(std::make_pair(333, 2));
  ASSERT_TRUE(it_real.second == res.second);
  ASSERT_TRUE((*it_real.first).first == (*res.first).first);
}

TEST(test_map, map_test_realmap_4) {
  s21::map<int, int> map{std::make_pair(9, 1)};
  std::map<int, int> map_real{std::make_pair(9, 1)};
  s21::map<int, int> map1;
  std::map<int, int> map_real1;
  ASSERT_TRUE(map1.empty() == map_real1.empty());
  map1.swap(map);
  map_real1.swap(map_real);
  ASSERT_TRUE(map1.empty() == map_real1.empty());
  ASSERT_TRUE(map.empty() == map_real.empty());
}

TEST(test_map, map_test_merge_test) {
  s21::map<int, int> map{std::make_pair(9, 11)};
  s21::map<int, int> map1{std::make_pair(12, 3), std::make_pair(1, 13),
                          std::make_pair(11, 9)};
  map1.merge(map);
  int arr_key[] = {1, 9, 11, 12};
  s21::map<int, int>::MapIterator it = map1.begin();
  for (int i = 0; i < 4; i++) {
    ASSERT_TRUE((*it).first == arr_key[i]);
    it++;
  }
}
