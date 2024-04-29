#include "../vector.h"

template <class T>
s21::vector<T>& s21::vector<T>::operator=(vector<value_type>& v) noexcept {
  if (__data != v.__data) {
    delete[] __data;
    __size = v.__size;
    __capacity = v.__capacity;
    __data = new (std::nothrow) value_type[__capacity];
    this->__copy_data(v.__data);
  }
  return *this;
}

template <class T>
s21::vector<T>& s21::vector<T>::operator=(vector<value_type>&& v) noexcept {
  if (__data != v.__data) {
    std::swap(__data, v.__data);
    std::swap(__size, v.__size);
    std::swap(__capacity, v.__capacity);
  }
  return *this;
}

template <class T>
T& s21::vector<T>::operator[](size_type i) noexcept {
  return __data[i];
}

template <class T>
const T& s21::vector<T>::operator[](size_type i) const noexcept {
  return __data[i];
}

template <class T>
bool operator==(const s21::vector<T>& lhs, const s21::vector<T>& rhs) {
  return s21::vector<T>::__vector_cmp(lhs, rhs) == 0;
}

template <class T>
bool operator!=(const s21::vector<T>& lhs, const s21::vector<T>& rhs) {
  return s21::vector<T>::__vector_cmp(lhs, rhs) != 0;
}

template <class T>
bool operator<(const s21::vector<T>& lhs, const s21::vector<T>& rhs) {
  return s21::vector<T>::__vector_cmp(lhs, rhs) < 0;
}

template <class T>
bool operator<=(const s21::vector<T>& lhs, const s21::vector<T>& rhs) {
  return s21::vector<T>::__vector_cmp(lhs, rhs) <= 0;
}
template <class T>
bool operator>(const s21::vector<T>& lhs, const s21::vector<T>& rhs) {
  return s21::vector<T>::__vector_cmp(lhs, rhs) > 0;
}

template <class T>
bool operator>=(const s21::vector<T>& lhs, const s21::vector<T>& rhs) {
  return s21::vector<T>::__vector_cmp(lhs, rhs) >= 0;
}