#ifndef S21_MAP_H
#define S21_MAP_H

#include <iostream>
#include <limits>
#include <stdexcept>
#include <vector>

#include "../../RBtree/s21_RBtree.h"

namespace s21 {
template <typename Key, typename Value>
class map : public RBtree<Key, Value> {
 public:
  class MapIterator;
  class ConstMapIterator;
  using key_type = Key;
  using mapped_type = Value;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = MapIterator;
  using const_iterator = ConstMapIterator;
  using size_type = size_t;

  // Member functions
  map();
  map(std::initializer_list<value_type> const& items);
  map(const map& m);
  map(map&& other) noexcept;
  // оператор копирующего присваивания
  map& operator=(const map& other);
  // оператор перемещающего присванивания
  map& operator=(map&& other);
  ~map();

  // Element access
  Value& at(const Key& key);
  Value& operator[](const Key& key) noexcept;

  // Iterators
  iterator begin();
  iterator end();

  // Capacity
  bool empty();
  size_type size();
  size_type max_size();

  // Modifiers
  void clear();
  std::pair<iterator, bool> insert(const value_type& value);
  std::pair<iterator, bool> insert(const Key& key, const Value& obj);
  std::pair<iterator, bool> insert_or_assign(const Key& key, const Value& obj);
  void erase(iterator pos);
  void swap(map& other);
  void merge(map& other);
  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args);

  // Lookup
  bool contains(const Key& key);

  class MapIterator : public RBtree<Key, Value>::Iterator {
   public:
    friend class map;
    MapIterator() : RBtree<Key, Value>::Iterator(){};
    MapIterator(Node<Key, Value>* iter_ptr)
        : RBtree<Key, Value>::Iterator(iter_ptr){};
    value_type operator*();
  };
  class ConstMapIterator : public MapIterator,
                           protected RBtree<Key, Value>::Iterator {
   public:
    friend class map;
    ConstMapIterator() : MapIterator(){};
    ConstMapIterator(Node<Key, Value>* iter_ptr) : MapIterator(iter_ptr){};
  };

 private:
  Node<Key, Value>* find(const Key key);
};

// Member functions
template <typename Key, typename Value>
map<Key, Value>::map() : RBtree<Key, Value>() {}

template <typename Key, typename Value>
map<Key, Value>::map(std::initializer_list<value_type> const& items) {
  for (auto& element : items) {
    this->insert(element);
  }
}

template <typename Key, typename Value>
map<Key, Value>::map(const map<Key, Value>& m) : RBtree<Key, Value>(m) {}

template <typename Key, typename Value>
map<Key, Value>::map(map<Key, Value>&& other) noexcept
    : RBtree<Key, Value>(std::move(other)) {}

// оператор копирующего присваивания
template <typename Key, typename Value>
map<Key, Value>& map<Key, Value>::operator=(const map<Key, Value>& other) {
  if (&other != this) {
    map<Key, Value> buf(other);
    swap(buf);
  }
  return *this;
}

// оператор перемещающего присванивания
template <typename Key, typename Value>
map<Key, Value>& map<Key, Value>::operator=(map<Key, Value>&& other) {
  if (&other != this) {
    swap(other);
  }
  other.clear();
  return *this;
}

template <typename Key, typename Value>
map<Key, Value>::~map() {}

// Element access
template <typename Key, typename Value>
Value& map<Key, Value>::operator[](const Key& key) noexcept {
  Node<Key, Value>* buf = this->find(key);
  if (buf == nullptr) {
    std::pair<iterator, bool> res1;
    return this->insert(key, Value()).first.getValue();
  } else {
    return buf->value;
  }
}

template <typename Key, typename Value>
Value& map<Key, Value>::at(const Key& key) {
  Node<Key, Value>* buf = this->find(key);
  if (buf == nullptr) {
    throw std::out_of_range("Key not find");
  }
  return buf->value;
}

// Iterators
template <typename Key, typename Value>
typename map<Key, Value>::iterator map<Key, Value>::begin() {
  return iterator(this->MinNode());
}
template <typename Key, typename Value>
typename map<Key, Value>::iterator map<Key, Value>::end() {
  return iterator(this->MaxNode());
}

