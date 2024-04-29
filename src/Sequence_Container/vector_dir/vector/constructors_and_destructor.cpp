#include "../vector.h"

template <class T>
s21::vector<T>::vector() noexcept : s21::vector<T>::vector(0) {}

template <class T>
s21::vector<T>::vector(size_type n) noexcept : __size{n}, __capacity{n} {
  if (n != 0)
    __data = new (std::nothrow) value_type[__capacity];
  else
    __data = nullptr;
}

template <class T>
s21::vector<T>::vector(std::initializer_list<value_type> const& items) noexcept
    : s21::vector<T>::vector(items.size()) {
  __copy_data(std::data(items));
}

template <class T>
s21::vector<T>::vector(const vector<value_type>& v) noexcept
    : s21::vector<T>::vector(v.__size) {
  __copy_data(v.__data);
}

template <class T>
s21::vector<T>::vector(vector<value_type>&& v) noexcept
    : s21::vector<T>::vector() {
  *this = std::move(v);
}

template <class T>
s21::vector<T>::~vector() noexcept {
  delete[] __data;
}