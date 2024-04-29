#ifndef S21_QUEUE_H
#define S21_QUEUE_H

namespace s21 {
template <class Type, class Container = s21::deque<Type>>
class queue {
 public:
  using value_type = Type;
  using reference = Type &;
  using const_reference = const Type &;
  using size_type = std::size_t;
  // Функции
  queue();
  queue(std::initializer_list<value_type> const &items);
  // конструктор копирования
  queue(const queue &q);
  // конструктор перемещения
  queue(queue &&q);
  ~queue();
  // оператор перемещающего присваивания
  queue operator=(queue &&q);
  // оператор копирующего присваивания
  queue &operator=(const queue &other) noexcept;

  // Доступ к элементу
  const_reference front();
  const_reference back();

  // Емкость
  bool empty();
  size_type size();

  //   //Модификаторы
  void push(const_reference value);
  void pop();
  void swap(queue &other);

  template <class... Args>
  void insert_many_back(Args &&...args);

 private:
  Container realqueue;
};

template <class Type, class Container>
queue<Type, Container>::queue() : realqueue() {}

template <class Type, class Container>
queue<Type, Container>::queue(std::initializer_list<value_type> const &items)
    : queue() {
  for (auto &element : items) {
    push(element);
  }
}

// конструктор копирования
template <class Type, class Container>
queue<Type, Container>::queue(const queue &q) : realqueue(q.realqueue) {}
// конструктор перемещения
template <class Type, class Container>
queue<Type, Container>::queue(queue &&q) : realqueue(std::move(q.realqueue)) {}

template <class Type, class Container>
queue<Type, Container>::~queue() {}

template <class Type, class Container>
queue<Type, Container> queue<Type, Container>::operator=(queue &&q) {
  this->realqueue = std::move(q.realqueue);

  return *this;
}

template <class Type, class Container>
queue<Type, Container> &queue<Type, Container>::operator=(
    const queue &other) noexcept {
  this->realqueue = other.realqueue;

  return *this;
}

template <class Type, class Container>
typename queue<Type, Container>::const_reference
queue<Type, Container>::front() {
  return realqueue.front();
}

template <class Type, class Container>
typename queue<Type, Container>::const_reference
queue<Type, Container>::back() {
  return realqueue.back();
}

template <class Type, class Container>
bool queue<Type, Container>::empty() {
  return realqueue.empty();
}

template <class Type, class Container>
typename queue<Type, Container>::size_type queue<Type, Container>::size() {
  return realqueue.size();
}

template <class Type, class Container>
void queue<Type, Container>::push(const_reference value) {
  realqueue.push_back(value);
}

template <class Type, class Container>
void queue<Type, Container>::pop() {
  realqueue.pop_front();
}

template <class Type, class Container>
void queue<Type, Container>::swap(queue &other) {
  std::swap(this->realqueue, other.realqueue);
}

template <class Type, class Container>
template <class... Args>
void queue<Type, Container>::insert_many_back(Args &&...args) {
  (realqueue.push_back(args), ...);
}

}  // namespace s21

#endif