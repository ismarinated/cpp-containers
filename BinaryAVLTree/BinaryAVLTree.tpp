#include <limits>
#include <utility>

#include "BinaryAVLTree.h"

namespace s21 {

template <typename Key, typename Value>
BinaryAVLTree<Key, Value>::BinaryAVLTree() noexcept : root(nullptr) {}

template <typename Key, typename Value>
BinaryAVLTree<Key, Value>::BinaryAVLTree(const BinaryAVLTree& other) {
  root = cloneTree(other.root, nullptr);
}

template <typename Key, typename Value>
BinaryAVLTree<Key, Value>::BinaryAVLTree(BinaryAVLTree&& other) noexcept {
  root = other.root;
  other.root = nullptr;
}

template <typename Key, typename Value>
BinaryAVLTree<Key, Value>::~BinaryAVLTree() {
  clear();
}

template <typename Key, typename Value>
BinaryAVLTree<Key, Value>& BinaryAVLTree<Key, Value>::operator=(
    const BinaryAVLTree& other) {
  if (this != &other) {
    clear();
    BinaryAVLTree tmp(other);
    *this = std::move(tmp);
  }

  return *this;
}

template <typename Key, typename Value>
BinaryAVLTree<Key, Value>& BinaryAVLTree<Key, Value>::operator=(
    BinaryAVLTree&& other) {
  if (this != &other) {
    clear();
    root = other.root;
    other.root = nullptr;
  }

  return *this;
}

template <typename Key, typename Value>
typename BinaryAVLTree<Key, Value>::mapped_type& BinaryAVLTree<Key, Value>::at(
    const Key& key) {
  Node* node = getNode(root, key);
  if (node == nullptr) {
    throw std::out_of_range("The key is not present in the container");
  }
  return node->value.second;
}

template <typename Key, typename Value>
typename BinaryAVLTree<Key, Value>::mapped_type&
BinaryAVLTree<Key, Value>::operator[](const Key& key) {
  std::pair<iterator, bool> result = insert(std::make_pair(key, mapped_type{}));
  return (*result.first).second;
}

template <typename Key, typename Value>
std::pair<typename BinaryAVLTree<Key, Value>::iterator, bool>
BinaryAVLTree<Key, Value>::insert(const value_type& insValue) {
  std::pair<iterator, bool> result;
  if (root == nullptr) {
    root = new Node(insValue);
    result.first = iterator(root, this);
    result.second = true;
  } else {
    bool setResult = setNode(root, insValue);
    result = std::make_pair(find(insValue.first), setResult);
  }
  return result;
}

template <typename Key, typename Value>
std::pair<typename BinaryAVLTree<Key, Value>::iterator, bool>
BinaryAVLTree<Key, Value>::insert(const Key& key, const mapped_type& obj) {
  return insert(std::make_pair(key, obj));
}

template <typename Key, typename Value>
std::pair<typename BinaryAVLTree<Key, Value>::iterator, bool>
BinaryAVLTree<Key, Value>::insert_or_assign(const Key& key,
                                            const mapped_type& obj) {
  root = deleteNode(root, key);
  return insert(key, obj);
}

template <typename Key, typename Value>
template <typename... Args>
std::vector<std::pair<typename BinaryAVLTree<Key, Value>::iterator, bool>>
BinaryAVLTree<Key, Value>::insert_many(Args&&... args) {
  std::vector<std::pair<iterator, bool>> resVector;
  for (const auto& arg : {args...}) {
    resVector.push_back(insert(arg));
  }

  return resVector;
}

template <typename Key, typename Value>
typename BinaryAVLTree<Key, Value>::iterator BinaryAVLTree<Key, Value>::find(
    const Key& key) {
  return iterator(getNode(root, key), this);
}

template <typename Key, typename Value>
void BinaryAVLTree<Key, Value>::clear() {
  if (root != nullptr) {
    freeNodes(root);
    root = nullptr;
  }
}

template <typename Key, typename Value>
bool BinaryAVLTree<Key, Value>::empty() {
  return root == nullptr;
}

template <typename Key, typename Value>
typename BinaryAVLTree<Key, Value>::size_type
BinaryAVLTree<Key, Value>::size() {
  return getNodesAmount(root);
}

template <typename Key, typename Value>
typename BinaryAVLTree<Key, Value>::size_type
BinaryAVLTree<Key, Value>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(Node);
}

