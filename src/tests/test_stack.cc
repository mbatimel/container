#include "test_headers.h"

TEST(test_container, stack_test_1) {
  s21::stack<int> s21_stack;
  std::stack<int> orig_stack;

  s21_stack.push(12);
  s21_stack.push(143);
  s21_stack.push(56);
  s21_stack.push(45);
  s21_stack.push(742);

  orig_stack.push(12);
  orig_stack.push(143);
  orig_stack.push(56);
  orig_stack.push(45);
  orig_stack.push(742);

  ASSERT_TRUE(s21_stack.top() == orig_stack.top());
  s21_stack.pop();
  orig_stack.pop();

  ASSERT_TRUE(s21_stack.top() == orig_stack.top());
  s21_stack.pop();
  orig_stack.pop();

  ASSERT_TRUE(s21_stack.top() == orig_stack.top());
  s21_stack.pop();
  orig_stack.pop();

  ASSERT_TRUE(s21_stack.top() == orig_stack.top());
  s21_stack.pop();
  orig_stack.pop();
}

TEST(test_container, stack_test_2) {
  s21::stack<int> s21_stack({12, 44, 23, 56, 13, 5});
  std::stack<int> orig_stack({12, 44, 23, 56, 13, 5});

  ASSERT_TRUE(s21_stack.size() == orig_stack.size());
  ASSERT_TRUE(s21_stack.empty() == orig_stack.empty());

  ASSERT_TRUE(s21_stack.top() == orig_stack.top());
  s21_stack.pop();
  orig_stack.pop();

  ASSERT_TRUE(s21_stack.top() == orig_stack.top());
  s21_stack.pop();
  orig_stack.pop();

  ASSERT_TRUE(s21_stack.top() == orig_stack.top());
  s21_stack.pop();
  orig_stack.pop();

  ASSERT_TRUE(s21_stack.top() == orig_stack.top());
  s21_stack.pop();
  orig_stack.pop();
}

TEST(test_container, stack_test_3_swap) {
  s21::stack<int> s21_stack({12, 44, 23, 56, 13, 5});
  std::stack<int> orig_stack({12, 44, 23, 56, 13, 5});

  s21::stack<int> s21_stack2;
  std::stack<int> orig_stack2;

  s21_stack2.push(3);
  s21_stack2.push(34);

  orig_stack2.push(3);
  orig_stack2.push(34);

  s21_stack.swap(s21_stack2);
  orig_stack.swap(orig_stack2);

  ASSERT_TRUE(s21_stack.size() == 2);
  ASSERT_TRUE(s21_stack.size() == orig_stack.size());

  ASSERT_TRUE(s21_stack.top() == orig_stack.top());
  ASSERT_TRUE(s21_stack2.size() == orig_stack2.size());

  ASSERT_TRUE(s21_stack2.top() == orig_stack2.top());
  ASSERT_TRUE(s21_stack2.size() == 6);
}

TEST(test_container, stack_test_copy) {
  s21::stack<int> s21_stack;
  std::stack<int> orig_stack;

  s21_stack.push(144);
  s21_stack.push(12);
  s21_stack.push(75);
  s21_stack.push(13);
  s21_stack.push(532);
  s21_stack.push(1345);
  s21_stack.push(99);

  orig_stack.push(144);
  orig_stack.push(12);
  orig_stack.push(75);
  orig_stack.push(13);
  orig_stack.push(532);
  orig_stack.push(1345);
  orig_stack.push(99);

  s21::stack<int> s21_stack1 = s21_stack;
  s21::stack<int> s21_stack2(s21_stack);

  ASSERT_TRUE(s21_stack1.top() == orig_stack.top());
  ASSERT_TRUE(s21_stack2.top() == orig_stack.top());
  ASSERT_TRUE(s21_stack1.empty() == orig_stack.empty());
  ASSERT_TRUE(s21_stack1.size() == orig_stack.size());
  ASSERT_TRUE(s21_stack2.size() == s21_stack1.size());
  ASSERT_TRUE(s21_stack2.empty() == orig_stack.empty());

  orig_stack.pop();
  s21_stack1.pop();
  s21_stack2.pop();

  ASSERT_TRUE(s21_stack1.top() == orig_stack.top());
  ASSERT_TRUE(s21_stack2.top() == orig_stack.top());
  ASSERT_TRUE(s21_stack1.empty() == orig_stack.empty());
  ASSERT_TRUE(s21_stack1.size() == orig_stack.size());
  ASSERT_TRUE(s21_stack2.size() == s21_stack1.size());
  ASSERT_TRUE(s21_stack2.empty() == orig_stack.empty());

  orig_stack.pop();
  s21_stack1.pop();
  s21_stack2.pop();

  ASSERT_TRUE(s21_stack1.top() == orig_stack.top());
  ASSERT_TRUE(s21_stack2.top() == orig_stack.top());
  ASSERT_TRUE(s21_stack1.empty() == orig_stack.empty());
  ASSERT_TRUE(s21_stack1.size() == orig_stack.size());
  ASSERT_TRUE(s21_stack2.size() == s21_stack1.size());
  ASSERT_TRUE(s21_stack2.empty() == orig_stack.empty());
}

