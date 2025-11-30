#ifndef S21_RBTREE_H
#define S21_RBTREE_H

#include <cstddef>
#include <iostream>
#include <limits>

namespace s21 {

enum class Color { RED, BLACK };

template <typename Key, bool AllowDuplicates = false>
class RBTree {
 public:
  struct Node {
    Key data;
    Color color;
    Node* parent;
    Node* left;
    Node* right;

    Node(Key value)
        : data(value),
          color(Color::RED),
          parent(nullptr),
          left(nullptr),
          right(nullptr) {}
  };

  RBTree() : root_(nullptr), size_(0) {}

  RBTree(RBTree&& other) : root_(other.root_), size_(other.size_) {
    other.root_ = nullptr;
    other.size_ = 0;
  }

  RBTree& operator=(RBTree&& other) {
    if (this != &other) {
      clear();
      root_ = other.root_;
      size_ = other.size_;
      other.root_ = nullptr;
      other.size_ = 0;
    }
    return *this;
  }

  bool empty() const { return root_ == nullptr; }

  ~RBTree() { clear(); }

  Node* getRoot() const { return root_; }

  void insert(const Key& value) {
    if constexpr (!AllowDuplicates) {
      if (contains(value)) return;  // Запрещаем дубликаты для set
    }
    Node* new_node = new Node(value);
    if (!root_) {
      root_ = new_node;
    } else {
      insertRec(root_, new_node);
    }
    fixInsert(new_node);
    size_++;
  }

  Node* find(const Key& value) { return findRec(root_, value); }

  const Node* find(const Key& value) const { return findRec(root_, value); }

  bool contains(const Key& value) const { return find(value) != nullptr; }

  size_t size() const { return size_; }

  size_t max_size() const {
    return std::numeric_limits<size_t>::max() / (sizeof(Node) + sizeof(*this));
  }

  void clear() {
    clear(root_);
    root_ = nullptr;
    size_ = 0;
  }

  void erase(const Key& value) {
    Node* node = find(value);
    if (node) {
      eraseNode(node);
      size_--;
    }
  }

  size_t count(const Key& value) const {
    size_t cnt = 0;
    countRec(root_, value, cnt);
    return cnt;
  }

  void countRec(Node* node, const Key& value, size_t& cnt) const {
    if (!node) return;

    if (value < node->data) {
      countRec(node->left, value, cnt);
    } else if (value > node->data) {
      countRec(node->right, value, cnt);
    } else {
      cnt++;
      countRec(node->left, value, cnt);
      countRec(node->right, value, cnt);
    }
  }
  Node* minimum(Node* node) const {
    if (!node) {
      return nullptr;
    }
    while (node->left) {
      node = node->left;
    }
    return node;
  }

  Node* successor(Node* node) const {
    if (node->right) {
      return minimum(node->right);
    }
    Node* parent = node->parent;
    while (parent && node == parent->right) {
      node = parent;
      parent = parent->parent;
    }
    return parent;
  }

  const Node* successor(const Node* node) const {
    if (node->right) {
      return minimum(node->right);
    }
    const Node* parent = node->parent;
    while (parent && node == parent->right) {
      node = parent;
      parent = parent->parent;
    }
    return parent;
  }

 private:
  Node* root_;
  size_t size_;

  void insertRec(Node* root, Node* new_node) {
    if (new_node->data < root->data) {
      if (root->left) {
        insertRec(root->left, new_node);
      } else {
        root->left = new_node;
        new_node->parent = root;
      }
    } else {
      if (root->right) {
        insertRec(root->right, new_node);
      } else {
        root->right = new_node;
        new_node->parent = root;
      }
    }
  }

  void fixInsert(Node* node) {
    while (node->parent && node->parent->color == Color::RED) {
      if (node->parent == node->parent->parent->left) {
        fixInsertLeftCase(node);
      } else {
        fixInsertRightCase(node);
      }
    }
    // Корень всегда черный
    root_->color = Color::BLACK;
  }

  void fixInsertLeftCase(Node*& node) {
    Node* uncle = node->parent->parent->right;
    if (uncle && uncle->color == Color::RED) {
      handleRedUncle(node, uncle);
    } else {
      handleBlackUncleLeft(node);
    }
  }

  void fixInsertRightCase(Node*& node) {
    Node* uncle = node->parent->parent->left;
    if (uncle && uncle->color == Color::RED) {
      handleRedUncle(node, uncle);
    } else {
      handleBlackUncleRight(node);
    }
  }

  void handleRedUncle(Node*& node, Node* uncle) {
    node->parent->color = Color::BLACK;
    uncle->color = Color::BLACK;
    node->parent->parent->color = Color::RED;
    node = node->parent->parent;
  }

  void handleBlackUncleLeft(Node*& node) {
    if (node == node->parent->right) {
      node = node->parent;
      rotateLeft(node);
    }
    node->parent->color = Color::BLACK;
    node->parent->parent->color = Color::RED;
    rotateRight(node->parent->parent);
  }