template <typename Key, typename Value>
bool BinaryAVLTree<Key, Value>::setNode(Node* currentNode,
                                        const value_type& valueToSet) {
  bool insertResult = false;
  if (currentNode->value.first > valueToSet.first) {
    if (currentNode->left == nullptr) {
      currentNode->left = new Node(valueToSet, currentNode);
      insertResult = true;
    } else {
      setNode(currentNode->left, valueToSet);
    }
  } else if (currentNode->value.first < valueToSet.first) {
    if (currentNode->right == nullptr) {
      currentNode->right = new Node(valueToSet, currentNode);
    } else {
      setNode(currentNode->right, valueToSet);
      insertResult = true;
    }
  }

  setHeight(currentNode);
  balance(currentNode);
  return insertResult;
}

template <typename Key, typename Value>
typename BinaryAVLTree<Key, Value>::Node* BinaryAVLTree<Key, Value>::getNode(
    Node* currentNode, const Key& keyToFind) {
  Node* desiredNode;
  if (currentNode == nullptr || currentNode->value.first == keyToFind) {
    desiredNode = currentNode;
  } else if (currentNode->value.first < keyToFind) {
    desiredNode = getNode(currentNode->right, keyToFind);
  } else {
    desiredNode = getNode(currentNode->left, keyToFind);
  }
  return desiredNode;
}

template <typename Key, typename Value>
typename BinaryAVLTree<Key, Value>::Node* BinaryAVLTree<Key, Value>::deleteNode(
    Node* currentNode, const Key& keyToDelete) {
  if (currentNode == nullptr) {
    return nullptr;
  }

  if (currentNode->value.first > keyToDelete) {
    currentNode->left = deleteNode(currentNode->left, keyToDelete);
  } else if (currentNode->value.first < keyToDelete) {
    currentNode->right = deleteNode(currentNode->right, keyToDelete);
  } else {
    Node* parentNode = currentNode->parent;
    Node* rightNode = currentNode->right;
    Node* leftNode = currentNode->left;
    if (currentNode->left == nullptr && currentNode->right == nullptr) {
      delete currentNode;
      currentNode = nullptr;
    } else if (currentNode->left == nullptr) {
      delete currentNode;
      currentNode = rightNode;
      if (currentNode != nullptr) {
        currentNode->parent = parentNode;
      }
    } else if (currentNode->right == nullptr) {
      delete currentNode;
      currentNode = leftNode;
      if (currentNode != nullptr) {
        currentNode->parent = parentNode;
      }
    } else {
      Node* minNode = findMin(currentNode->right);
      currentNode->value = minNode->value;
      currentNode->right = deleteNode(currentNode->right, minNode->value.first);
    }
  }

  if (currentNode != nullptr) {
    setHeight(currentNode);
    balance(currentNode);
  }

  return currentNode;
}

template <typename Key, typename Value>
void BinaryAVLTree<Key, Value>::freeNodes(Node* currentNode) {
  if (currentNode != nullptr) {
    freeNodes(currentNode->right);
    freeNodes(currentNode->left);
    delete currentNode;
  }
}

template <typename Key, typename Value>
typename BinaryAVLTree<Key, Value>::size_type
BinaryAVLTree<Key, Value>::getNodesAmount(Node* currentNode) {
  if (currentNode == nullptr) {
    return 0;
  }

  size_type leftSubTreeSize = getNodesAmount(currentNode->left);
  size_type rightSubTreeSize = getNodesAmount(currentNode->right);

  return 1 + leftSubTreeSize + rightSubTreeSize;
}

template <typename Key, typename Value>
typename BinaryAVLTree<Key, Value>::Node* BinaryAVLTree<Key, Value>::cloneTree(
    Node* currentNode, Node* clonedParentNode) {
  if (currentNode == nullptr) {
    return nullptr;
  }

  Node* clonedNode = new Node(currentNode->value, clonedParentNode);
  clonedNode->left = cloneTree(currentNode->left, clonedNode);
  clonedNode->right = cloneTree(currentNode->right, clonedNode);

  return clonedNode;
}

template <typename Key, typename Value>
typename BinaryAVLTree<Key, Value>::iterator
BinaryAVLTree<Key, Value>::begin() {
  return iterator(findMin(root), this);
}

template <typename Key, typename Value>
typename BinaryAVLTree<Key, Value>::iterator BinaryAVLTree<Key, Value>::end() {
  return iterator(nullptr, this);
}

template <typename Key, typename Value>
typename BinaryAVLTree<Key, Value>::const_iterator
BinaryAVLTree<Key, Value>::cbegin() {
  return const_iterator(findMin(root), this);
}

template <typename Key, typename Value>
typename BinaryAVLTree<Key, Value>::const_iterator
BinaryAVLTree<Key, Value>::cend() {
  return const_iterator(nullptr, this);
}

