#ifndef __S21_VECTOR_H__
#define __S21_VECTOR_H__

#include <iostream>
#include <limits>

namespace s21 {

template <typename T>
class vector {
 public:
  class VectorIterator;
  class VectorConstIterator;

  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using iterator = vector<T>::VectorIterator;
  using const_iterator = vector<T>::VectorConstIterator;

  vector();
  vector(size_type size);
  vector(std::initializer_list<value_type> const &items);
  vector(const vector &v);
  vector(vector &&v);
  vector operator=(vector &&v);
  ~vector();

  reference operator[](size_type pos);
  reference at(size_type pos);
  const_reference front();
  const_reference back();

  iterator begin();
  iterator end();
  const_iterator cbegin();
  const_iterator cend();

  bool empty() const;
  size_type max_size() const;
  void reserve(size_type size);
  void shrink_to_fit();

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector &other);

  template <typename... Args>
  void insert_many_back(Args &&...args);
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);

  size_type size() const;
  size_type capacity() const;
  value_type *data() const;

 private:
  value_type *data_;
  size_type size_;
  size_type capacity_;
};

}  // namespace s21

#include "s21_vector.tpp"
#include "s21_vector_iterator.h"

#endif