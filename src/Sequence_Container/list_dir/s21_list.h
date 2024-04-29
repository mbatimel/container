#ifndef S21_CONTAINER_LIST_H
#define S21_CONTAINER_LIST_H
#include <initializer_list>
#include <iostream>
#include <limits>
#include <vector>
namespace s21 {
template <typename T>
class list {
 public:
  /*__________________List Member type________________________*/

  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;

 private:
  struct Node {
    value_type value_;
    Node *prev, *next;
    Node(value_type value) : value_(value), prev(nullptr), next(nullptr) {}
  };
  Node* head_;
  Node* tail_;
  Node* end_;
  size_type size_;

 public:
  template <typename value_type>
  class ListIterator {
   public:
    ListIterator() { ptr_ = nullptr; }
    ListIterator(Node* ptr) : ptr_(ptr){};

    reference operator*() { return this->ptr_->value_; }

    ListIterator operator++(int) {
      ListIterator it = *this;
      ptr_ = ptr_->next;
      return it;
    }

    ListIterator operator--(int) {
      ListIterator it = *this;
      ptr_ = ptr_->prev;
      return it;
    }

    ListIterator& operator++() {
      ptr_ = ptr_->next;
      return *this;
    }

    ListIterator& operator--() {
      ptr_ = ptr_->prev;
      return *this;
    }

    ListIterator operator+(const size_type value) {
      Node* tmp = ptr_;
      for (size_type i = 0; i < value; i++) {
        tmp = tmp->next;
      }

      ListIterator res(tmp);
      return res;
    }

    ListIterator operator-(const size_type value) {
      Node* tmp = ptr_;
      for (size_type i = 0; i < value; i++) {
        tmp = tmp->prev;
      }
      ListIterator res(tmp);
      return res;
    }

    bool operator==(ListIterator other) { return this->ptr_ == other.ptr_; }
    bool operator!=(ListIterator other) { return this->ptr_ != other.ptr_; }

   private:
    Node* ptr_ = nullptr;
    friend class list<value_type>;
  };  // end class ListIterator

  template <typename value_type>
  class ListConstIterator : public ListIterator<value_type> {
   public:
    ListConstIterator(ListIterator<T> other) : ListIterator<T>(other) {}
    const T& operator*() { return ListIterator<T>::operator*(); }
  };  // end class ListConstIterator

  using iterator = ListIterator<T>;
  using const_iterator = ListConstIterator<T>;

  /*__________________List Functions_________________________*/

  list() : head_(nullptr), tail_(nullptr), end_(nullptr), size_(0) {
    end_ = new Node(size_);
    change_end();
  }
  list(size_type n) : head_(nullptr), tail_(nullptr), end_(nullptr), size_(0) {
    if (n >= max_size()) {
      throw std::out_of_range("Limit of the container is exceeded");
    }
    end_ = new Node(size_);
    for (size_type i = 0; i < n; ++i) {
      push_back(value_type());
    }
    change_end();
  }
  list(std::initializer_list<value_type> const& items)
      : head_(nullptr), tail_(nullptr), end_(nullptr), size_(0) {
    end_ = new Node(size_);
    for (const auto& item : items) {
      push_back(item);
      change_end();
    }
  }
  list(const list& l)
      : head_(nullptr), tail_(nullptr), end_(nullptr), size_(0) {
    end_ = new Node(size_);
    this->copy(l);
  }
  list(list&& l) : head_(nullptr), tail_(nullptr), end_(nullptr), size_(0) {
    swap(l);
  }
  ~list() {
    clear();
    delete end_;
  }

  list& operator=(list&& l) {
    if (this != &l) {
      clear();
      swap(l);
    }
    return *this;
  }

  /*__________________List Element access___________________*/
  const_reference front() { return !head_ ? end_->value_ : head_->value_; }
  const_reference back() { return !end_ ? end_->value_ : tail_->value_; }

  /*__________________List Iterators________________________*/
  iterator begin() { return !head_ ? iterator(end_) : iterator(head_); }

  const_iterator begin() const {
    return !head_ ? const_iterator(end_) : const_iterator(head_);
  }
  iterator end() { return iterator(end_); }
  /*__________________List Capacity________________________*/
  bool empty() { return size_ == 0; }
  size_type size() { return size_; }
  size_type max_size() const noexcept {
    return (std::numeric_limits<size_type>::max() / sizeof(Node));
  }

