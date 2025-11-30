#ifndef LIST_H
#define LIST_H

#include <cstddef>
#include <initializer_list>
#include <limits>
#include <utility>

namespace s21 {

template <typename T>
class list {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;

 private:
  struct Node {
    value_type data;
    Node* next;
    Node* prev;

    explicit Node(const_reference value)
        : data(value), next(nullptr), prev(nullptr) {}
  };

  Node* head;
  Node* tail;
  size_type list_size;

 public:
  class iterator {
   public:
    Node* node;

    explicit iterator(Node* ptr) : node(ptr) {}

    iterator& operator++() {
      if (node) node = node->next;
      return *this;
    }

    iterator& operator--() {
      if (node) node = node->prev;
      return *this;
    }

    reference operator*() { return node->data; }

    bool operator==(const iterator& other) const { return node == other.node; }

    bool operator!=(const iterator& other) const { return node != other.node; }
  };

  class const_iterator {
   public:
    const Node* node;

    explicit const_iterator(const Node* ptr) : node(ptr) {}

    const_iterator& operator++() {
      if (node) node = node->next;
      return *this;
    }

    const_iterator& operator--() {
      if (node) node = node->prev;
      return *this;
    }

    const_reference operator*() const { return node->data; }

    bool operator==(const const_iterator& other) const {
      return node == other.node;
    }

    bool operator!=(const const_iterator& other) const {
      return node != other.node;
    }
  };

  list() : head(nullptr), tail(nullptr), list_size(0) {}

  explicit list(size_type n) : list() {
    while (n--) push_back(T());
  }

  list(std::initializer_list<T> const& items) : list() {
    typename std::initializer_list<T>::const_iterator const_it = items.begin();

    while (const_it != items.end()) {
      push_back(*const_it);
      ++const_it;
    }
  }

  list(const list& l) : list() {
    typename list::const_iterator it = l.begin();

    while (it != l.end()) {
      push_back(*it);
      ++it;
    }
  }

  list(list&& l) : head(l.head), tail(l.tail), list_size(l.list_size) {
    l.head = l.tail = nullptr;
    l.list_size = 0;
  }

  ~list() { clear(); }

  list& operator=(list&& l) {
    if (this != &l) {
      clear();

      head = l.head;
      tail = l.tail;
      list_size = l.list_size;

      l.head = l.tail = nullptr;
      l.list_size = 0;
    }

    return *this;
  }

  const_reference front() const { return head->data; }
  const_reference back() const { return tail->data; }

  iterator begin() { return iterator(head); }
  iterator end() { return iterator(nullptr); }

  const_iterator begin() const { return const_iterator(head); }
  const_iterator end() const { return const_iterator(nullptr); }

  bool empty() const { return list_size == 0; }

  size_type size() const { return list_size; }

  size_type max_size() const {
    return std::numeric_limits<size_type>::max() / sizeof(Node);
  }

  void clear() {
    while (!empty()) pop_back();
  }

  iterator insert(iterator pos, const_reference value) {
    Node* new_node = new Node(value);
    Node* current = pos.node;

    if (!current) {
      push_back(value);
      return --end();
    }

    new_node->next = current;
    new_node->prev = current->prev;

    if (current->prev) {
      current->prev->next = new_node;
    } else {
      head = new_node;
    }

    current->prev = new_node;
    ++list_size;

    return iterator(new_node);
  }

  void erase(iterator pos) {
    if (!pos.node) return;

    if (pos.node == head) {
      pop_front();
    } else if (pos.node == tail) {
      pop_back();
    } else {
      Node* current = pos.node;

      current->prev->next = current->next;
      current->next->prev = current->prev;

      delete current;
      --list_size;
    }
  }

  void push_back(const_reference value) {
    Node* new_node = new Node(value);

    if (!tail)
      head = tail = new_node;
    else {
      tail->next = new_node;
      new_node->prev = tail;
      tail = new_node;
    }

    ++list_size;
  }

  void pop_back() {
    if (!tail) return;

    Node* temp = tail;
    tail = tail->prev;

    if (tail)
      tail->next = nullptr;
    else
      head = nullptr;

    delete temp;
    --list_size;
  }

  void push_front(const_reference value) {
    Node* new_node = new Node(value);

    if (!head)
      head = tail = new_node;
    else {
      head->prev = new_node;
      new_node->next = head;
      head = new_node;
    }

    ++list_size;
  }

  void pop_front() {
    if (!head) return;

    Node* temp = head;
    head = head->next;

    if (head)
      head->prev = nullptr;
    else
      tail = nullptr;

    delete temp;
    --list_size;
  }

  void swap(list& other) {
    Node* temp_head = head;
    Node* temp_tail = tail;
    size_type temp_size = list_size;

    head = other.head;
    tail = other.tail;
    list_size = other.list_size;

    other.head = temp_head;
    other.tail = temp_tail;
    other.list_size = temp_size;
  }

