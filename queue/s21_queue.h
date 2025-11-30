#ifndef QUEUE_H
#define QUEUE_H

#include <cstddef>
#include <initializer_list>
#include <utility>

namespace s21 {

template <typename T>
class queue {
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
  size_type queue_size;

 public:
  queue() : head(nullptr), tail(nullptr), queue_size(0) {}

  queue(std::initializer_list<T> const& items) : queue() {
    typename std::initializer_list<T>::const_iterator const_it = items.begin();

    while (const_it != items.end()) {
      push(*const_it);
      ++const_it;
    }
  }

  queue(const queue& q) : queue() {
    for (Node* curr = q.head; curr; curr = curr->next) {
      push(curr->data);
    }
  }

  queue(queue&& q) : head(q.head), tail(q.tail), queue_size(q.queue_size) {
    q.head = q.tail = nullptr;
    q.queue_size = 0;
  }

  ~queue() { clear(); }

  queue& operator=(queue&& q) {
    if (this != &q) {
      clear();

      head = q.head;
      tail = q.tail;
      queue_size = q.queue_size;

      q.head = q.tail = nullptr;
      q.queue_size = 0;
    }

    return *this;
  }

  const_reference front() const { return head->data; }
  const_reference back() const { return tail->data; }

  bool empty() const { return queue_size == 0; }

  size_type size() const { return queue_size; }

  void push(const_reference value) {
    Node* new_node = new Node(value);

    if (!tail) {
      head = tail = new_node;
    } else {
      tail->next = new_node;
      new_node->prev = tail;
      tail = new_node;
    }

    ++queue_size;
  }

  void pop() {
    if (!head) return;

    Node* temp = head;
    head = head->next;

    if (head)
      head->prev = nullptr;
    else
      tail = nullptr;

    delete temp;
    --queue_size;
  }

  void swap(queue& other) {
    Node* temp_head = head;
    Node* temp_tail = tail;
    size_type temp_size = queue_size;

    head = other.head;
    tail = other.tail;
    queue_size = other.queue_size;

    other.head = temp_head;
    other.tail = temp_tail;
    other.queue_size = temp_size;
  }

  template <typename... Args>
  void insert_many_back(Args&&... args) {
    if constexpr (sizeof...(args) == 0) return;

    (push(std::forward<Args>(args)), ...);
  }

 private:
  void clear() {
    while (!empty()) pop();
  }
};

}  // namespace s21

#endif  // QUEUE_H