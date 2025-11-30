#ifndef S21_MULTISET_H
#define S21_MULTISET_H

#include <initializer_list>
#include <utility>

#include "../RBtree/s21_rbtree.h"

namespace s21 {

template <typename Key>
class multiset {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;

  class Iterator {
   public:
    Iterator(typename RBTree<Key, true>::Node* node,
             const RBTree<Key, true>* tree)
        : node_(node), tree_(tree) {}

    reference operator*() const {
      if (!node_) {
        throw std::out_of_range("Dereferencing end iterator");
      }
      return node_->data;
    }

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
    typename RBTree<Key, true>::Node* node_;
    const RBTree<Key, true>* tree_;
  };

  class ConstIterator {
   public:
    ConstIterator(const typename RBTree<Key, true>::Node* node,
                  const RBTree<Key, true>* tree)
        : node_(node), tree_(tree) {}

    const_reference operator*() const {
      if (!node_) {
        throw std::out_of_range("Dereferencing end iterator");
      }
      return node_->data;
    }

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
    const typename RBTree<Key, true>::Node* node_;
    const RBTree<Key, true>* tree_;
  };

  using iterator = Iterator;
  using const_iterator = ConstIterator;

  multiset() = default;

  multiset(std::initializer_list<value_type> const& items) {
    for (const auto& item : items) {
      insert(item);
    }
  }

  multiset(const multiset& other) {
    for (const auto& item : other) {
      insert(item);
    }
  }

  multiset(multiset&& other) : tree_(std::move(other.tree_)) {
    other.tree_ = RBTree<Key, true>();
  }

  ~multiset() = default;

  multiset& operator=(multiset&& other) {
    if (this != &other) {
      tree_ = std::move(other.tree_);
      other.tree_ = RBTree<Key, true>();
    }
    return *this;
  }

  multiset& operator=(const multiset& other) {
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

  size_type max_size() const { return tree_.max_size(); }

  void clear() { tree_.clear(); }

  iterator insert(const value_type& value) {
    tree_.insert(value);
    return iterator(tree_.find(value), &tree_);
  }

  iterator find(const Key& key) {
    auto node = tree_.find(key);
    return iterator(node, &tree_);
  }

  void erase(iterator pos) {
    if (pos != end()) {
      tree_.erase(*pos);
    }
  }

  bool contains(const Key& key) const { return tree_.find(key) != nullptr; }

  size_type count(const Key& key) const { return tree_.count(key); }
  std::pair<iterator, iterator> equal_range(const Key& key) {
    auto lower = lower_bound(key);
    auto upper = upper_bound(key);
    return std::make_pair(lower, upper);
  }

  iterator lower_bound(const Key& key) {
    auto it = begin();
    while (it != end() && *it < key) {
      ++it;
    }
    return it;
  }

  iterator upper_bound(const Key& key) {
    auto it = begin();
    while (it != end() && *it <= key) {
      ++it;
    }
    return it;
  }

  void merge(multiset& other) {
    for (auto it = other.begin(); it != other.end();) {
      auto next = it;
      ++next;
      insert(*it);
      other.erase(it);
      it = next;
    }
  }

  void swap(multiset& other) { std::swap(tree_, other.tree_); }

  iterator begin() { return iterator(tree_.minimum(tree_.getRoot()), &tree_); }
  const_iterator begin() const {
    return const_iterator(tree_.minimum(tree_.getRoot()), &tree_);
  }

  iterator end() { return iterator(nullptr, &tree_); }
  const_iterator end() const { return const_iterator(nullptr, &tree_); }

  template <typename... Args>
  std::vector<iterator> insert_many(Args&&... args) {
    std::vector<iterator> results;
    (results.push_back(insert(std::forward<Args>(args))), ...);
    return results;
  }

 private:
  using MultiSetTree = RBTree<Key, true>;  // Используем RBTree с дубликатами
  MultiSetTree tree_;
};

}  // namespace s21

#endif  // S21_MULTISET_H