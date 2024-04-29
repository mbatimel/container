#ifndef VECTOR_CONTAINER_H
#define VECTOR_CONTAINER_H

#include "s21_vector.h"

template <class T>
class s21::sequence_container : public s21::container {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = T*;
  using const_iterator = const T*;
  using size_type = size_t;

  virtual sequence_container() = 0;
  virtual sequence_container(size_type n) = 0;
  virtual sequence_container(
      std::initializer_list<value_type> const& items) = 0;
  virtual sequence_container(const s21::sequence_container& s) = 0;
  virtual sequence_container(s21::sequence_container&& s) = 0;
  virtual ~sequence_container() = 0;
  virtual sequence_container operator=(s21::sequence_container& s) = 0;
  virtual sequence_container operator=(s21::sequence_container&& s) = 0;

  virtual size_type size() = 0;
  virtual void resize(size_type new_size, const value_type& value) = 0;
  virtual bool empty() = 0;
  virtual void insert(iterator it, const value_type& value) = 0;
  virtual void insert(iterator it, size_type size, const value_type& value) = 0;
  template <class IT>
  virtual void insert(iterator it, IT first, IT last) = 0;
  virtual void erase(iterator it) = 0;
  virtual void erase(iterator first, iterator last) = 0;
  virtual void push_back(const value_type& value) = 0;
  virtual void pop() = 0;
  virtual value_type& front() = 0;
  virtual value_type& back() = 0;
};
#endif