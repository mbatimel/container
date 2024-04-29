#ifndef S21_READ_BLACK_TREE_H
#define S21_READ_BLACK_TREE_H

#include <iostream>
#include <stdexcept>

enum RBTColor { Black, Red };

template <typename Key, typename Value>
struct Node {
  Key key;
  Value value;
  Node<Key, Value>* parent;
  Node<Key, Value>* left;
  Node<Key, Value>* right;
  RBTColor color;
};

template <typename Key, typename Value>
class RBtree {
 public:
  class Iterator;
  using size_type = size_t;
  // конструкторы
  RBtree();
  RBtree(Node<Key, Value>* root);
  RBtree(const RBtree& other);
  RBtree(RBtree&& other);
  ~RBtree();

  // функции отчистки и удаления
  void FreeNode(Node<Key, Value>* node);
  void clear();
  void erase(Iterator pos);

  // поиск минимальног/максимального элемента
  Node<Key, Value>* MinNode();
  Node<Key, Value>* MaxNode();
  static Node<Key, Value>* MinNode(Node<Key, Value>* nodeptr);
  static Node<Key, Value>* MaxNode(Node<Key, Value>* nodeptr);

  // вспомогательные функции
  void insertTree(const Key& key, const Value& value);
  void swap(RBtree& other);
  Node<Key, Value>* Copytree(Node<Key, Value>* ptr,
                             Node<Key, Value>* parent_ptr);
  Node<Key, Value>* find1(const Key key);
  Node<Key, Value>* find2(const Key key);
  Value operator[](const Key key);

  // Балансировка доделать
  void fixed(Node<Key, Value>* nodeptr);
  void right_rotate(Node<Key, Value>* x);
  void left_rotate(Node<Key, Value>* x);

  // итератор
  class Iterator {
   protected:
    Node<Key, Value>* iter_ptr;
    Node<Key, Value>* Max_Node_it;
    Node<Key, Value>* Min_Node_it;

   public:
    Iterator();
    Iterator(Node<Key, Value>* iter_ptr);
    Iterator& operator++();
    Iterator& operator--();
    Iterator operator++(int);
    Iterator operator--(int);
    bool operator!=(Iterator other) const;
    bool operator==(Iterator other) const;
    Iterator& operator()(Node<Key, Value>* ptr);

    Node<Key, Value>* go_next(Node<Key, Value>* ptr);
    Node<Key, Value>* go_previous(Node<Key, Value>* ptr);
    bool iter_is_nullptr();

    Key getKey();
    Value& getValue();
    friend class RBtree<Key, Value>;
    Value& operator*() { return getValue(); }
  };
  Iterator begin();
  Iterator end();
  Iterator lower_bound(const Key& key) noexcept;
  Iterator upper_bound(const Key& key) noexcept;
  size_type size();
  size_t RecursiveSize(Node<Key, Value>* node);
  bool empty();

 protected:
  Node<Key, Value>* root;
};

template <typename Key, typename Value>
bool RBtree<Key, Value>::Iterator::operator==(Iterator other) const {
  return other.iter_ptr == this->iter_ptr;
}

// конструкторы

template <typename Key, typename Value>
RBtree<Key, Value>::RBtree() : root(nullptr) {}

template <typename Key, typename Value>
RBtree<Key, Value>::RBtree(Node<Key, Value>* root) : root(root) {}

template <typename Key, typename Value>
RBtree<Key, Value>::RBtree(const RBtree& other) {
  this->root = Copytree(other.root, nullptr);
}

template <typename Key, typename Value>
RBtree<Key, Value>::RBtree(RBtree&& other) : root(other.root) {
  other.root = nullptr;
}

template <typename Key, typename Value>
RBtree<Key, Value>::~RBtree() {
  clear();
}
template <typename Key, typename Value>
typename RBtree<Key, Value>::Iterator RBtree<Key, Value>::lower_bound(
    const Key& key) noexcept {
  Node<Key, Value>* search = root;
  Node<Key, Value>* result = nullptr;

  while (search != nullptr) {
    if (search->value >= key) {
      result = search;
      search = search->left;
    } else {
      search = search->right;
    }
  }
  return (result == nullptr ? end() : Iterator(result));
}
template <typename Key, typename Value>
typename RBtree<Key, Value>::Iterator RBtree<Key, Value>::upper_bound(
    const Key& key) noexcept {
  Node<Key, Value>* search = root;
  Node<Key, Value>* result = nullptr;

  while (search != nullptr) {
    if (search->value > key) {
      result = search;
      search = search->left;
    } else {
      search = search->right;
    }
  }
  return (result == nullptr ? end() : Iterator(result));
}
template <typename Key, typename Value>
size_t RBtree<Key, Value>::size() {
  return RecursiveSize(root);
}
template <typename Key, typename Value>
size_t RBtree<Key, Value>::RecursiveSize(Node<Key, Value>* node) {
  if (node == nullptr) return 0;
  size_t left_size = RecursiveSize(node->left);
  size_t right_size = RecursiveSize(node->right);
  return 1 + left_size + right_size;
}
template <typename Key, typename Value>
bool RBtree<Key, Value>::empty() {
  return root == nullptr;
}

