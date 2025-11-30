#ifndef S21_MAP_H
#define S21_MAP_H

#include "../BinaryAVLTree/BinaryAVLTree.h"

namespace s21 {

template <typename Key, typename Value>
class map : public BinaryAVLTree<Key, Value> {
 public:
  class MapIterator;
  class ConstMapIterator;

  using key_type = Key;
  using mapped_type = Value;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = MapIterator;
  using const_iterator = ConstMapIterator;
  using size_type = size_t;

  map() : BinaryAVLTree<Key, Value>() {};
  map(const map &other) : BinaryAVLTree<Key, Value>(other) {};
  map(map &&other) noexcept : BinaryAVLTree<Key, Value>(std::move(other)) {};
  map(std::initializer_list<value_type> const &items);
  ~map() = default;

  map &operator=(const map &other);
  map &operator=(map &&other);
};

}  // namespace s21

#include "s21_map.tpp"

#endif