// Capacity
template <typename Key, typename Value>
bool map<Key, Value>::empty() {
  bool res = false;
  if (this->root == nullptr) {
    res = true;
  }
  return res;
}

template <typename Key, typename Value>
typename map<Key, Value>::size_type map<Key, Value>::size() {
  size_type res = 1;
  iterator start = this->begin();
  iterator stop = this->end();
  if (!start.iter_is_nullptr()) {
    while (start.getKey() != stop.getKey()) {
      ++start;
      res++;
    }
  } else {
    res = 0;
  }

  return res;
}

template <typename Key, typename Value>
typename map<Key, Value>::size_type map<Key, Value>::max_size() {
  std::allocator<std::pair<key_type, mapped_type>> Alloc;
  return std::allocator_traits<decltype(Alloc)>::max_size(Alloc) / 5;
}

// Modifiers
template <typename Key, typename Value>
void map<Key, Value>::clear() {
  RBtree<Key, Value>::clear();
}

template <typename Key, typename Value>
std::pair<typename map<Key, Value>::iterator, bool> map<Key, Value>::insert(
    const value_type& value) {
  return this->insert(value.first, value.second);
}

template <typename Key, typename Value>
std::pair<typename map<Key, Value>::iterator, bool> map<Key, Value>::insert(
    const Key& key, const Value& obj) {
  std::pair<iterator, bool> result;
  Node<Key, Value>* buf = nullptr;
  if (this->root != nullptr) {
    buf = this->find1(key);
  }
  if (buf == nullptr) {
    result.second = true;
    this->insertTree(key, obj);
    buf = this->find1(key);
  } else {
    result.second = false;
    buf = this->find1(key);
  }
  iterator it(buf);
  result.first = it;
  return result;
}

template <typename Key, typename Value>
std::pair<typename map<Key, Value>::iterator, bool>
map<Key, Value>::insert_or_assign(const Key& key, const Value& obj) {
  std::pair<iterator, bool> result;
  Node<Key, Value>* buf = this->find(key);
  if (buf == nullptr) {
    result = insert(key, obj);
  } else {
    buf->value = obj;
    result.second = true;
    result.first = iterator(buf);
  }
  return result;
}

template <typename Key, typename Value>
void map<Key, Value>::erase(iterator pos) {
  RBtree<Key, Value>::erase(pos);
}

template <typename Key, typename Value>
void map<Key, Value>::swap(map<Key, Value>& other) {
  RBtree<Key, Value>::swap(other);
}

template <typename Key, typename Value>
void map<Key, Value>::merge(map& other) {
  iterator it = other.begin();
  iterator it_end = other.end();
  std::pair<typename s21::map<Key, Value>::iterator, bool> res;
  for (; it.getKey() != it_end.getKey(); ++it) {
    res = this->insert(it.getKey(), it.getValue());
  }
  if (!it.iter_is_nullptr()) {
    res = this->insert(it.getKey(), it.getValue());
  }
}

template <typename Key, typename Value>
template <class... Args>
std::vector<std::pair<typename map<Key, Value>::iterator, bool>>
map<Key, Value>::insert_many(Args&&... args) {
  std::vector<std::pair<typename map<Key, Value>::iterator, bool>> result;
  for (const auto& elem : {args...}) {
    result.push_back(insert(elem));
  }
  return result;
}

// Lookup
template <typename Key, typename Value>
bool map<Key, Value>::contains(const Key& key) {
  bool res = false;
  if (this->find1(key) != nullptr) {
    res = true;
  }
  return res;
}

// Доп функции

template <typename Key, typename Value>
Node<Key, Value>* map<Key, Value>::find(const Key key) {
  return this->find1(key);
}

template <typename Key, typename Value>
typename map<Key, Value>::value_type map<Key, Value>::MapIterator::operator*() {
  if (RBtree<Key, Value>::Iterator::iter_ptr == nullptr) {
    throw std::invalid_argument("iter_ptr == null_ptr");
  }
  std::pair<const key_type, mapped_type> pr =
      std::make_pair(RBtree<Key, Value>::Iterator::iter_ptr->key,
                     RBtree<Key, Value>::Iterator::iter_ptr->value);
  std::pair<const key_type, mapped_type>& ref = pr;
  return ref;
}

}  // namespace s21

#endif