TEST(test_container, stack_test_move) {
  s21::stack<int> s21_stack;
  std::stack<int> orig_stack;

  s21_stack.push(144);
  s21_stack.push(12);
  s21_stack.push(75);
  s21_stack.push(13);
  s21_stack.push(532);
  s21_stack.push(1345);
  s21_stack.push(99);

  orig_stack.push(144);
  orig_stack.push(12);
  orig_stack.push(75);
  orig_stack.push(13);
  orig_stack.push(532);
  orig_stack.push(1345);
  orig_stack.push(99);

  s21::stack<int> s21_stack2 = std::move(s21_stack);
  std::stack<int> orig_stack2 = std::move(orig_stack);

  ASSERT_TRUE(s21_stack.size() == orig_stack.size());
  ASSERT_TRUE(s21_stack.size() == 0);

  ASSERT_TRUE(s21_stack2.top() == orig_stack2.top());
  ASSERT_TRUE(s21_stack2.size() == orig_stack2.size());

  ASSERT_TRUE(s21_stack.empty() == orig_stack.empty());
}

TEST(test_container, stack_test_assign) {
  s21::stack<int> s21_stack;
  std::stack<int> orig_stack;

  s21_stack.push(144);
  s21_stack.push(12);
  s21_stack.push(75);
  s21_stack.push(13);
  s21_stack.push(532);
  s21_stack.push(1345);
  s21_stack.push(99);

  orig_stack.push(144);
  orig_stack.push(12);
  orig_stack.push(75);
  orig_stack.push(13);
  orig_stack.push(532);
  orig_stack.push(1345);
  orig_stack.push(99);

  s21::stack<int> s21_stack2;
  s21_stack2 = s21_stack;
  //   s21_stack2 = s21_stack2;
  std::stack<int> orig_stack2;
  orig_stack2 = orig_stack;

  ASSERT_TRUE(s21_stack2.size() == orig_stack2.size());

  ASSERT_TRUE(s21_stack2.top() == orig_stack2.top());
  ASSERT_TRUE(s21_stack2.top() == s21_stack.top());

  ASSERT_TRUE(s21_stack.empty() == orig_stack.empty());
  ASSERT_TRUE(s21_stack2.empty() == orig_stack2.empty());

  ASSERT_TRUE(s21_stack2.size() == orig_stack2.size());

  s21_stack2.pop();
  orig_stack2.pop();
  ASSERT_TRUE(s21_stack2.top() == orig_stack2.top());

  s21_stack2.pop();
  orig_stack2.pop();
  ASSERT_TRUE(s21_stack2.top() == orig_stack2.top());
}

TEST(test_container, stack_test_assign2) {
  s21::stack<int> s21_stack;
  std::stack<int> orig_stack;

  s21_stack.push(144);
  s21_stack.push(12);
  s21_stack.push(75);
  s21_stack.push(13);
  s21_stack.push(532);
  s21_stack.push(1345);
  s21_stack.push(99);

  orig_stack.push(144);
  orig_stack.push(12);
  orig_stack.push(75);
  orig_stack.push(13);
  orig_stack.push(532);
  orig_stack.push(1345);
  orig_stack.push(99);

  s21::stack<int> s21_stack2;
  s21_stack2 = std::move(s21_stack);
  std::stack<int> orig_stack2;
  orig_stack2 = std::move(orig_stack);

  ASSERT_TRUE(s21_stack2.size() == orig_stack2.size());

  ASSERT_TRUE(s21_stack2.top() == orig_stack2.top());

  ASSERT_TRUE(s21_stack.empty() == orig_stack.empty());
  ASSERT_TRUE(s21_stack2.empty() == orig_stack2.empty());

  ASSERT_TRUE(s21_stack2.size() == orig_stack2.size());

  s21_stack2.pop();
  orig_stack2.pop();
  ASSERT_TRUE(s21_stack2.top() == orig_stack2.top());

  s21_stack2.pop();
  orig_stack2.pop();
  ASSERT_TRUE(s21_stack2.top() == orig_stack2.top());
}

TEST(test_container, insert_many_front) {
  s21::stack<int> s21_stack;
  int arr[] = {1, 6, 5, 4, 12, 99, 1345, 532, 13, 75, 12, 144};

  s21_stack.push(144);
  s21_stack.push(12);
  s21_stack.push(75);
  s21_stack.push(13);
  s21_stack.push(532);
  s21_stack.push(1345);
  s21_stack.push(99);
  s21_stack.insert_many_front(12, 4, 5, 6, 1);
  int i = 0;
  while (!s21_stack.empty()) {
    ASSERT_TRUE(s21_stack.top() == arr[i]);
    i++;
    s21_stack.pop();
  }
}