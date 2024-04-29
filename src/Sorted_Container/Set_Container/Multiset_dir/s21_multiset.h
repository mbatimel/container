#ifndef S21_CONTAINER_MULTISET_H
#define S21_CONTAINER_MULTISET_H
#include <iostream>
#include <limits>
#include <stdexcept>
#include <vector>

namespace s21 {

template <typename Key>
class multiset : public RBtree<Key, Key> {
 public:
  class ConstMultisetIterator;
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename RBtree<Key, Key>::Iterator;
  using const_iterator = ConstMultisetIterator;
  using size_type = std::size_t;
  multiset();
  multiset(std::initializer_list<value_type> const& items);
  multiset(const multiset& ms);
  multiset(multiset&& ms);
  ~multiset();
  multiset& operator=(multiset&& ms);
  iterator begin();
  iterator end();
  bool empty();
  size_type size();
  size_type max_size();
  size_type count(const Key& key);
  void clear();
  iterator insert(const value_type& value);
  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args);
  void swap(multiset& other);
  void merge(multiset& other);
  bool contains(const Key& key);
  iterator find(const Key& key);
  void erase(iterator pos);
  std::pair<iterator, iterator> equal_range(const Key& key);
  class ConstMultisetIterator : public RBtree<Key, Key>::Iterator {
   public:
    friend class multiset;
    ConstMultisetIterator() : RBtree<Key, Key>::Iterator(){};
    ConstMultisetIterator(Node<Key, Key>* iter_ptr)
        : RBtree<Key, Key>::Iterator(iter_ptr){};
  };
};

template <typename Key>
multiset<Key>::multiset() : RBtree<Key, Key>() {}

template <typename Key>
multiset<Key>::multiset(std::initializer_list<value_type> const& items) {
  for (auto& element : items) {
    this->insert(element);
  }
}

template <typename Key>
multiset<Key>::multiset(const multiset& ms) : RBtree<Key, Key>(ms) {}

template <typename Key>
multiset<Key>::multiset(multiset&& ms) : RBtree<Key, Key>(std::move(ms)) {}

template <typename Key>
multiset<Key>::~multiset() {}

template <typename Key>
multiset<Key>& multiset<Key>::operator=(multiset&& ms) {
  if (&ms != this) {
    swap(ms);
  }
  ms.clear();
  return *this;
}

template <typename Key>
void multiset<Key>::erase(iterator pos) {
  RBtree<Key, Key>::erase(pos);
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::begin() {
  return iterator(this->MinNode());
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::end() {
  return iterator(this->MaxNode());
}

template <typename Key>
bool multiset<Key>::empty() {
  bool res = false;
  if (this->root == nullptr) {
    res = true;
  }
  return res;
}

template <typename Key>
typename multiset<Key>::size_type multiset<Key>::size() {
  size_type res = 1;
  iterator start = this->begin();
  iterator stop = this->end();
  if (!start.iter_is_nullptr()) {
    while (start != stop) {
      ++start;
      res++;
    }
  } else {
    res = 0;
  }

  return res;
}

template <typename Key>
typename multiset<Key>::size_type multiset<Key>::max_size() {
  std::allocator<std::pair<key_type, value_type>> Alloc;
  return std::allocator_traits<decltype(Alloc)>::max_size(Alloc) / 5;
}

template <typename Key>
void multiset<Key>::clear() {
  RBtree<Key, Key>::clear();
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::insert(
    const value_type& value) {
  Node<Key, Key>* buf = nullptr;
  this->insertTree(value, value);
  buf = this->find2(value);
  iterator it(buf);
  return it;
}

template <typename Key>
void multiset<Key>::swap(multiset<Key>& other) {
  RBtree<Key, Key>::swap(other);
}

template <typename Key>
void multiset<Key>::merge(multiset<Key>& other) {
  iterator it = other.begin();
  iterator it_end = other.end();
  typename s21::multiset<Key>::iterator res;
  for (; it != it_end; ++it) {
    res = this->insert(it.getKey());
  }
  if (!it.iter_is_nullptr()) {
    res = this->insert(it.getKey());
  }
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::find(const Key& key) {
  Node<Key, Key>* buf = this->find1(key);
  iterator it(buf);
  return it;
}

template <typename Key>
bool multiset<Key>::contains(const Key& key) {
  Node<Key, Key>* res = nullptr;
  res = this->find1(key);
  bool otv = false;
  if (res != nullptr) {
    otv = true;
  }
  return otv;
}

template <typename Key>
template <class... Args>
std::vector<std::pair<typename multiset<Key>::iterator, bool>>
multiset<Key>::insert_many(Args&&... args) {
  std::vector<std::pair<typename multiset<Key>::iterator, bool>> result;
  for (const auto& elem : {args...}) {
    result.push_back(std::make_pair(insert(elem), true));
  }
  return result;
}

template <typename Key>
std::pair<typename multiset<Key>::iterator, typename multiset<Key>::iterator>
multiset<Key>::equal_range(const typename multiset<Key>::key_type& key) {
  return std::make_pair(RBtree<Key, Key>::lower_bound(key),
                        RBtree<Key, Key>::upper_bound(key));
}

template <typename Key>
typename multiset<Key>::size_type multiset<Key>::count(const Key& key) {
  size_t res = 0;
  auto lb = this->lower_bound(key);
  auto ub = this->upper_bound(key);
  for (auto iter = lb; iter != ub; ++iter) {
    res++;
  }
  return res;
}

}  // namespace s21
#endif  // end of S21_CONTAINER_MULTISET_H