template <typename Key, typename Value>
typename BinaryAVLTree<Key, Value>::Node* BinaryAVLTree<Key, Value>::findMin(
    Node* currentNode) {
  Node* minNode;
  if (currentNode == nullptr) {
    minNode = nullptr;
  } else if (currentNode->left == nullptr) {
    minNode = currentNode;
  } else {
    minNode = findMin(currentNode->left);
  }

  return minNode;
}

template <typename Key, typename Value>
typename BinaryAVLTree<Key, Value>::Node* BinaryAVLTree<Key, Value>::findMax(
    Node* currentNode) {
  Node* maxNode;
  if (currentNode == nullptr) {
    maxNode = nullptr;
  } else if (currentNode->right == nullptr) {
    maxNode = currentNode;
  } else {
    maxNode = findMax(currentNode->right);
  }

  return maxNode;
}

template <typename Key, typename Value>
bool BinaryAVLTree<Key, Value>::contains(const Key& key) {
  return !(getNode(root, key) == nullptr);
}

template <typename Key, typename Value>
void BinaryAVLTree<Key, Value>::erase(iterator pos) {
  if (root == nullptr) {
    return;
  }
  root = deleteNode(root, (*pos).first);
}

template <typename Key, typename Value>
void BinaryAVLTree<Key, Value>::swap(BinaryAVLTree& other) {
  std::swap(root, other.root);
}

template <typename Key, typename Value>
void BinaryAVLTree<Key, Value>::merge(BinaryAVLTree& other) {
  if (this == &other) {
    return;
  }

  BinaryAVLTree copyOther(other);
  for (auto iter{copyOther.begin()}; iter != copyOther.end(); ++iter) {
    std::pair<iterator, bool> res = insert(*iter);
    if (res.second) other.erase(res.first);
  }
}

// Iterator
template <typename Key, typename Value>
BinaryAVLTree<Key, Value>::TreeIterator::TreeIterator() noexcept
    : currentNode(nullptr) {}

template <typename Key, typename Value>
BinaryAVLTree<Key, Value>::TreeIterator::TreeIterator(Node* currNode,
                                                      BinaryAVLTree* ownerTree)
    : currentNode(currNode), ownerTree(ownerTree) {}

template <typename Key, typename Value>
typename BinaryAVLTree<Key, Value>::iterator&
BinaryAVLTree<Key, Value>::TreeIterator::operator++() {
  if (currentNode != nullptr) {
    // If currentNode == nullptr do nothing
    if (currentNode->right) {
      // If right node exists -> turn right and then go left until you find the
      // minimum value
      currentNode = currentNode->right;
      while (currentNode->left) {
        currentNode = currentNode->left;
      }
    } else {
      // Go to parent node until you find the value that is bigger than current
      Node* prevNode = currentNode;
      currentNode = currentNode->parent;
      while (currentNode != nullptr && prevNode == currentNode->right) {
        prevNode = currentNode;
        currentNode = currentNode->parent;
      }
    }
  }

  return *this;
}

template <typename Key, typename Value>
typename BinaryAVLTree<Key, Value>::iterator
BinaryAVLTree<Key, Value>::TreeIterator::operator++(int) {
  iterator tmp = *this;
  operator++();
  return tmp;
}

template <typename Key, typename Value>
typename BinaryAVLTree<Key, Value>::iterator&
BinaryAVLTree<Key, Value>::TreeIterator::operator--() {
  if (currentNode == nullptr) {
    // Set the last node
    currentNode = ownerTree->findMax(ownerTree->root);
  } else if (currentNode->left) {
    // If left node exists -> turn left and then go right until you find the
    // maximum value
    currentNode = currentNode->left;
    while (currentNode->right) {
      currentNode = currentNode->right;
    }
  } else {
    // Go to parent node until you find the value that is smaller than current
    Node* prevNode = currentNode;
    currentNode = currentNode->parent;
    while (currentNode != nullptr && prevNode == currentNode->left) {
      currentNode = currentNode->parent;
    }
  }

  return *this;
}

template <typename Key, typename Value>
typename BinaryAVLTree<Key, Value>::iterator
BinaryAVLTree<Key, Value>::TreeIterator::operator--(int) {
  iterator tmp = *this;
  operator--();
  return tmp;
}

template <typename Key, typename Value>
typename BinaryAVLTree<Key, Value>::reference
BinaryAVLTree<Key, Value>::TreeIterator::operator*() const {
  if (currentNode == nullptr) {
    static value_type emptyValue{};
    return emptyValue;
  }
  return currentNode->value;
}