// функции отчистки и удаления

template <typename Key, typename Value>
void RBtree<Key, Value>::FreeNode(Node<Key, Value>* node) {
  if (node != nullptr) {
    FreeNode(node->left);
    FreeNode(node->right);
    delete node;
  }
}

template <typename Key, typename Value>
void RBtree<Key, Value>::clear() {
  if (this->root != nullptr) {
    FreeNode(root);
    this->root = nullptr;
  }
}

template <typename Key, typename Value>
bool RBtree<Key, Value>::Iterator::operator!=(Iterator other) const {
  return other.iter_ptr != this->iter_ptr;
}

template <typename Key, typename Value>
void RBtree<Key, Value>::erase(RBtree<Key, Value>::Iterator pos) {
  Node<Key, Value>* son;
  // нет предков
  if (pos.iter_ptr->right == nullptr && pos.iter_ptr->left == nullptr) {
    if (root != pos.iter_ptr) {
      if (pos.iter_ptr->parent->left == pos.iter_ptr) {
        pos.iter_ptr->parent->left = nullptr;
      } else {
        pos.iter_ptr->parent->right = nullptr;
      }
    } else {
      root = nullptr;
    }
  }  // есть только один предок
  else if (pos.iter_ptr->right == nullptr || pos.iter_ptr->left == nullptr) {
    if (pos.iter_ptr->right != nullptr) {
      son = pos.iter_ptr->right;
    } else {
      son = pos.iter_ptr->left;
    }
    if (pos.iter_ptr->parent != nullptr) {
      if (pos.iter_ptr->parent->right == pos.iter_ptr) {
        pos.iter_ptr->parent->right = son;
      } else {
        pos.iter_ptr->parent->left = son;
      }
      son->parent = pos.iter_ptr->parent;
    } else {
      root = son;
    }
  }  // есть два предка
  else {
    son = pos.iter_ptr->left;
    // разборка с родителями
    if (pos.iter_ptr->parent != nullptr) {
      if (pos.iter_ptr->parent->right == pos.iter_ptr) {
        pos.iter_ptr->parent->right = son;
      } else {
        pos.iter_ptr->parent->left = son;
      }
      son->parent = pos.iter_ptr->parent;
    } else {
      root = son;
      son->parent = nullptr;
    }
    // ищем сынку куда пристроиться
    if (son->right != nullptr) {
      Node<Key, Value>* buf = MinNode(pos.iter_ptr->right);
      buf->left = son->right;
      son->right = pos.iter_ptr->right;
      son->right->parent = son;
      buf->left->parent = buf;
    } else {
      son->right = pos.iter_ptr->right;
    }
  }
  delete pos.iter_ptr;
}

// поиск минимальног/максимального элемента

template <typename Key, typename Value>
Node<Key, Value>* RBtree<Key, Value>::MinNode(Node<Key, Value>* nodeptr) {
  Node<Key, Value>* buf = nodeptr;
  while (nodeptr != nullptr) {
    buf = nodeptr;
    nodeptr = buf->left;
  }
  return buf;
}

template <typename Key, typename Value>
Node<Key, Value>* RBtree<Key, Value>::MaxNode(Node<Key, Value>* nodeptr) {
  Node<Key, Value>* buf = nodeptr;
  while (nodeptr != nullptr) {
    buf = nodeptr;
    nodeptr = buf->right;
  }
  return buf;
}

template <typename Key, typename Value>
Node<Key, Value>* RBtree<Key, Value>::MinNode() {
  return MinNode(this->root);
}

template <typename Key, typename Value>
Node<Key, Value>* RBtree<Key, Value>::MaxNode() {
  return MaxNode(this->root);
}

// вспомогательные функции

