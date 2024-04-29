#include "../vector.h"

template <class T>
void s21::vector<T>::__copy_data(const_iterator data) noexcept {
  for (size_type i = 0; i < __size; ++i) __data[i] = data[i];
}

template <class T>
T& s21::vector<T>::at(size_type i) {
  if (i >= __size) throw std::out_of_range("Index is beyond the bounds");
  return __data[i];
}

template <class T>
const T& s21::vector<T>::front() const noexcept {
  return __data[0];
}

template <class T>
const T& s21::vector<T>::back() const noexcept {
  return __data[__size - 1];
}

template <class T>
T* s21::vector<T>::data() noexcept {
  return __data;
}

template <class T>
T* s21::vector<T>::begin() noexcept {
  return __data;
}

template <class T>
T* s21::vector<T>::end() noexcept {
  return __data + __size;
}

template <class T>
bool s21::vector<T>::empty() const noexcept {
  return __size == 0;
}

template <class T>
size_t s21::vector<T>::size() const noexcept {
  return __size;
}

template <class T>
size_t s21::vector<T>::max_size() const noexcept {
  // return static_cast<size_t>(pow(2, 64 - sizeof(T) / 2)) - 1;
  return std::numeric_limits<std::size_t>::max() / sizeof(value_type);
}

template <class T>
void s21::vector<T>::reserve(size_type new_capacity) noexcept {
  if (new_capacity > __capacity) {
    vector<T> new_vector(new_capacity);
    new_vector.__size = __size;
    new_vector.__copy_data(__data);
    *this = std::move(new_vector);
  }
}

template <class T>
size_t s21::vector<T>::capacity() const noexcept {
  return __capacity;
}

template <class T>
void s21::vector<T>::shrink_to_fit() noexcept {
  if (__size < __capacity) {
    vector<T> new_vector(__size);
    new_vector.__copy_data(__data);
    *this = std::move(new_vector);
  }
}

template <class T>
void s21::vector<T>::clear() noexcept {
  for (size_type i = 0; i < __size; ++i) __data[i] = value_type();
  __size = 0;
}

template <class T>
T* s21::vector<T>::insert(iterator pos, const_reference value) noexcept {
  size_type idx = pos - begin();
  if (__size == __capacity) reserve(__capacity ? __capacity * 2 : 1);
  iterator new_pos = begin() + idx;
  for (iterator it = end(); it != new_pos; --it) {
    *it = *(it - 1);
  }

  *new_pos = value;
  ++__size;
  return new_pos;
}

template <class T>
void s21::vector<T>::erase(iterator pos) noexcept {
  *pos = value_type();
  for (iterator it = pos; it < this->end(); ++it) *it = *(it + 1);

  --__size;
}

template <class T>
void s21::vector<T>::push_back(const_reference value) noexcept {
  if (__size == __capacity) reserve(__capacity ? __capacity * 2 : 1);
  __data[__size++] = value;
}

template <class T>
void s21::vector<T>::pop_back() noexcept {
  __data[--__size] = value_type();
}

template <class T>
void s21::vector<T>::swap(vector& other) noexcept {
  *this = std::move(other);
}

template <class T>
int s21::vector<T>::__vector_cmp(const s21::vector<T>& lhs,
                                 const s21::vector<T>& rhs) {
  int result = 0;
  if (lhs.__size != rhs.__size) result = lhs.__size - rhs.__size;
  for (size_t i = 0; i < lhs.__size && !result; ++i)
    result = lhs.__data[i] - rhs.__data[i];
  return result;
}