#ifndef __S21_ARRAY_H__
#define __S21_ARRAY_H__

#include <iostream>

namespace s21 {

template <typename T, size_t N>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using iterator = T *;
  using const_iterator = const T *;

  array(std::initializer_list<value_type> const &items);
  array();
  array(const array &a);
  array(array &&a);
  ~array() = default;

  array operator=(array &&a);
  reference operator[](size_type pos);

  iterator begin();
  iterator end();

  reference at(size_type pos);
  const_reference front();
  const_reference back();

  bool empty() const;

  iterator data();
  size_type size() const;
  size_type max_size() const;

  void swap(array &other);
  void fill(const_reference value);

 private:
  value_type data_[N]{};
};

}  // namespace s21

#include "s21_array.tpp"

#endif