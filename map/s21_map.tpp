#include "s21_map.h"

namespace s21 {

template <typename Key, typename Value>
map<Key, Value>::map(std::initializer_list<value_type> const &items) {
  for (auto i = items.begin(); i != items.end(); ++i) {
    BinaryAVLTree<Key, Value>::insert(*i);
  }
}

template <typename Key, typename Value>
map<Key, Value> &map<Key, Value>::operator=(const map &other) {
  BinaryAVLTree<Key, Value>::operator=(other);
  return *this;
}

template <typename Key, typename Value>
map<Key, Value> &map<Key, Value>::operator=(map &&other) {
  BinaryAVLTree<Key, Value>::operator=(std::move(other));
  return *this;
}
}  // namespace s21
