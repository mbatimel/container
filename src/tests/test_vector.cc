
#include "test_headers.h"

TEST(Default_constructor, test_int) {
  s21::vector<int> test;
  std::vector<int> result;
  ASSERT_EQ(test.size(), result.size());
  ASSERT_EQ(test.capacity(), result.capacity());
  ASSERT_EQ(test.data(), result.data());
}

TEST(Default_constructor, test_double) {
  s21::vector<double> test;
  std::vector<double> result;
  ASSERT_EQ(test.size(), result.size());
  ASSERT_EQ(test.capacity(), result.capacity());
  ASSERT_EQ(test.data(), result.data());
}

TEST(Parametrized_constructor, test_empty) {
  s21::vector<int> test(0);
  std::vector<int> result(0);
  ASSERT_EQ(test.size(), result.size());
  ASSERT_EQ(test.capacity(), result.capacity());
  ASSERT_EQ(test.data(), result.data());
}

TEST(Parametrized_constructor, test_params) {
  s21::vector<double> test(5);
  std::vector<double> result(5);
  ASSERT_EQ(test.size(), result.size());
  ASSERT_EQ(test.capacity(), result.capacity());
}

TEST(Initializer_list_constructor, test_empty) {
  std::initializer_list<double> empt;
  s21::vector<double> test(empt);
  std::vector<double> result(empt);
  ASSERT_EQ(test.size(), result.size());
  ASSERT_EQ(test.capacity(), result.capacity());
  ASSERT_EQ(test.data(), result.data());
}

TEST(Initializer_list_constructor, test_params) {
  std::initializer_list<double> params = {1.2, 3.4, 5.678};
  s21::vector<double> test{params};
  std::vector<double> result{params};
  ASSERT_EQ(test.size(), result.size());
  ASSERT_EQ(test.capacity(), result.capacity());
  for (size_t i = 0; i < test.size(); ++i) ASSERT_DOUBLE_EQ(test[i], result[i]);
}

TEST(Copy_constructor, test_params) {
  std::initializer_list<double> params = {1.2, 3.4, 5.678};
  s21::vector<double> temp1{params}, test(temp1);
  std::vector<double> temp2{params}, result(temp2);
  ASSERT_TRUE(temp1 == test);
  ASSERT_EQ(test.size(), result.size());
  ASSERT_EQ(test.capacity(), result.capacity());
  for (size_t i = 0; i < test.size(); ++i) ASSERT_DOUBLE_EQ(test[i], result[i]);
}

TEST(Move_constructor, test_params) {
  std::initializer_list<double> params = {1.2, 3.4, 5.678};
  s21::vector<double> temp1{params}, test(std::move(temp1));
  std::vector<double> temp2{params}, result(std::move(temp2));
  ASSERT_TRUE(temp1 != test);
  ASSERT_EQ(test.size(), result.size());
  ASSERT_EQ(test.capacity(), result.capacity());
  for (size_t i = 0; i < test.size(); ++i) ASSERT_DOUBLE_EQ(test[i], result[i]);
  ASSERT_EQ(temp1.size(), temp2.size());
  ASSERT_EQ(temp1.capacity(), temp2.capacity());
  for (size_t i = 0; i < temp1.size(); ++i)
    ASSERT_DOUBLE_EQ(temp1[i], temp2[i]);
}

TEST(Copy_assignment_operator, test_params) {
  std::initializer_list<double> params = {1.2, 3.4, 5.678};
  s21::vector<double> temp1{params}, test;
  test = temp1;
  std::vector<double> temp2{params}, result;
  result = temp2;
  ASSERT_TRUE(temp1 == test);
  ASSERT_EQ(test.size(), result.size());
  ASSERT_EQ(test.capacity(), result.capacity());
  for (size_t i = 0; i < test.size(); ++i) ASSERT_DOUBLE_EQ(test[i], result[i]);
}

