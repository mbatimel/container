

#ifndef CPP2_S21_CONTAINERS_S21_CONTAINERS_SET_SET_H_
#define CPP2_S21_CONTAINERS_S21_CONTAINERS_SET_SET_H_

#include <vector>

namespace s21 {

template <typename Key>
class set : public RBtree<Key, Key> {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const Key&;
  using iterator = typename RBtree<Key, Key>::Iterator;
  using size_type = size_t;

  set() : RBtree<Key, Key>(){};
  set(std::initializer_list<value_type> const& items);
  set(const set& other) : RBtree<Key, Key>(other){};
  set(set&& other) noexcept;
  set& operator=(set&& other);
  set& operator=(const set& other);
  ~set() = default;
  std::pair<iterator, bool> insert(const value_type& value);
  bool contains(const Key& key);
  void merge(set<Key>& other);
  void swap(set& other);
  void erase(iterator pos);
  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args);

  iterator find(const Key& key) { return RBtree<Key, Key>::find1(key); };
};

template <typename Key>
void set<Key>::erase(iterator pos) {
  RBtree<Key, Key>::erase(pos);
}

template <typename Key>
set<Key>::set(set<Key>&& other) noexcept : RBtree<Key, Key>(std::move(other)) {}

template <typename Key>
std::pair<typename set<Key>::iterator, bool> set<Key>::insert(const Key& key) {
  std::pair<iterator, bool> result;
  Node<Key, Key>* buf = nullptr;
  if (this->root != nullptr) {
    buf = this->find1(key);
  }
  if (buf == nullptr) {
    result.second = true;
    this->insertTree(key, key);
    buf = this->find1(key);
  } else {
    result.second = false;
    buf = this->find1(key);
  }
  iterator it(buf);
  result.first = it;
  return result;
}

template <typename Key>
void set<Key>::merge(set<Key>& other) {
  iterator it = other.begin();
  iterator it_end = other.end();
  typename s21::set<Key>::iterator res;
  for (; it != it_end; ++it) {
    res = (this->insert(it.getKey())).first;
  }
  if (!it.iter_is_nullptr()) {
    res = (this->insert(it.getKey())).first;
  }
}

template <typename Key>
template <class... Args>
std::vector<std::pair<typename set<Key>::iterator, bool>> set<Key>::insert_many(
    Args&&... args) {
  std::vector<std::pair<typename set<Key>::iterator, bool>> result;
  for (const auto& elem : {args...}) {
    result.push_back(insert(elem));
  }
  return result;
}

template <typename Key>
bool set<Key>::contains(const Key& key) {
  Node<Key, Key>* res = nullptr;
  res = this->find1(key);
  bool otv = false;
  if (res != nullptr) {
    otv = true;
  }
  return otv;
}

template <typename Key>
set<Key>::set(const std::initializer_list<value_type>& items) {
  for (auto& element : items) {
    this->insert(element);
  }
}

template <typename Key>
set<Key>& set<Key>::operator=(const set& other) {
  if (&other != this) {
    set<Key> buf(other);
    swap(buf);
  }
  return *this;
}

template <typename Key>
set<Key>& set<Key>::operator=(set&& other) {
  if (&other != this) {
    swap(other);
    other.clear();
  }
  return *this;
}

template <typename Key>
void set<Key>::swap(set& other) {
  RBtree<Key, Key>::swap(other);
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_CONTAINERS_SET_SET_H_