#include "test_headers.h"

TEST(test_container, deque_test_1) {
  s21::deque<int> s21_deque;
  std::deque<int> orig_deque;
  s21_deque.push_front(12);
  s21_deque.push_front(75);
  s21_deque.push_back(13);
  s21_deque.push_back(532);

  orig_deque.push_front(12);
  orig_deque.push_front(75);
  orig_deque.push_back(13);
  orig_deque.push_back(532);

  ASSERT_TRUE(s21_deque.back() == orig_deque.back());
  ASSERT_TRUE(s21_deque.front() == orig_deque.front());
  ASSERT_TRUE(s21_deque.empty() == orig_deque.empty());

  orig_deque.pop_back();
  s21_deque.pop_back();
  ASSERT_TRUE(s21_deque.back() == orig_deque.back());

  orig_deque.pop_back();
  s21_deque.pop_back();
  ASSERT_TRUE(s21_deque.back() == orig_deque.back());

  orig_deque.pop_back();
  s21_deque.pop_back();
  ASSERT_TRUE(s21_deque.back() == orig_deque.back());

  orig_deque.pop_back();
  s21_deque.pop_back();
  ASSERT_TRUE(s21_deque.empty() == orig_deque.empty());
}

TEST(test_container, deque_test_2) {
  s21::deque<int> s21_deque;
  std::deque<int> orig_deque;
  s21_deque.push_front(12);
  s21_deque.push_front(75);
  s21_deque.push_back(13);
  s21_deque.push_back(532);
  s21_deque.push_front(1345);
  s21_deque.push_front(99);

  orig_deque.push_front(12);
  orig_deque.push_front(75);
  orig_deque.push_back(13);
  orig_deque.push_back(532);
  orig_deque.push_front(1345);
  orig_deque.push_front(99);

  ASSERT_TRUE(s21_deque.back() == orig_deque.back());
  ASSERT_TRUE(s21_deque.front() == orig_deque.front());
  ASSERT_TRUE(s21_deque.empty() == orig_deque.empty());

  orig_deque.pop_front();
  s21_deque.pop_front();
  ASSERT_TRUE(s21_deque.back() == orig_deque.back());
  ASSERT_TRUE(s21_deque.front() == orig_deque.front());
  ASSERT_TRUE(s21_deque.empty() == orig_deque.empty());

  orig_deque.pop_front();
  s21_deque.pop_front();
  ASSERT_TRUE(s21_deque.back() == orig_deque.back());
  ASSERT_TRUE(s21_deque.front() == orig_deque.front());
  ASSERT_TRUE(s21_deque.empty() == orig_deque.empty());

  orig_deque.push_front(12);
  s21_deque.push_front(12);
  ASSERT_TRUE(s21_deque.back() == orig_deque.back());
  ASSERT_TRUE(s21_deque.front() == orig_deque.front());
  ASSERT_TRUE(s21_deque.empty() == orig_deque.empty());
}

TEST(test_container, deque_test_3) {
  s21::deque<int> s21_deque;
  std::deque<int> orig_deque;
  s21_deque.push_front(12);
  s21_deque.push_front(75);
  s21_deque.push_back(13);
  s21_deque.push_back(532);
  s21_deque.push_front(1345);
  s21_deque.push_front(99);

  orig_deque.push_front(12);
  orig_deque.push_front(75);
  orig_deque.push_back(13);
  orig_deque.push_back(532);
  orig_deque.push_front(1345);
  orig_deque.push_front(99);

  ASSERT_TRUE(s21_deque.size() == orig_deque.size());

  s21_deque.pop_back();
  orig_deque.pop_back();
  ASSERT_TRUE(s21_deque.size() == orig_deque.size());

  s21_deque.pop_front();
  orig_deque.pop_front();
  ASSERT_TRUE(s21_deque.size() == orig_deque.size());

  s21_deque.pop_back();
  orig_deque.pop_back();
  ASSERT_TRUE(s21_deque.size() == orig_deque.size());

  s21_deque.pop_front();
  orig_deque.pop_front();
  ASSERT_TRUE(s21_deque.size() == orig_deque.size());

  s21_deque.pop_back();
  orig_deque.pop_back();
  ASSERT_TRUE(s21_deque.size() == orig_deque.size());

  s21_deque.pop_front();
  orig_deque.pop_front();
  ASSERT_TRUE(s21_deque.size() == orig_deque.size());
}