TEST(Move_assignment_operator, test_params) {
  std::initializer_list<double> params = {1.2, 3.4, 5.678};
  s21::vector<double> temp1{params}, test;
  test = std::move(temp1);
  std::vector<double> temp2{params}, result;
  result = std::move(temp2);
  ASSERT_TRUE(temp1 != test);
  ASSERT_EQ(test.size(), result.size());
  ASSERT_EQ(test.capacity(), result.capacity());
  for (size_t i = 0; i < test.size(); ++i) ASSERT_DOUBLE_EQ(test[i], result[i]);
  ASSERT_EQ(temp1.size(), temp2.size());
  ASSERT_EQ(temp1.capacity(), temp2.capacity());
  for (size_t i = 0; i < temp1.size(); ++i)
    ASSERT_DOUBLE_EQ(temp1[i], temp2[i]);
}

TEST(At_method, test_params) {
  std::initializer_list<double> params = {1.2, 3.4, 5.678};
  s21::vector<double> test(params);
  std::vector<double> result(params);
  ASSERT_DOUBLE_EQ(test.at(1), result.at(1));
  ASSERT_ANY_THROW(test.at(test.size()));
}

TEST(Front_method, test_params) {
  std::initializer_list<double> params = {1.2, 3.4, 5.678};
  s21::vector<double> test(params);
  std::vector<double> result(params);
  ASSERT_DOUBLE_EQ(test.front(), result.front());
}

TEST(Back_method, test_params) {
  std::initializer_list<double> params = {1.2, 3.4, 5.678};
  s21::vector<double> test(params);
  std::vector<double> result(params);
  ASSERT_DOUBLE_EQ(test.back(), result.back());
}

TEST(Data_method, test_params) {
  std::initializer_list<double> params = {1.2, 3.4, 5.678};
  s21::vector<double> test(params);
  std::vector<double> result(params);
  for (size_t i = 0; i < test.size(); ++i)
    ASSERT_DOUBLE_EQ(test.data()[i], result.data()[i]);
}

TEST(Begin_method, test_params) {
  std::initializer_list<double> params = {1.2, 3.4, 5.678};
  s21::vector<double> test(params);
  std::vector<double> result(params);
  ASSERT_DOUBLE_EQ(*test.begin(), *result.begin());
}

TEST(End_method, test_params) {
  std::initializer_list<double> params = {1.2, 3.4, 5.678};
  s21::vector<double> test(params);
  std::vector<double> result(params);
  ASSERT_DOUBLE_EQ(*(test.end() - 1), *(result.end() - 1));
}

TEST(Empty_method, test) {
  s21::vector<int> test1, test2{1, 2, 3};
  ASSERT_TRUE(test1.empty());
  ASSERT_FALSE(test2.empty());
}

TEST(Size_method, test_params) {
  std::initializer_list<double> params = {1.2, 3.4, 5.678};
  s21::vector<double> test(params);
  std::vector<double> result(params);
  ASSERT_EQ(test.size(), result.size());
}

TEST(Max_size_method, test_params) {
  std::initializer_list<double> params = {1.2, 3.4, 5.678};
  s21::vector<double> test(params);
  std::vector<double> result(params);
  ASSERT_EQ(test.max_size(), result.max_size());
}

TEST(Reserve_method, test_params) {
  std::initializer_list<double> params = {1.2, 3.4, 5.678};
  s21::vector<double> test(params);
  std::vector<double> result(params);
  test.reserve(6);
  result.reserve(6);
  ASSERT_EQ(test.size(), result.size());
  ASSERT_EQ(test.capacity(), result.capacity());
  for (size_t i = 0; i < test.size(); ++i) ASSERT_DOUBLE_EQ(test[i], result[i]);
}

TEST(Capacity_method, test_params) {
  std::initializer_list<double> params = {1.2, 3.4, 5.678};
  s21::vector<double> test(params);
  std::vector<double> result(params);
  ASSERT_EQ(test.capacity(), result.capacity());
}

TEST(Shrink_to_fit_method, test_params) {
  std::initializer_list<double> params = {1.2, 3.4, 5.678};
  s21::vector<double> test(params);
  std::vector<double> result(params);
  test.reserve(6);
  test.shrink_to_fit();
  result.reserve(6);
  result.shrink_to_fit();
  ASSERT_EQ(test.capacity(), result.capacity());
}

