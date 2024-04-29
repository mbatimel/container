#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>

#include "s21_vector.h"

template <class T>
class s21::vector {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = T*;
  using const_iterator = const T*;
  using size_type = size_t;

  explicit vector() noexcept;
  vector(size_type n) noexcept;
  vector(std::initializer_list<value_type> const& items) noexcept;
  explicit vector(const vector<value_type>& v) noexcept;
  explicit vector(vector<value_type>&& v) noexcept;
  ~vector() noexcept;
  vector<value_type>& operator=(vector<value_type>& v) noexcept;
  vector<value_type>& operator=(vector<value_type>&& v) noexcept;

  reference at(size_type i);
  const_reference front() const noexcept;
  const_reference back() const noexcept;
  T* data() noexcept;

  iterator begin() noexcept;
  iterator end() noexcept;

  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;
  void reserve(size_type new_capacity) noexcept;
  size_type capacity() const noexcept;
  void shrink_to_fit() noexcept;

  void clear() noexcept;
  iterator insert(iterator pos, const_reference value) noexcept;
  void erase(iterator pos) noexcept;
  void push_back(const_reference value) noexcept;
  void pop_back() noexcept;
  void swap(vector& other) noexcept;

  reference operator[](size_type i) noexcept;
  const_reference operator[](size_type i) const noexcept;

  static int __vector_cmp(const vector<value_type>& lhs,
                          const vector<value_type>& rhs);

 private:
  size_type __size, __capacity;
  iterator __data;

  void __copy_data(const_iterator data) noexcept;
};

template <class T>
bool operator==(const s21::vector<T>& lhs, const s21::vector<T>& rhs);
template <class T>
bool operator!=(const s21::vector<T>& lhs, const s21::vector<T>& rhs);
template <class T>
bool operator<(const s21::vector<T>& lhs, const s21::vector<T>& rhs);
template <class T>
bool operator<=(const s21::vector<T>& lhs, const s21::vector<T>& rhs);
template <class T>
bool operator>(const s21::vector<T>& lhs, const s21::vector<T>& rhs);
template <class T>
bool operator>=(const s21::vector<T>& lhs, const s21::vector<T>& rhs);

#include "vector/constructors_and_destructor.cpp"
#include "vector/functions.cpp"
#include "vector/methods.cpp"
#include "vector/operators.cpp"

#endif