#ifndef AVL_TREE_H
#define AVL_TREE_H
#include <vector>
namespace s21 {

template <typename Key, typename Value>
class BinaryAVLTree {
 public:
  class TreeIterator;
  class ConstTreeIterator;

  using key_type = Key;
  using mapped_type = Value;
  using value_type = std::pair<key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = TreeIterator;
  using const_iterator = ConstTreeIterator;
  using size_type = size_t;

  typedef struct Node {
    value_type value;
    Node* parent = nullptr;
    Node* left = nullptr;
    Node* right = nullptr;
    unsigned char height = 0;

    Node(value_type val, Node* par = nullptr);
  } Node;

  class TreeIterator {
   public:
    TreeIterator() noexcept;
    TreeIterator(Node* currNode, BinaryAVLTree* ownerTree);

    iterator& operator++();
    iterator operator++(int);

    iterator& operator--();
    iterator operator--(int);

    reference operator*() const;
    bool operator==(const iterator& other) const;
    bool operator!=(const iterator& other) const;

   protected:
    Node* currentNode;
    BinaryAVLTree* ownerTree;
  };

  class ConstTreeIterator : public TreeIterator {
   public:
    ConstTreeIterator() noexcept : TreeIterator() {};
    ConstTreeIterator(Node* currNode, BinaryAVLTree* ownerTree)
        : TreeIterator(currNode, ownerTree) {};
    ConstTreeIterator(const TreeIterator& other)
        : ConstTreeIterator(other.currentNode, other.ownerTree) {};

    const_iterator& operator++();
    const_iterator operator++(int);

    const_iterator& operator--();
    const_iterator operator--(int);

    const_reference operator*() const;
  };

  BinaryAVLTree() noexcept;
  BinaryAVLTree(const BinaryAVLTree& other);
  BinaryAVLTree(BinaryAVLTree&& other) noexcept;
  ~BinaryAVLTree();

  BinaryAVLTree& operator=(const BinaryAVLTree& other);
  BinaryAVLTree& operator=(BinaryAVLTree&& other);
  mapped_type& at(const Key& key);
  mapped_type& operator[](const Key& key);
  iterator begin();
  iterator end();
  const_iterator cbegin();
  const_iterator cend();
  std::pair<iterator, bool> insert(const value_type& value);
  std::pair<iterator, bool> insert(const Key& key, const mapped_type& obj);
  std::pair<iterator, bool> insert_or_assign(const Key& key,
                                             const mapped_type& obj);
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args);

  iterator find(const Key& key);
  bool contains(const Key& key);
  void clear();
  void erase(iterator pos);
  void swap(BinaryAVLTree& other);
  void merge(BinaryAVLTree& other);
  bool empty();
  size_type size();
  size_type max_size();

 protected:
  Node* findMin(Node* currentNode);
  Node* findMax(Node* currentNode);
  Node* getNode(Node* currentNode, const Key& keyToFind);
  bool setNode(Node* currentNode, const value_type& valueToSet);
  Node* deleteNode(Node* currentNode, const Key& key);
  void freeNodes(Node* currentNode);
  size_type getNodesAmount(Node* currentNode);
  Node* cloneTree(Node* currentNode, Node* clonedParentNode);

  // Balancing AVL
  void rightRotate(Node* currentNode);
  void leftRotate(Node* currentNode);
  void balance(Node* currentNode);
  int getBalance(Node* currentNode);
  int getHeight(Node* currentNode);
  void setHeight(Node* currentNode);

  Node* root;
};

}  // namespace s21

#include "BinaryAVLTree.tpp"

#endif