  /*__________________List Modifiers________________________*/
  void clear() {
    while (!empty()) {
      pop_back();
    }
  }
  iterator insert(iterator pos, const_reference value) {
    Node* current = pos.ptr_;
    Node* add = new Node(value);
    if (empty()) {
      add->next = end_;
      add->prev = end_;
      head_ = add;
      tail_ = add;
    } else {
      if (current == head_) {
        head_ = add;
      } else if (current == end_) {
        tail_ = add;
      }
      add->next = current;
      add->prev = current->prev;
      current->prev->next = add;
      current->prev = add;
    }
    size_++;
    change_end();
    return iterator(add);
  }
  void erase(iterator pos) {
    Node* current = pos.ptr_;
    if (!empty() && current != end_) {
      if (current == head_) {
        if (current->next && current->next != end_) {
          head_ = current->next;
        } else {
          head_ = end_;
        }
      } else if (current == tail_) {
        if (current->prev && current->prev != end_) {
          tail_ = current->prev;
        } else {
          tail_ = end_;
        }
      }
      current->prev->next = current->next;
      current->next->prev = current->prev;
      delete current;
      this->size_--;
    } else {
      throw std::invalid_argument("Invalid argument");
    }
    change_end();
  }
  void push_back(const_reference value) {
    Node* new_node = new Node(value);
    if (empty()) {
      head_ = new_node;
      tail_ = new_node;
    } else {
      new_node->prev = tail_;
      tail_->next = new_node;
      tail_ = new_node;
    }
    size_++;
    change_end();
  }
  void pop_back() {
    if (empty()) {
      throw std::out_of_range("list is empty");
    }
    Node* last_node = tail_;
    if (size_ == 1) {
      head_ = nullptr;
      tail_ = nullptr;
    } else {
      tail_ = last_node->prev;
      tail_->next = nullptr;
    }
    delete last_node;
    size_--;
  }
  void push_front(const_reference value) {
    Node* new_node = new Node(value);
    if (empty()) {
      head_ = new_node;
      tail_ = new_node;
    } else {
      new_node->next = head_;
      head_->prev = new_node;
      head_ = new_node;
    }
    size_++;
    change_end();
  }
  void pop_front() {
    if (empty()) {
      throw std::out_of_range("list is empty");
    }
    Node* first_node = head_;
    if (size_ == 1) {
      head_ = nullptr;
      tail_ = nullptr;
    } else {
      head_ = first_node->next;
      head_->prev = nullptr;
    }
    delete first_node;
    size_--;
    change_end();
  }
  void swap(list& other) {
    using std::swap;
    swap(this->head_, other.head_);
    swap(this->tail_, other.tail_);
    swap(this->size_, other.size_);
    swap(this->end_, other.end_);
  }
  void merge(list& other) {
    if (!this->empty() && !other.empty()) {
      iterator iter_this = this->begin();
      iterator iter_other = other.begin();
      while (iter_this != this->end()) {
        if (iter_other != other.end()) {
          if (iter_this.ptr_->value_ >= iter_other.ptr_->value_) {
            this->insert(iter_this, iter_other.ptr_->value_);
            iter_other++;
          } else {
            iter_this++;
          }
        } else {
          break;
        }
      }
      while (iter_other != other.end()) {
        this->insert(iter_this, iter_other.ptr_->value_);
        iter_other++;
      }
    } else if (this->empty() && !other.empty()) {
      this->copy(other);
    }
    other.clear();
  }
  void splice(const_iterator pos, list& other) {
    if (!other.empty()) {
      for (iterator it = other.begin(); it != other.end(); ++it) {
        insert(pos, *it);
      }
    }
  }
  void reverse() {
    if (!this->empty()) {
      size_type step = 0;
      for (iterator it = this->begin(); step <= this->size(); ++it) {
        step++;
        std::swap(it.ptr_->prev, it.ptr_->next);
      }
      std::swap(head_, tail_);
    }
  }
  void unique() {
    if (!this->empty()) {
      for (iterator it = this->begin(); it != this->end(); it++) {
        if (it.ptr_->value_ == it.ptr_->prev->value_) {
          iterator del_it = (it - 1);
          this->erase(del_it);
        }
      }
    }
  }

  void sort() {
    std::vector<value_type> nums;
    nums.resize(size_);
    int i = 0;
    for (auto it = begin(); it != end(); ++it) {
      nums[i] = *it;
      i++;
    }
    nums.sort();
    i = 0;
    for (auto it = begin(); it != end(); ++it) {
      *it = nums[i];
      i++;
    }
  }
  void copy(const list& l) {
    Node* current = l.head_;
    for (size_type i = 0; i != l.size_; i++) {
      push_back(current->value_);
      current = current->next;
    }
  }
  void change_end() {
    if (end_) {
      end_->next = head_;
      end_->prev = tail_;
      end_->value_ = size();
      if (head_) {
        head_->prev = end_;
      }
      if (tail_) {
        tail_->next = end_;
      }
    }
  }

  template <class... Args>
  iterator insert_many(const_iterator pos, Args&&... args) {
    for (const auto& arg : {args...}) {
      insert(pos, arg);
    }
    return pos;
  }

  template <class... Args>
  void insert_many_back(Args&&... args) {
    for (const auto& arg : {args...}) {
      push_back(arg);
    }
  }

  template <class... Args>
  void insert_many_front(Args&&... args) {
    for (const auto& arg : {args...}) {
      push_front(arg);
    }
  }

};  // end class list
}  // end namespace s21
#endif  // S21_CONTAINER_LIST_H_