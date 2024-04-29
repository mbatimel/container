#include <gtest/gtest.h>

#include <queue>

#include "test_headers.h"

TEST(test_container, queue_test_1) {
  s21::queue<int> s21_queue;
  std::queue<int> orig_queue;

  s21_queue.push(12);
  s21_queue.push(143);
  s21_queue.push(56);
  s21_queue.push(45);
  s21_queue.push(742);

  orig_queue.push(12);
  orig_queue.push(143);
  orig_queue.push(56);
  orig_queue.push(45);
  orig_queue.push(742);

  ASSERT_TRUE(s21_queue.front() == 12);
  ASSERT_TRUE(s21_queue.back() == 742);

  ASSERT_TRUE(s21_queue.front() == orig_queue.front());
  ASSERT_TRUE(s21_queue.back() == orig_queue.back());
  s21_queue.pop();
  orig_queue.pop();

  ASSERT_TRUE(s21_queue.front() == orig_queue.front());
  ASSERT_TRUE(s21_queue.back() == orig_queue.back());
  s21_queue.pop();
  orig_queue.pop();

  ASSERT_TRUE(s21_queue.front() == orig_queue.front());
  ASSERT_TRUE(s21_queue.back() == orig_queue.back());
  s21_queue.pop();
  orig_queue.pop();

  ASSERT_TRUE(s21_queue.front() == orig_queue.front());
  ASSERT_TRUE(s21_queue.back() == orig_queue.back());
  s21_queue.pop();
  orig_queue.pop();
}

TEST(test_container, queue_test_2) {
  s21::queue<int> s21_queue({12, 44, 23, 56, 13, 5});
  std::queue<int> orig_queue({12, 44, 23, 56, 13, 5});

  ASSERT_TRUE(s21_queue.size() == orig_queue.size());
  ASSERT_TRUE(s21_queue.empty() == orig_queue.empty());

  ASSERT_TRUE(s21_queue.front() == orig_queue.front());
  ASSERT_TRUE(s21_queue.front() == 12);
  s21_queue.pop();
  orig_queue.pop();

  ASSERT_TRUE(s21_queue.front() == orig_queue.front());
  ASSERT_TRUE(s21_queue.front() == 44);
  s21_queue.pop();
  orig_queue.pop();

  ASSERT_TRUE(s21_queue.front() == orig_queue.front());
  ASSERT_TRUE(s21_queue.front() == 23);
  s21_queue.pop();
  orig_queue.pop();

  ASSERT_TRUE(s21_queue.front() == orig_queue.front());
  ASSERT_TRUE(s21_queue.front() == 56);
  s21_queue.pop();
  orig_queue.pop();
}

TEST(test_container, queue_test_swap) {
  s21::queue<int> s21_queue({12, 44, 23, 56, 13, 5});
  std::queue<int> orig_queue({12, 44, 23, 56, 13, 5});

  s21::queue<int> s21_queue2;
  std::queue<int> orig_queue2;

  s21_queue2.push(3);
  s21_queue2.push(34);

  orig_queue2.push(3);
  orig_queue2.push(34);

  s21_queue.swap(s21_queue2);
  orig_queue.swap(orig_queue2);

  ASSERT_TRUE(s21_queue.size() == 2);
  ASSERT_TRUE(s21_queue.size() == orig_queue.size());

  ASSERT_TRUE(s21_queue.front() == orig_queue.front());
  ASSERT_TRUE(s21_queue.back() == orig_queue.back());
  ASSERT_TRUE(s21_queue2.size() == orig_queue2.size());

  ASSERT_TRUE(s21_queue2.front() == orig_queue2.front());
  ASSERT_TRUE(s21_queue2.back() == orig_queue2.back());
  ASSERT_TRUE(s21_queue2.size() == 6);
}

TEST(test_container, queue_test_copy) {
  s21::queue<int> s21_queue;
  std::queue<int> orig_queue;

  s21_queue.push(144);
  s21_queue.push(12);
  s21_queue.push(75);
  s21_queue.push(13);
  s21_queue.push(532);
  s21_queue.push(1345);
  s21_queue.push(99);

  orig_queue.push(144);
  orig_queue.push(12);
  orig_queue.push(75);
  orig_queue.push(13);
  orig_queue.push(532);
  orig_queue.push(1345);
  orig_queue.push(99);

  s21::queue<int> s21_queue1 = s21_queue;
  s21::queue<int> s21_queue2(s21_queue);

  ASSERT_TRUE(s21_queue1.front() == orig_queue.front());
  ASSERT_TRUE(s21_queue2.front() == orig_queue.front());
  ASSERT_TRUE(s21_queue1.back() == orig_queue.back());
  ASSERT_TRUE(s21_queue2.back() == orig_queue.back());
  ASSERT_TRUE(s21_queue1.empty() == orig_queue.empty());
  ASSERT_TRUE(s21_queue1.size() == orig_queue.size());
  ASSERT_TRUE(s21_queue2.size() == s21_queue1.size());
  ASSERT_TRUE(s21_queue2.empty() == orig_queue.empty());

  orig_queue.pop();
  s21_queue1.pop();
  s21_queue2.pop();

  ASSERT_TRUE(s21_queue1.front() == orig_queue.front());
  ASSERT_TRUE(s21_queue2.front() == orig_queue.front());
  ASSERT_TRUE(s21_queue1.back() == orig_queue.back());
  ASSERT_TRUE(s21_queue2.back() == orig_queue.back());
  ASSERT_TRUE(s21_queue1.empty() == orig_queue.empty());
  ASSERT_TRUE(s21_queue1.size() == orig_queue.size());
  ASSERT_TRUE(s21_queue2.size() == s21_queue1.size());
  ASSERT_TRUE(s21_queue2.empty() == orig_queue.empty());

  orig_queue.pop();
  s21_queue1.pop();
  s21_queue2.pop();

  ASSERT_TRUE(s21_queue1.front() == orig_queue.front());
  ASSERT_TRUE(s21_queue2.front() == orig_queue.front());
  ASSERT_TRUE(s21_queue1.back() == orig_queue.back());
  ASSERT_TRUE(s21_queue2.back() == orig_queue.back());
  ASSERT_TRUE(s21_queue1.empty() == orig_queue.empty());
  ASSERT_TRUE(s21_queue1.size() == orig_queue.size());
  ASSERT_TRUE(s21_queue2.size() == s21_queue1.size());
  ASSERT_TRUE(s21_queue2.empty() == orig_queue.empty());
}

