#ifndef S21_DEQUE_CONTAINER_H
#define S21_DEQUE_CONTAINER_H

#include <iostream>

namespace s21 {
template <class Type>
class deque {
 public:
  using value_type = Type;
  using reference = Type &;
  using const_reference = const Type &;
  using size_type = std::size_t;

  // Функции
  deque();
  deque(const deque &s);
  deque(deque &&s);
  deque &operator=(const deque &other);
  deque &operator=(deque &&other);
  deque(std::initializer_list<value_type> const &items);
  ~deque();

  // Емкость
  bool empty();
  size_type size();

  // Модификаторы
  void push_back(const_reference data);
  void pop_back();
  void push_front(const_reference data);
  void pop_front();
  void swap(deque &other);

  // Доступ к элементу
  const_reference front() const;
  const_reference back() const;

 private:
  struct Node {
    Type date;
    Node *next;
    Node *previous;
    Node(Type data) {
      date = data;
      next = nullptr;
      previous = nullptr;
    }
  };

  Node *first;
  Node *last;
  unsigned NodeCount;
};

template <class Type>
deque<Type>::deque() {
  NodeCount = 0;
  first = nullptr;
  last = nullptr;
}

template <class Type>
deque<Type>::deque(deque &&s)
    : first(s.first), last(s.last), NodeCount(s.NodeCount) {
  s.first = nullptr;
  s.last = nullptr;
  s.NodeCount = 0;
}

template <class Type>
deque<Type>::deque(std::initializer_list<value_type> const &items) : deque() {
  for (auto &element : items) {
    push_back(element);
  }
}

template <class Type>
deque<Type>::deque(const deque &s) {
  Node *buf = s.first;
  NodeCount = 0;
  first = nullptr;
  last = nullptr;
  while (buf != nullptr) {
    this->push_back(buf->date);
    buf = buf->next;
  }
}

// оператор копирующего присваивания
template <class Type>
deque<Type> &deque<Type>::operator=(const deque &other) {
  if (&other != this) {
    deque<Type> buf(other);
    this->swap(buf);
  }
  return *this;
}

// оператор перемещающего присваивания
template <class Type>
deque<Type> &deque<Type>::operator=(deque &&other) {
  if (&other != this) {
    this->swap(other);
  }
  return *this;
}

template <class Type>
bool deque<Type>::empty() {
  bool res = false;
  if (NodeCount == 0) {
    res = true;
  }
  return res;
}

template <class Type>
void deque<Type>::swap(deque &other) {
  std::swap(first, other.first);
  std::swap(last, other.last);
  std::swap(NodeCount, other.NodeCount);
}

template <class Type>
typename deque<Type>::size_type deque<Type>::size() {
  return NodeCount;
}

template <class Type>
deque<Type>::~deque() {
  while (!empty()) {
    this->pop_front();
  }
}

template <class Type>
void deque<Type>::push_back(const_reference data) {
  Node *new_elem = new Node(data);
  if (last != nullptr) {
    last->next = new_elem;
    new_elem->previous = last;
    new_elem->next = nullptr;
    last = new_elem;
  } else {
    last = new_elem;
    first = new_elem;
  }
  NodeCount += 1;
}

template <class Type>
typename deque<Type>::const_reference deque<Type>::back() const {
  return last->date;
}

template <class Type>
void deque<Type>::push_front(const_reference data) {
  Node *new_elem = new Node(data);
  if (first != nullptr) {
    first->previous = new_elem;
    new_elem->next = first;
    new_elem->previous = nullptr;
    first = new_elem;
  } else {
    first = new_elem;
    last = new_elem;
  }
  NodeCount += 1;
}

template <class Type>
void deque<Type>::pop_back() {
  if (last != nullptr) {
    Node *pop_elem = last;
    last = pop_elem->previous;
    if (last != nullptr) {
      last->next = nullptr;
    } else {
      first = nullptr;
    }
    delete pop_elem;
    NodeCount -= 1;
  }
}

template <class Type>
void deque<Type>::pop_front() {
  if (first != nullptr) {
    Node *pop_element = first;
    first = pop_element->next;
    if (first == nullptr) {
      last = nullptr;
    } else {
      first->previous = nullptr;
    }
    delete pop_element;
    NodeCount -= 1;
  }
}

template <class Type>
typename deque<Type>::const_reference deque<Type>::front() const {
  return first->date;
}
}  // namespace s21

#endif