TEST(test_container, deque_test_4) {
  s21::deque<int> s21_deque;
  std::deque<int> orig_deque;
  s21_deque.push_back(144);
  s21_deque.push_front(12);
  s21_deque.push_front(75);
  s21_deque.push_back(13);
  s21_deque.push_back(532);
  s21_deque.push_front(1345);
  s21_deque.push_front(99);

  orig_deque.push_back(144);
  orig_deque.push_front(12);
  orig_deque.push_front(75);
  orig_deque.push_back(13);
  orig_deque.push_back(532);
  orig_deque.push_front(1345);
  orig_deque.push_front(99);

  ASSERT_TRUE(s21_deque.size() == orig_deque.size());
  ASSERT_TRUE(s21_deque.back() == orig_deque.back());

  s21_deque.pop_back();
  orig_deque.pop_back();

  ASSERT_TRUE(s21_deque.back() == orig_deque.back());
  ASSERT_TRUE(s21_deque.size() == orig_deque.size());
}

TEST(test_container, deque_test_swap) {
  s21::deque<int> s21_deque;
  s21::deque<int> s21_deque1;
  std::deque<int> orig_deque;
  std::deque<int> orig_deque1;

  s21_deque.push_back(12);
  s21_deque.push_front(3);

  s21_deque1.push_front(13);
  s21_deque1.push_front(12);
  s21_deque1.push_front(11);

  orig_deque.push_back(12);
  orig_deque.push_front(3);

  orig_deque1.push_front(13);
  orig_deque1.push_front(12);
  orig_deque1.push_front(11);

  ASSERT_TRUE(s21_deque.size() == orig_deque.size());
  ASSERT_TRUE(s21_deque1.size() == orig_deque1.size());

  s21_deque.swap(s21_deque1);

  ASSERT_TRUE(s21_deque.size() == orig_deque1.size());
  ASSERT_TRUE(s21_deque1.back() == orig_deque.back());

  s21_deque1.pop_front();
  orig_deque.pop_front();

  ASSERT_TRUE(s21_deque1.front() == orig_deque.front());
}

TEST(test_container, deque_test_copy) {
  s21::deque<int> s21_deque;
  std::deque<int> orig_deque;

  s21_deque.push_back(144);
  s21_deque.push_front(12);
  s21_deque.push_front(75);
  s21_deque.push_back(13);
  s21_deque.push_back(532);
  s21_deque.push_front(1345);
  s21_deque.push_front(99);

  orig_deque.push_back(144);
  orig_deque.push_front(12);
  orig_deque.push_front(75);
  orig_deque.push_back(13);
  orig_deque.push_back(532);
  orig_deque.push_front(1345);
  orig_deque.push_front(99);

  s21::deque<int> s21_deque1 = s21_deque;
  s21::deque<int> s21_deque2(s21_deque);

  ASSERT_TRUE(s21_deque1.back() == orig_deque.back());
  ASSERT_TRUE(s21_deque1.front() == orig_deque.front());
  ASSERT_TRUE(s21_deque1.empty() == orig_deque.empty());

  ASSERT_TRUE(s21_deque2.back() == orig_deque.back());
  ASSERT_TRUE(s21_deque2.front() == orig_deque.front());
  ASSERT_TRUE(s21_deque2.empty() == orig_deque.empty());

  orig_deque.pop_front();
  s21_deque1.pop_front();
  ASSERT_TRUE(s21_deque1.back() == orig_deque.back());
  ASSERT_TRUE(s21_deque1.front() == orig_deque.front());
  ASSERT_TRUE(s21_deque1.empty() == orig_deque.empty());

  orig_deque.pop_front();
  s21_deque1.pop_front();
  ASSERT_TRUE(s21_deque1.back() == orig_deque.back());
  ASSERT_TRUE(s21_deque1.front() == orig_deque.front());
  ASSERT_TRUE(s21_deque1.empty() == orig_deque.empty());
}

TEST(test_container, deque_test_move) {
  s21::deque<int> s21_deque;
  std::deque<int> orig_deque;

  s21_deque.push_back(144);
  s21_deque.push_front(12);
  s21_deque.push_front(75);
  s21_deque.push_back(13);
  s21_deque.push_back(532);
  s21_deque.push_front(1345);
  s21_deque.push_front(99);

  orig_deque.push_back(144);
  orig_deque.push_front(12);
  orig_deque.push_front(75);
  orig_deque.push_back(13);
  orig_deque.push_back(532);
  orig_deque.push_front(1345);
  orig_deque.push_front(99);

  s21::deque<int> s21_deque2 = std::move(s21_deque);
  std::deque<int> orig_deque2 = std::move(orig_deque);

  ASSERT_TRUE(s21_deque.size() == orig_deque.size());
  ASSERT_TRUE(s21_deque.size() == 0);

  ASSERT_TRUE(s21_deque2.front() == orig_deque2.front());
  ASSERT_TRUE(s21_deque2.back() == orig_deque2.back());

  ASSERT_TRUE(s21_deque.empty() == orig_deque.empty());
}