TEST(Clear_method, test_params) {
  std::initializer_list<double> params = {1.2, 3.4, 5.678};
  s21::vector<double> test(params);
  std::vector<double> result(params);
  test.clear();
  result.clear();
  ASSERT_EQ(test.size(), result.size());
  ASSERT_EQ(test.capacity(), result.capacity());
}

TEST(Insert_method, test_params) {
  std::initializer_list<double> params = {1.2, 3.4, 5.678};
  s21::vector<double> test(params);
  std::vector<double> result(params);
  test.insert(test.begin(), 324.32);
  result.insert(result.begin(), 324.32);
  ASSERT_EQ(test.size(), result.size());
  ASSERT_EQ(test.capacity(), result.capacity());
  for (size_t i = 0; i < test.size(); ++i) ASSERT_DOUBLE_EQ(test[i], result[i]);
}

TEST(Erase_method, test_params) {
  std::initializer_list<double> params = {1.2, 3.4, 5.678};
  s21::vector<double> test(params);
  std::vector<double> result(params);
  test.erase(test.begin() + 1);
  result.erase(result.begin() + 1);
  ASSERT_EQ(test.size(), result.size());
  ASSERT_EQ(test.capacity(), result.capacity());
  for (size_t i = 0; i < test.size(); ++i) ASSERT_DOUBLE_EQ(test[i], result[i]);
}

TEST(Push_back_method, test_params) {
  std::initializer_list<double> params = {1.2, 3.4, 5.678};
  s21::vector<double> test(params);
  std::vector<double> result(params);
  test.push_back(2.28);
  result.push_back(2.28);
  ASSERT_EQ(test.size(), result.size());
  ASSERT_EQ(test.capacity(), result.capacity());
  for (size_t i = 0; i < test.size(); ++i) ASSERT_DOUBLE_EQ(test[i], result[i]);
}

TEST(Pop_back_method, test_params) {
  std::initializer_list<double> params = {1.2, 3.4, 5.678};
  s21::vector<double> test(params);
  std::vector<double> result(params);
  test.pop_back();
  result.pop_back();
  ASSERT_EQ(test.size(), result.size());
  ASSERT_EQ(test.capacity(), result.capacity());
  for (size_t i = 0; i < test.size(); ++i) ASSERT_DOUBLE_EQ(test[i], result[i]);
}

TEST(Swap_method, test_params) {
  std::initializer_list<int> params1 = {1, 2, 3}, params2 = {4, 5, 6};
  s21::vector<int> test1(params1), test2(params2);
  std::vector<int> result1(params1), result2(params2);
  test1.swap(test2);
  result1.swap(result2);
  ASSERT_EQ(test1.size(), result1.size());
  ASSERT_EQ(test1.capacity(), result1.capacity());
  for (size_t i = 0; i < test1.size(); ++i)
    ASSERT_DOUBLE_EQ(test1[i], result1[i]);
  ASSERT_EQ(test2.size(), result2.size());
  ASSERT_EQ(test2.capacity(), result2.capacity());
  for (size_t i = 0; i < test2.size(); ++i)
    ASSERT_DOUBLE_EQ(test2[i], result2[i]);
}

TEST(Brackets_operator, test_params) {
  std::initializer_list<double> params = {1.2, 3.4, 5.678};
  s21::vector<double> test(params);
  for (size_t i = 0; i < test.size(); ++i)
    ASSERT_DOUBLE_EQ(test[i], test.data()[i]);
}

TEST(Comparison_operators, test_params) {
  std::initializer_list<int> params1 = {1, 2, 3}, params2 = {1, 2, 4};
  s21::vector<int> test1(params1), test2(params2);
  std::vector<int> result1(params1), result2(params2);
  ASSERT_EQ(test1 == test1, result1 == result1);
  ASSERT_EQ(test1 != test2, result1 != result2);
  ASSERT_EQ(test1 > test2, result1 > result2);
  ASSERT_EQ(test2 >= test1, result2 >= result1);
  ASSERT_EQ(test1 < test2, result1 < result2);
  ASSERT_EQ(test2 <= test1, result2 <= result1);
}