  void handleBlackUncleRight(Node*& node) {
    if (node == node->parent->left) {
      node = node->parent;
      rotateRight(node);
    }
    node->parent->color = Color::BLACK;
    node->parent->parent->color = Color::RED;
    rotateLeft(node->parent->parent);
  }

  void rotate(Node* node, bool isLeft) {
    if (!node) return;
    Node* child = isLeft ? node->right : node->left;
    if (!child) return;
    if (isLeft) {
      node->right = child->left;
      if (child->left) {
        child->left->parent = node;
      }
    } else {
      node->left = child->right;
      if (child->right) {
        child->right->parent = node;
      }
    }
    child->parent = node->parent;
    if (!node->parent) {
      root_ = child;
    } else if (node == node->parent->left) {
      node->parent->left = child;
    } else {
      node->parent->right = child;
    }
    if (isLeft) {
      child->left = node;
    } else {
      child->right = node;
    }
    node->parent = child;
  }

  void rotateLeft(Node* node) { rotate(node, true); }

  void rotateRight(Node* node) { rotate(node, false); }

  Node* findRec(Node* node, const Key& value) {
    if (!node || node->data == value) {
      return node;
    }
    if (value < node->data) {
      return findRec(node->left, value);
    }
    return findRec(node->right, value);
  }

  const Node* findRec(const Node* node, const Key& value) const {
    if (!node || node->data == value) {
      return node;
    }
    if (value < node->data) {
      return findRec(node->left, value);
    }
    return findRec(node->right, value);
  }

  void clear(Node* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
  }

  void eraseNode(Node* node) {
    if (!node) {
      return;
    }
    Node* child = nullptr;
    Node* parent = nullptr;
    Color original_color = node->color;

    if (!node->left) {
      // У узла нет левого ребенка
      child = node->right;
      transplant(node, node->right);
    } else if (!node->right) {
      // У узла нет правого ребенка
      child = node->left;
      transplant(node, node->left);
    } else {
      // У узла есть оба ребенка
      Node* successor = minimum(node->right);
      original_color = successor->color;
      child = successor->right;
      parent = successor->parent;

      if (successor->parent != node) {
        transplant(successor, successor->right);
        successor->right = node->right;
        successor->right->parent = successor;
      } else {
        parent = successor;
      }

      transplant(node, successor);
      successor->left = node->left;
      successor->left->parent = successor;
      successor->color = node->color;
    }

    delete node;

    if (original_color == Color::BLACK) {
      fixDelete(child, parent);
    }
  }

  void transplant(Node* u, Node* v) {
    if (!u->parent) {
      root_ = v;
    } else if (u == u->parent->left) {
      u->parent->left = v;
    } else {
      u->parent->right = v;
    }
    if (v) {
      v->parent = u->parent;
    }
  }

  void fixDelete(Node* node, Node* parent) {
    while (node != root_ && (!node || node->color == Color::BLACK)) {
      if (!parent) {
        break;
      }

      if (node == parent->left) {
        Node* sibling = parent->right;
        if (!sibling) {
          break;
        }

        if (sibling->color == Color::RED) {
          // Брат красный
          sibling->color = Color::BLACK;
          parent->color = Color::RED;
          rotateLeft(parent);
          sibling = parent->right;
        }

        if ((!sibling->left || sibling->left->color == Color::BLACK) &&
            (!sibling->right || sibling->right->color == Color::BLACK)) {
          // Оба ребенка брата черные
          sibling->color = Color::RED;
          node = parent;
          parent = node->parent;
        } else {
          if (!sibling->right || sibling->right->color == Color::BLACK) {
            // Левый ребенок брата красный, правый черный
            sibling->left->color = Color::BLACK;
            sibling->color = Color::RED;
            rotateRight(sibling);
            sibling = parent->right;
          }
          //  Правый ребенок брата красный
          sibling->color = parent->color;
          parent->color = Color::BLACK;
          sibling->right->color = Color::BLACK;
          rotateLeft(parent);
          node = root_;
        }
      } else {
        Node* sibling = parent->left;
        if (!sibling) {
          break;
        }

        if (sibling->color == Color::RED) {
          // Брат красный
          sibling->color = Color::BLACK;
          parent->color = Color::RED;
          rotateRight(parent);
          sibling = parent->left;
        }

        if ((!sibling->right || sibling->right->color == Color::BLACK) &&
            (!sibling->left || sibling->left->color == Color::BLACK)) {
          // Оба ребенка брата черные
          sibling->color = Color::RED;
          node = parent;
          parent = node->parent;
        } else {
          if (!sibling->left || sibling->left->color == Color::BLACK) {
            // Правый ребенок брата красный, левый черный
            sibling->right->color = Color::BLACK;
            sibling->color = Color::RED;
            rotateLeft(sibling);
            sibling = parent->left;
          }
          //  Левый ребенок брата красный
          sibling->color = parent->color;
          parent->color = Color::BLACK;
          sibling->left->color = Color::BLACK;
          rotateRight(parent);
          node = root_;
        }
      }
    }

    if (node) {
      node->color = Color::BLACK;
    }
  }
};

}  // namespace s21

#endif  // S21_RBTREE_H