#ifndef S21_ARRAY_CONTAITER_H
#define S21_ARRAY_CONTAITER_H
#include <initializer_list>
#include <iostream>
#include <limits>
namespace s21 {
template <typename T, std::size_t N>
class array {
 public:
  /*_________Array Member type________________*/
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;
  using const_iterator = const T *;
  using iterator = T *;

 private:
  size_type size_ = N;
  value_type mass_[N] = {};

 public:
  /*________Array Member functions__________*/
  array() : size_(N) {}
  array(std::initializer_list<value_type> const &items) : size_(N) {
    if (items.size() != N) {
      throw std::invalid_argument(
          "Initializer list size doesn't match array size");
    }
    std::copy(items.begin(), items.end(), mass_);
  }
  array(const array &a) { std::copy(a.mass_, a.mass_ + N, mass_); }
  array(array &&a) { std::move(a.mass_, a.mass_ + N, mass_); }
  ~array() = default;

  array operator=(const array &a) {
    std::copy(a.mass_, a.mass_ + N, mass_);

    return *this;
  }

  array operator=(array &&a) noexcept {
    for (size_t i = 0; i < N; ++i) {
      mass_[i] = std::move(a.mass_[i]);
    }

    return *this;
  }

  /*__________Array Element access__________*/
  reference at(size_type pos) {
    if (pos >= size_) {
      throw std::out_of_range("pos out of range");
    }
    return this->mass_[pos];
  }
  reference operator[](size_type pos) { return this->mass_[pos]; }
  const_reference front() const { return this->mass_[0]; }
  const_reference back() { return this->mass_[N - 1]; }
  iterator data() { return this->mass_; }
  iterator begin() { return this->mass_; }
  iterator end() { return this->mass_ + N; }

  /*_________Array Capacity________________*/
  bool empty() {
    bool flag = false;
    if (size_ == 0) {
      flag = true;
    }
    return flag;
  }
  size_type size() { return size_; }
  size_type max_size() { return size_; }

  /*________Array Modifiers________________*/
  void swap(array &other) { std::swap_ranges(begin(), end(), other.begin()); }
  void fill(const_reference value) { std::fill(mass_, mass_ + N, value); }
};
}  // namespace s21
#endif  // END S21_ARRAY_CONTAITER_H