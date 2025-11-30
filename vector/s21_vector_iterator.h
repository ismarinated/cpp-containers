#ifndef __S21_VECTOR_ITERATOR_H__
#define __S21_VECTOR_ITERATOR_H__

namespace s21 {

template <typename T>
class vector<T>::VectorIterator {
 private:
  value_type* ptr_;

 public:
  VectorIterator(value_type* p);

  reference operator*();

  VectorIterator& operator++();
  VectorIterator& operator--();
  VectorIterator operator++(int);
  VectorIterator operator--(int);
  VectorIterator operator+(int value) const;
  VectorIterator operator-(int value) const;

  bool operator==(iterator iter) const;
  bool operator!=(iterator iter) const;
  bool operator>(iterator iter) const;
  bool operator<(iterator iter) const;
  bool operator>=(iterator iter) const;
  bool operator<=(iterator iter) const;
};

template <typename T>
class vector<T>::VectorConstIterator {
 private:
  const value_type* ptr_;

 public:
  VectorConstIterator(const value_type* p);

  const_reference operator*() const;

  VectorConstIterator& operator++();
  VectorConstIterator& operator--();
  VectorConstIterator operator++(int);
  VectorConstIterator operator--(int);
  VectorConstIterator operator+(int value);
  VectorConstIterator operator-(int value);
  ptrdiff_t operator-(const_iterator iter);

  bool operator==(const_iterator iter) const;
  bool operator!=(const_iterator iter) const;
  bool operator>(const_iterator iter) const;
  bool operator<(const_iterator iter) const;
  bool operator>=(const_iterator iter) const;
  bool operator<=(const_iterator iter) const;
};

}  // namespace s21

#include "s21_vector_iterator.tpp"

#endif