TEST(test_container, deque_test_assign) {
  s21::deque<int> s21_deque;
  std::deque<int> orig_deque;

  s21_deque.push_back(144);
  s21_deque.push_front(12);
  s21_deque.push_front(75);
  s21_deque.push_back(13);
  s21_deque.push_back(532);
  s21_deque.push_front(1345);
  s21_deque.push_front(99);

  orig_deque.push_back(144);
  orig_deque.push_front(12);
  orig_deque.push_front(75);
  orig_deque.push_back(13);
  orig_deque.push_back(532);
  orig_deque.push_front(1345);
  orig_deque.push_front(99);

  s21::deque<int> s21_deque2;
  s21_deque2 = s21_deque;
  // s21_deque2 = s21_deque2;
  std::deque<int> orig_deque2;
  orig_deque2 = orig_deque;

  ASSERT_TRUE(s21_deque2.size() == orig_deque2.size());

  ASSERT_TRUE(s21_deque2.front() == orig_deque2.front());
  ASSERT_TRUE(s21_deque2.back() == orig_deque2.back());

  ASSERT_TRUE(s21_deque.empty() == orig_deque.empty());

  ASSERT_TRUE(s21_deque.front() == orig_deque.front());
  ASSERT_TRUE(s21_deque.back() == orig_deque.back());

  s21_deque2.pop_back();
  orig_deque2.pop_back();
  ASSERT_TRUE(s21_deque2.back() == orig_deque2.back());

  s21_deque2.pop_front();
  orig_deque2.pop_front();
  ASSERT_TRUE(s21_deque2.front() == orig_deque2.front());
}

TEST(test_container, deque_test_assign2) {
  s21::deque<int> s21_deque;
  std::deque<int> orig_deque;

  s21_deque.push_back(144);
  s21_deque.push_front(12);
  s21_deque.push_front(75);
  s21_deque.push_back(13);
  s21_deque.push_back(532);
  s21_deque.push_front(1345);
  s21_deque.push_front(99);

  orig_deque.push_back(144);
  orig_deque.push_front(12);
  orig_deque.push_front(75);
  orig_deque.push_back(13);
  orig_deque.push_back(532);
  orig_deque.push_front(1345);
  orig_deque.push_front(99);

  s21::deque<int> s21_deque2;
  s21_deque2 = std::move(s21_deque);
  std::deque<int> orig_deque2;
  orig_deque2 = std::move(orig_deque);

  ASSERT_TRUE(s21_deque2.size() == orig_deque2.size());

  ASSERT_TRUE(s21_deque2.front() == orig_deque2.front());
  ASSERT_TRUE(s21_deque2.back() == orig_deque2.back());

  s21_deque2.pop_back();
  orig_deque2.pop_back();
  ASSERT_TRUE(s21_deque2.back() == orig_deque2.back());

  s21_deque2.pop_front();
  orig_deque2.pop_front();
  ASSERT_TRUE(s21_deque2.front() == orig_deque2.front());
}

TEST(test_container, deque_test_initlistconst) {
  s21::deque<int> s21_deque{1, 2, 3, 4, 5, 6, 7};
  std::deque<int> orig_deque{1, 2, 3, 4, 5, 6, 7};
  ASSERT_TRUE(s21_deque.size() == orig_deque.size());
  ASSERT_TRUE(s21_deque.back() == orig_deque.back());
  ASSERT_TRUE(s21_deque.front() == orig_deque.front());

  s21_deque.pop_back();
  orig_deque.pop_back();
  ASSERT_TRUE(s21_deque.back() == orig_deque.back());

  s21_deque.pop_back();
  orig_deque.pop_back();
  ASSERT_TRUE(s21_deque.back() == orig_deque.back());
}

TEST(test_container, deque_test_initlistconst2) {
  s21::deque<int> s21_deque = {1, 2, 3, 4, 5, 6, 7};
  std::deque<int> orig_deque = {1, 2, 3, 4, 5, 6, 7};
  ASSERT_TRUE(s21_deque.size() == orig_deque.size());
  ASSERT_TRUE(s21_deque.back() == orig_deque.back());
  ASSERT_TRUE(s21_deque.front() == orig_deque.front());

  s21_deque.pop_back();
  orig_deque.pop_back();
  ASSERT_TRUE(s21_deque.back() == orig_deque.back());

  s21_deque.pop_back();
  orig_deque.pop_back();
  ASSERT_TRUE(s21_deque.back() == orig_deque.back());
}