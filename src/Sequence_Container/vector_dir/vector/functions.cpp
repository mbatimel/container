#include "../vector.h"

template <class T>
int __vector_cmp(const s21::vector<T>& lhs, const s21::vector<T>& rhs) {
  int result = 0;
  if (lhs.__size != rhs.__size) result = lhs.__size - rhs.__size;
  for (size_t i = 0; i < lhs.__size && !result; ++i)
    result = lhs.__data[i] - rhs.__data[i];
  return result;
}