  void merge(list& other) {
    if (this == &other || other.empty()) return;

    Node* current = head;
    Node* other_current = other.head;

    list merged_list;
    while (current || other_current) {
      if (!other_current || (current && current->data < other_current->data)) {
        merged_list.push_back(current->data);
        current = current->next;
      } else {
        merged_list.push_back(other_current->data);
        other_current = other_current->next;
      }
    }
    swap(merged_list);
    other.clear();
  }

  void splice(const_iterator pos, list& other) {
    if (this == &other || other.empty()) return;

    Node* first = other.head;
    Node* last = other.tail;

    const Node* const_pos_node = pos.node;

    if (!const_pos_node) {  // Вставка в конец
      if (tail)
        tail->next = first;
      else
        head = first;

      first->prev = tail;
      tail = last;
    } else {  // Вставка перед pos
      Node* pos_node = const_cast<Node*>(const_pos_node);

      first->prev = pos_node->prev;
      last->next = pos_node;

      if (pos_node->prev)
        pos_node->prev->next = first;
      else
        head = first;

      pos_node->prev = last;
    }

    list_size += other.list_size;
    other.head = other.tail = nullptr;
    other.list_size = 0;
  }

  void reverse() {
    if (empty()) return;

    Node* current = head;
    Node* temp = nullptr;

    while (current) {
      temp = current->prev;
      current->prev = current->next;
      current->next = temp;
      current = current->prev;
    }

    temp = head;
    head = tail;
    tail = temp;
  }

  void unique() {
    if (empty()) return;

    Node* current = head;
    while (current->next) {
      if (current->data == current->next->data) {
        Node* temp = current->next;
        current->next = temp->next;

        if (temp->next)
          temp->next->prev = current;
        else
          tail = current;

        delete temp;
        --list_size;
      } else {
        current = current->next;
      }
    }
  }

  void sort() {
    if (list_size < 2) return;

    for (Node* i = head->next; i; i = i->next) {
      T temp = i->data;
      Node* j = i->prev;

      while (j && j->data > temp) {
        j->next->data = j->data;
        j = j->prev;
      }

      if (j)
        j->next->data = temp;
      else
        head->data = temp;
    }
  }

  template <typename... Args>
  typename list<T>::iterator insert_many(const_iterator pos, Args&&... args) {
    if constexpr (sizeof...(args) == 0)
      return iterator(const_cast<Node*>(pos.node));

    const Node* pos_node = pos.node;
    const Node* prev_node = pos_node ? pos_node->prev : tail;

    Node* first_new_node = nullptr;
    Node* last_new_node = nullptr;

    insert_nodes(first_new_node, last_new_node, std::forward<Args>(args)...);

    Node* modifiable_prev_node = const_cast<Node*>(prev_node);
    Node* modifiable_pos_node = const_cast<Node*>(pos_node);

    if (modifiable_prev_node)
      modifiable_prev_node->next = first_new_node;

    else
      head = first_new_node;

    if (first_new_node) first_new_node->prev = modifiable_prev_node;

    if (modifiable_pos_node)
      modifiable_pos_node->prev = last_new_node;
    else
      tail = last_new_node;

    if (last_new_node) last_new_node->next = modifiable_pos_node;

    list_size += sizeof...(args);

    return iterator(first_new_node);
  }

  template <typename... Args>
  void insert_many_back(Args&&... args) {
    if constexpr (sizeof...(args) == 0) return;

    Node* first_new_node = nullptr;
    Node* last_new_node = nullptr;

    insert_nodes(first_new_node, last_new_node, std::forward<Args>(args)...);

    if (tail) {
      tail->next = first_new_node;
      first_new_node->prev = tail;
    } else
      head = first_new_node;

    tail = last_new_node;
    list_size += sizeof...(args);
  }

  template <typename... Args>
  void insert_many_front(Args&&... args) {
    if constexpr (sizeof...(args) == 0) return;

    Node* first_new_node = nullptr;
    Node* last_new_node = nullptr;

    insert_nodes(first_new_node, last_new_node, std::forward<Args>(args)...);

    if (head) {
      head->prev = last_new_node;
      last_new_node->next = head;
    } else
      tail = last_new_node;

    head = first_new_node;
    list_size += sizeof...(args);
  }

 private:
  template <typename... Args>
  void insert_nodes(Node*& first_new_node, Node*& last_new_node,
                    Args&&... args) {
    if constexpr (sizeof...(args) > 0) {  // Без этого условия ловит ошибки на
      for (const auto& arg : {std::forward<Args>(args)...}) {  // 0 аргументах
        Node* new_node = new Node(arg);

        if (!first_new_node) first_new_node = new_node;

        if (last_new_node) {
          last_new_node->next = new_node;
          new_node->prev = last_new_node;
        }

        last_new_node = new_node;
      }
    }
  }
};

}  // namespace s21

#endif  // LIST_H