template <typename Key, typename Value>
void RBtree<Key, Value>::insertTree(const Key& key, const Value& value) {
  Node<Key, Value>* new_elem = new Node<Key, Value>;
  new_elem->key = key;
  new_elem->value = value;
  new_elem->left = nullptr;
  new_elem->right = nullptr;
  new_elem->parent = nullptr;
  new_elem->color = Red;
  Node<Key, Value>* buf = this->root;
  Node<Key, Value>* buf1 = NULL;
  if (buf == nullptr) {
    this->root = new_elem;
  } else {
    while (buf != nullptr) {
      buf1 = buf;
      if (buf->key > new_elem->key) {
        buf = buf->left;
      } else {
        buf = buf->right;
      }
    }
    new_elem->parent = buf1;
    if (buf1->key > new_elem->key) {
      buf1->left = new_elem;
    } else {
      buf1->right = new_elem;
    }
  }
  if (new_elem != root) {
    fixed(new_elem);
  }
}

template <typename Key, typename Value>
void RBtree<Key, Value>::swap(RBtree<Key, Value>& other) {
  std::swap(other.root, this->root);
}

template <typename Key, typename Value>
Node<Key, Value>* RBtree<Key, Value>::Copytree(Node<Key, Value>* ptr,
                                               Node<Key, Value>* parent_ptr) {
  Node<Key, Value>* new_node = nullptr;
  if (ptr != nullptr) {
    new_node = new Node<Key, Value>;
    new_node->color = ptr->color;
    new_node->key = ptr->key;
    new_node->value = ptr->value;
    new_node->parent = parent_ptr;
    new_node->left = Copytree(ptr->left, new_node);
    new_node->right = Copytree(ptr->right, new_node);
  }
  return new_node;
}

template <typename Key, typename Value>
Node<Key, Value>* RBtree<Key, Value>::find1(const Key key) {
  Node<Key, Value>* buf = this->root;
  while (buf != nullptr && buf->key != key) {
    if (buf->key > key) {
      buf = buf->left;
    } else {
      buf = buf->right;
    }
  }
  if (buf != nullptr && key != buf->key) {
    buf = nullptr;
  }
  return buf;
}

template <typename Key, typename Value>
Node<Key, Value>* RBtree<Key, Value>::find2(const Key key) {
  Node<Key, Value>* buf = this->root;
  Node<Key, Value>* res = buf;
  while (buf != nullptr) {
    if (buf->key == key) {
      res = buf;
    }
    if (buf->key > key) {
      buf = buf->left;
    } else {
      buf = buf->right;
    }
  }
  if (res != nullptr && key != res->key) {
    res = nullptr;
  }
  return res;
}

template <typename Key, typename Value>
Value RBtree<Key, Value>::operator[](const Key key) {
  return find1(key)->value;
}

template <typename Key, typename Value>
void RBtree<Key, Value>::fixed(Node<Key, Value>* nodeptr) {
  Node<Key, Value>* father = nodeptr->parent;
  if (father == nullptr) {
    return;
  }
  if (father->parent != nullptr) {
    Node<Key, Value>* uncle = (father->parent->right != father)
                                  ? father->parent->right
                                  : father->parent->left;
    if (uncle != nullptr && father->parent != this->root &&
        father->color == Red && uncle->color == Red) {
      father->parent->color = Red;
      father->color = Black;
      uncle->color = Black;
      fixed(father->parent);
    } else if (uncle != nullptr && father->color == Red &&
               uncle->color == Black && father->parent->left->left == nodeptr) {
      father->parent->color = Red;
      father->color = Black;
      right_rotate(father->parent);
      fixed(father->right->right);
    } else if (uncle != nullptr && father->color == Red &&
               uncle->color == Black &&
               father->parent->left->right == nodeptr) {
      nodeptr->color = Black;
      father->parent->color = Red;
      left_rotate(father);
      right_rotate(nodeptr->parent);
      fixed(nodeptr->right->right);
    } else if (uncle != nullptr && father->color == Red &&
               uncle->color == Black &&
               father->parent->right->right == nodeptr) {
      father->parent->color = Red;
      father->color = Black;
      left_rotate(father->parent);
      fixed(father->left);
    } else if (uncle != nullptr && father->color == Red &&
               uncle->color == Black &&
               father->parent->right->left == nodeptr) {
      father->parent->color = Red;
      nodeptr->color = Black;
      right_rotate(father);
      left_rotate(nodeptr->parent);
      fixed(nodeptr->left->left);
    }
  }
}

template <typename Key, typename Value>
void RBtree<Key, Value>::right_rotate(Node<Key, Value>* x) {
  Node<Key, Value>* y = x->left;
  x->left = y->right;
  if (y->right != nullptr) {
    y->right->parent = x;
  }
  y->parent = x->parent;
  if (x->parent == nullptr) {
    this->root = y;
  } else if (x == x->parent->right) {
    x->parent->right = y;
  } else {
    x->parent->left = y;
  }
  y->right = x;
  x->parent = y;
}