TEST(test_container, queue_test_move) {
  s21::queue<int> s21_queue(
      {12, 44, 23, 56, 13, 5, 3, 3, 2, 1, 67, 4, 1487, 22211});
  std::queue<int> orig_queue(
      {12, 44, 23, 56, 13, 5, 3, 3, 2, 1, 67, 4, 1487, 22211});

  s21::queue<int> s21_queue2 = std::move(s21_queue);
  std::queue<int> orig_queue2 = std::move(orig_queue);

  ASSERT_TRUE(s21_queue.size() == orig_queue.size());
  ASSERT_TRUE(s21_queue.size() == 0);

  ASSERT_TRUE(s21_queue2.front() == orig_queue2.front());
  ASSERT_TRUE(s21_queue2.back() == orig_queue2.back());
  ASSERT_TRUE(s21_queue2.size() == orig_queue2.size());
  ASSERT_TRUE(s21_queue2.size() == 14);

  ASSERT_TRUE(s21_queue.empty() == orig_queue.empty());
}

TEST(test_container, queue_test_assign) {
  s21::queue<int> s21_queue(
      {12, 44, 23, 56, 13, 5, 3, 3, 2, 1, 67, 4, 1487, 22211});
  std::queue<int> orig_queue(
      {12, 44, 23, 56, 13, 5, 3, 3, 2, 1, 67, 4, 1487, 22211});

  s21::queue<int> s21_queue2;
  std::queue<int> orig_queue2;

  s21_queue2 = s21_queue;
  // s21_queue2 = s21_queue2;
  orig_queue2 = orig_queue;

  ASSERT_TRUE(s21_queue.size() == orig_queue.size());
  ASSERT_TRUE(s21_queue2.size() == orig_queue2.size());

  ASSERT_TRUE(s21_queue2.front() == orig_queue2.front());
  ASSERT_TRUE(s21_queue2.back() == orig_queue2.back());

  s21_queue2.pop();
  orig_queue2.pop();
  s21_queue.pop();
  orig_queue.pop();
  ASSERT_TRUE(s21_queue2.front() == orig_queue2.front());
  ASSERT_TRUE(s21_queue2.back() == orig_queue2.back());
  ASSERT_TRUE(s21_queue2.front() == 44);
  ASSERT_TRUE(s21_queue2.back() == 22211);

  ASSERT_TRUE(s21_queue.empty() == orig_queue.empty());
  ASSERT_TRUE(s21_queue2.empty() == orig_queue2.empty());
}

// TEST(test_container, queue_test_assign2) {
//   s21::queue<int> s21_queue(
//       {12, 44, 23, 56, 13, 5, 3, 3, 2, 1, 67, 4, 1487, 22211});
//   std::queue<int> orig_queue(
//       {12, 44, 23, 56, 13, 5, 3, 3, 2, 1, 67, 4, 1487, 22211});

//   s21::queue<int> s21_queue2;
//   std::queue<int> orig_queue2;

//   s21_queue2 = std::move(s21_queue);
//   // s21_queue2 = std::move(s21_queue2);
//   orig_queue2 = std::move(orig_queue);
//   ASSERT_TRUE(s21_queue.empty() == orig_queue.empty());
//   ASSERT_TRUE(s21_queue2.empty() == orig_queue2.empty());
//   ASSERT_TRUE(!s21_queue2.empty());
//   ASSERT_TRUE(s21_queue.empty());

//   ASSERT_TRUE(s21_queue.size() == orig_queue.size());
//   ASSERT_TRUE(s21_queue2.size() == orig_queue2.size());

//   ASSERT_TRUE(s21_queue2.front() == orig_queue2.front());
//   ASSERT_TRUE(s21_queue2.back() == orig_queue2.back());

//   s21_queue2.pop();
//   orig_queue2.pop();
//   s21_queue.pop();
//   orig_queue.pop();
//   ASSERT_TRUE(s21_queue2.front() == orig_queue2.front());
//   ASSERT_TRUE(s21_queue2.back() == orig_queue2.back());
//   ASSERT_TRUE(s21_queue2.front() == 44);
//   ASSERT_TRUE(s21_queue2.back() == 22211);
// }

TEST(test_container, insert_many_back) {
  s21::queue<int> s21_queue;
  int arr[] = {144, 12, 75, 13, 532, 1345, 99, 12, 4, 5, 6, 1};

  s21_queue.push(144);
  s21_queue.push(12);
  s21_queue.push(75);
  s21_queue.push(13);
  s21_queue.push(532);
  s21_queue.push(1345);
  s21_queue.push(99);
  s21_queue.insert_many_back(12, 4, 5, 6, 1);
  int i = 0;
  while (!s21_queue.empty()) {
    ASSERT_TRUE(s21_queue.front() == arr[i]);
    i++;
    s21_queue.pop();
  }
}