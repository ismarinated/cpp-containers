#ifndef S21_SET_H
#define S21_SET_H

#include <initializer_list>
#include <utility>

#include "../RBtree/s21_rbtree.h"

namespace s21 {

template <typename Key>
class set {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;

  class Iterator {
   public:
    Iterator(typename RBTree<Key>::Node* node, const RBTree<Key>* tree)
        : node_(node), tree_(tree) {}

    reference operator*() const { return node_->data; }

    Iterator& operator++() {
      if (node_) {
        node_ = tree_->successor(node_);
      }
      return *this;
    }

    bool operator==(const Iterator& other) const {
      return node_ == other.node_;
    }

    bool operator!=(const Iterator& other) const {
      return node_ != other.node_;
    }

   private:
    typename RBTree<Key>::Node* node_;
    const RBTree<Key>* tree_;
  };

  class ConstIterator {
   public:
    ConstIterator(typename RBTree<Key>::Node* node, const RBTree<Key>* tree)
        : node_(node), tree_(tree) {}

    const_reference operator*() const { return node_->data; }

    ConstIterator& operator++() {
      if (node_) {
        node_ = tree_->successor(node_);
      }
      return *this;
    }

    bool operator==(const ConstIterator& other) const {
      return node_ == other.node_;
    }

    bool operator!=(const ConstIterator& other) const {
      return node_ != other.node_;
    }

   private:
    typename RBTree<Key>::Node* node_;
    const RBTree<Key>* tree_;
  };

  using iterator = Iterator;
  using const_iterator = ConstIterator;

  set() = default;

  set(std::initializer_list<value_type> const& items) {
    for (const auto& item : items) {
      insert(item);
    }
  }

  set(const set& other) {
    for (const auto& item : other) {
      insert(item);
    }
  }

  set(set&& other) : tree_(std::move(other.tree_)) { other.tree_ = SetTree(); }

  ~set() = default;

  set& operator=(set&& other) {
    if (this != &other) {
      tree_ = std::move(other.tree_);
      other.tree_ = SetTree();
    }
    return *this;
  }

  set& operator=(const set& other) {
    if (this != &other) {
      clear();
      for (const auto& item : other) {
        insert(item);
      }
    }
    return *this;
  }

  bool empty() const { return tree_.size() == 0; }

  size_type size() const { return tree_.size(); }

  size_type max_size() const {
    return std::numeric_limits<size_type>::max() / sizeof(value_type);
  }

  void clear() { tree_.clear(); }

  std::pair<iterator, bool> insert(const value_type& value) {
    bool inserted = !tree_.contains(value);
    if (inserted) {
      tree_.insert(value);
    }
    return std::make_pair(iterator(tree_.find(value), &tree_), inserted);
  }

  iterator find(const Key& key) { return iterator(tree_.find(key), &tree_); }

  void erase(iterator pos) {
    if (pos != end()) {
      tree_.erase(*pos);
    }
  }

  bool contains(const Key& key) const { return tree_.find(key) != nullptr; }

  iterator begin() {
    return iterator(tree_.minimum((tree_.getRoot())), &tree_);
  }
  iterator end() { return iterator(nullptr, &tree_); }

  void merge(set& other) {
    auto it = other.begin();
    while (it != other.end()) {
      auto next = it;
      ++next;
      if (!contains(*it)) {
        insert(*it);
        other.erase(it);
      }
      it = next;
    }
  }

  void swap(set& other) { std::swap(tree_, other.tree_); }

  const_iterator begin() const {
    return const_iterator(tree_.minimum(tree_.getRoot()), &tree_);
  }

  const_iterator end() const { return const_iterator(nullptr, &tree_); }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    std::vector<std::pair<iterator, bool>> result;
    (result.push_back(insert(std::forward<Args>(args))), ...);
    return result;
  }

 private:
  using SetTree = RBTree<Key, false>;  // Используем RBTree без дубликатов
  SetTree tree_;
};

}  // namespace s21

#endif  // S21_SET_H