template <typename Key, typename Value>
void RBtree<Key, Value>::left_rotate(Node<Key, Value>* x) {
  Node<Key, Value>* y = x->right;
  x->right = y->left;
  if (y->left != nullptr) {
    y->left->parent = x;
  }
  y->parent = x->parent;
  if (x->parent == nullptr) {
    this->root = y;
  } else if (x->parent->right == x) {
    x->parent->right = y;
  } else {
    x->parent->left = y;
  }
  y->left = x;
  x->parent = y;
}

// begin и end
template <typename Key, typename Value>
typename RBtree<Key, Value>::Iterator RBtree<Key, Value>::begin() {
  return RBtree<Key, Value>::Iterator(MinNode());
}

template <typename Key, typename Value>
typename RBtree<Key, Value>::Iterator RBtree<Key, Value>::end() {
  return RBtree<Key, Value>::Iterator(MaxNode());
}

// Итератор
template <typename Key, typename Value>
RBtree<Key, Value>::Iterator::Iterator()
    : iter_ptr(nullptr), Max_Node_it(nullptr), Min_Node_it(nullptr) {}

template <typename Key, typename Value>
RBtree<Key, Value>::Iterator::Iterator(Node<Key, Value>* iter_ptr)
    : iter_ptr(iter_ptr), Max_Node_it(nullptr), Min_Node_it(nullptr) {
  Node<Key, Value>* buf = iter_ptr;
  if (buf != nullptr) {
    while (buf->parent != nullptr) {
      buf = buf->parent;
    }
    Max_Node_it = MaxNode(buf);
    Min_Node_it = MinNode(buf);
  }
}

template <typename Key, typename Value>
Key RBtree<Key, Value>::Iterator::getKey() {
  return this->iter_ptr->key;
}

template <typename Key, typename Value>
Value& RBtree<Key, Value>::Iterator::getValue() {
  return this->iter_ptr->value;
}

template <typename Key, typename Value>
Node<Key, Value>* RBtree<Key, Value>::Iterator::go_next(Node<Key, Value>* ptr) {
  Node<Key, Value>* res = nullptr;
  if (ptr == Max_Node_it) {
    res = Min_Node_it;
  } else if (ptr->right != nullptr) {
    res = RBtree<Key, Value>::MinNode(ptr->right);
  } else {
    Node<Key, Value>* buf_parent = ptr->parent;
    while (buf_parent != nullptr && buf_parent->right == ptr) {
      ptr = buf_parent;
      buf_parent = ptr->parent;
    }
    res = (buf_parent != nullptr) ? buf_parent : ptr;
  }
  return res;
}

template <typename Key, typename Value>
Node<Key, Value>* RBtree<Key, Value>::Iterator::go_previous(
    Node<Key, Value>* ptr) {
  Node<Key, Value>* res = nullptr;
  if (ptr == Min_Node_it) {
    res = Max_Node_it;
  } else if (ptr->left != nullptr) {
    res = RBtree<Key, Value>::MaxNode(ptr->left);
  } else {
    Node<Key, Value>* buf_parent = ptr->parent;
    while (buf_parent != nullptr && buf_parent->left == ptr) {
      ptr = buf_parent;
      buf_parent = ptr->parent;
    }
    res = (buf_parent != nullptr) ? buf_parent : ptr;
  }
  return res;
}

template <typename Key, typename Value>
typename RBtree<Key, Value>::Iterator&
RBtree<Key, Value>::Iterator::operator++() {
  this->iter_ptr = this->go_next(iter_ptr);
  return *this;
}

template <typename Key, typename Value>
typename RBtree<Key, Value>::Iterator& RBtree<Key, Value>::Iterator::operator()(
    Node<Key, Value>* ptr) {
  this->iter_ptr = ptr;
  return *this;
}

template <typename Key, typename Value>
typename RBtree<Key, Value>::Iterator&
RBtree<Key, Value>::Iterator::operator--() {
  this->iter_ptr = this->go_previous(iter_ptr);
  return *this;
}

template <typename Key, typename Value>
typename RBtree<Key, Value>::Iterator RBtree<Key, Value>::Iterator::operator++(
    int) {
  Iterator buf(this->iter_ptr);
  this->iter_ptr = this->go_next(iter_ptr);
  return buf;
}

template <typename Key, typename Value>
typename RBtree<Key, Value>::Iterator RBtree<Key, Value>::Iterator::operator--(
    int) {
  Iterator buf(this->iter_ptr);
  this->iter_ptr = this->go_previous(iter_ptr);
  return buf;
}

template <typename Key, typename Value>
bool RBtree<Key, Value>::Iterator::iter_is_nullptr() {
  bool res = false;
  if (this->iter_ptr == nullptr) {
    res = true;
  }
  return res;
}

#endif