template <typename Key, typename Value>
bool BinaryAVLTree<Key, Value>::TreeIterator::operator==(
    const iterator& other) const {
  return currentNode == other.currentNode;
}

template <typename Key, typename Value>
bool BinaryAVLTree<Key, Value>::TreeIterator::operator!=(
    const iterator& other) const {
  return currentNode != other.currentNode;
}

// Const iterator
template <typename Key, typename Value>
typename BinaryAVLTree<Key, Value>::const_iterator&
BinaryAVLTree<Key, Value>::ConstTreeIterator::operator++() {
  TreeIterator::operator++();
  return *this;
}

template <typename Key, typename Value>
typename BinaryAVLTree<Key, Value>::const_iterator
BinaryAVLTree<Key, Value>::ConstTreeIterator::operator++(int) {
  ConstTreeIterator constTmp = TreeIterator::operator++(0);
  return constTmp;
}

template <typename Key, typename Value>
typename BinaryAVLTree<Key, Value>::const_iterator&
BinaryAVLTree<Key, Value>::ConstTreeIterator::operator--() {
  TreeIterator::operator--();
  return *this;
}

template <typename Key, typename Value>
typename BinaryAVLTree<Key, Value>::const_iterator
BinaryAVLTree<Key, Value>::ConstTreeIterator::operator--(int) {
  const_iterator constTmp = TreeIterator::operator--(0);
  return constTmp;
}

template <typename Key, typename Value>
typename BinaryAVLTree<Key, Value>::const_reference
BinaryAVLTree<Key, Value>::ConstTreeIterator::operator*() const {
  const_reference constVal = TreeIterator::operator*();
  return constVal;
}

// Node
template <typename Key, typename Value>
BinaryAVLTree<Key, Value>::Node::Node(value_type val, Node* par)
    : value(val), parent(par){};

// Balancing AVL
template <typename Key, typename Value>
int BinaryAVLTree<Key, Value>::getHeight(Node* currentNode) {
  return currentNode == nullptr ? 0 : currentNode->height;
}

template <typename Key, typename Value>
int BinaryAVLTree<Key, Value>::getBalance(Node* currentNode) {
  return currentNode == nullptr
             ? 0
             : getHeight(currentNode->right) - getHeight(currentNode->left);
}

template <typename Key, typename Value>
void BinaryAVLTree<Key, Value>::setHeight(Node* currentNode) {
  currentNode->height =
      std::max(getHeight(currentNode->left), getHeight(currentNode->right)) + 1;
}

template <typename Key, typename Value>
void BinaryAVLTree<Key, Value>::rightRotate(Node* currentNode) {
  Node* new_left = currentNode->left->left;
  Node* new_right_right = currentNode->right;
  Node* new_right_left = currentNode->left->right;

  std::swap(currentNode->value, currentNode->left->value);
  currentNode->right = currentNode->left;

  currentNode->left = new_left;
  if (currentNode->left) {
    currentNode->left->parent = currentNode;
  }

  currentNode->right->left = new_right_left;
  if (currentNode->right->left) {
    currentNode->right->left->parent = currentNode->right;
  }

  currentNode->right->right = new_right_right;
  if (currentNode->right->right) {
    currentNode->right->right->parent = currentNode->right;
  }

  setHeight(currentNode->right);
  setHeight(currentNode);
}

template <typename Key, typename Value>
void BinaryAVLTree<Key, Value>::leftRotate(Node* currentNode) {
  Node* new_right = currentNode->right->right;
  Node* new_left_left = currentNode->left;
  Node* new_left_right = currentNode->right->left;

  std::swap(currentNode->value, currentNode->right->value);
  currentNode->left = currentNode->right;

  currentNode->right = new_right;
  if (currentNode->right) {
    currentNode->right->parent = currentNode;
  }

  currentNode->left->right = new_left_right;
  if (currentNode->left->right) {
    currentNode->left->right->parent = currentNode->left;
  }

  currentNode->left->left = new_left_left;
  if (currentNode->left->left) {
    currentNode->left->left->parent = currentNode->left;
  }

  setHeight(currentNode->left);
  setHeight(currentNode);
}

template <typename Key, typename Value>
void BinaryAVLTree<Key, Value>::balance(Node* currentNode) {
  int balance = getBalance(currentNode);
  if (balance == -2) {
    if (getBalance(currentNode->left) == 1) leftRotate(currentNode->left);
    rightRotate(currentNode);
  } else if (balance == 2) {
    if (getBalance(currentNode->right) == -1) rightRotate(currentNode->right);
    leftRotate(currentNode);
  }
};
}  // namespace s21
