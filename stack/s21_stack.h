#ifndef STACK_H
#define STACK_H

#include <cstddef>
#include <initializer_list>
#include <utility>

namespace s21 {

template <typename T>
class stack {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;

 private:
  struct Node {
    value_type data;
    Node* next;
    explicit Node(const_reference value) : data(value), next(nullptr) {}
  };

  Node* top_node;
  size_type stack_size;

 public:
  stack() : top_node(nullptr), stack_size(0) {}

  stack(std::initializer_list<value_type> const& items) : stack() {
    typename std::initializer_list<value_type>::const_iterator const_it =
        items.begin();

    while (const_it != items.end()) {
      push(*const_it);
      ++const_it;
    }
  }

  stack(const stack& s) : stack() {
    if (s.top_node) {
      Node* temp = s.top_node;
      stack new_stack;

      while (temp) {
        new_stack.push(temp->data);
        temp = temp->next;
      }

      while (!new_stack.empty()) {
        push(new_stack.top());
        new_stack.pop();
      }
    }
  }

  stack(stack&& s) : top_node(s.top_node), stack_size(s.stack_size) {
    s.top_node = nullptr;
    s.stack_size = 0;
  }

  ~stack() { clear(); }

  stack& operator=(stack&& s) {
    if (this != &s) {
      clear();

      top_node = s.top_node;
      stack_size = s.stack_size;

      s.top_node = nullptr;
      s.stack_size = 0;
    }

    return *this;
  }

  const_reference top() const { return top_node->data; }

  bool empty() const { return stack_size == 0; }

  size_type size() const { return stack_size; }

  void push(const_reference value) {
    Node* new_node = new Node(value);

    new_node->next = top_node;
    top_node = new_node;

    ++stack_size;
  }

  void pop() {
    if (!top_node) return;

    Node* temp = top_node;
    top_node = top_node->next;

    delete temp;
    --stack_size;
  }

  void swap(stack& other) {
    Node* temp_node = top_node;
    size_type temp_size = stack_size;

    top_node = other.top_node;
    stack_size = other.stack_size;

    other.top_node = temp_node;
    other.stack_size = temp_size;
  }

  template <typename... Args>
  void insert_many_back(Args&&... args) {
    if constexpr (sizeof...(args) == 0) return;

    (push(std::forward<Args>(args)), ...);
  }

 private:
  void clear() {
    while (!empty()) {
      pop();
    }
  }
};

}  // namespace s21

#endif  // STACK_H