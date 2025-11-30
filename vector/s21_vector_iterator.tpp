#ifndef __S21_VECTOR_ITERATOR_CPP__
#define __S21_VECTOR_ITERATOR_CPP__

namespace s21 {

// -- VectorIterator

template <typename T>
vector<T>::VectorIterator::VectorIterator(value_type* p) : ptr_(p) {}

template <typename T>
typename vector<T>::reference vector<T>::VectorIterator::operator*() {
  return *ptr_;
}

template <typename T>
typename vector<T>::VectorIterator vector<T>::VectorIterator::operator++(int) {
  vector<T>::VectorIterator temp = *this;
  ++(*this);
  return temp;
}

template <typename T>
typename vector<T>::VectorIterator& vector<T>::VectorIterator::operator++() {
  ++ptr_;
  return *this;
}

template <typename T>
typename vector<T>::VectorIterator vector<T>::VectorIterator::operator+(
    int value) const {
  return ptr_ + value;
}

template <typename T>
typename vector<T>::VectorIterator vector<T>::VectorIterator::operator--(int) {
  vector<T>::VectorIterator temp = *this;
  --(*this);
  return temp;
}

template <typename T>
typename vector<T>::VectorIterator& vector<T>::VectorIterator::operator--() {
  --ptr_;
  return *this;
}

template <typename T>
typename vector<T>::VectorIterator vector<T>::VectorIterator::operator-(
    int value) const {
  return ptr_ - value;
}

template <typename T>
bool vector<T>::VectorIterator::operator==(iterator iter) const {
  return ptr_ == iter.ptr_;
}

template <typename T>
bool vector<T>::VectorIterator::operator!=(iterator iter) const {
  return ptr_ != iter.ptr_;
}

template <typename T>
bool vector<T>::VectorIterator::operator>(iterator iter) const {
  return ptr_ > iter.ptr_;
}

template <typename T>
bool vector<T>::VectorIterator::operator<(iterator iter) const {
  return ptr_ < iter.ptr_;
}

template <typename T>
bool vector<T>::VectorIterator::operator>=(iterator iter) const {
  return ptr_ >= iter.ptr_;
}

template <typename T>
bool vector<T>::VectorIterator::operator<=(iterator iter) const {
  return ptr_ <= iter.ptr_;
}

// -- VectorConstIterator

template <typename T>
vector<T>::VectorConstIterator::VectorConstIterator(const value_type* p)
    : ptr_(p) {}

template <typename T>
typename vector<T>::const_reference vector<T>::VectorConstIterator::operator*()
    const {
  return *ptr_;
}

template <typename T>
typename vector<T>::VectorConstIterator
vector<T>::VectorConstIterator::operator++(int) {
  vector<T>::VectorConstIterator temp = *this;
  ++(*this);
  return temp;
}

template <typename T>
typename vector<T>::VectorConstIterator&
vector<T>::VectorConstIterator::operator++() {
  ++ptr_;
  return *this;
}

template <typename T>
typename vector<T>::VectorConstIterator
vector<T>::VectorConstIterator::operator+(int value) {
  return ptr_ + value;
}

template <typename T>
typename vector<T>::VectorConstIterator
vector<T>::VectorConstIterator::operator--(int) {
  vector<T>::VectorConstIterator temp = *this;
  --(*this);
  return temp;
}

template <typename T>
typename vector<T>::VectorConstIterator&
vector<T>::VectorConstIterator::operator--() {
  --ptr_;
  return *this;
}

template <typename T>
typename vector<T>::VectorConstIterator
vector<T>::VectorConstIterator::operator-(int value) {
  return ptr_ - value;
}

template <typename T>
ptrdiff_t vector<T>::VectorConstIterator::operator-(const_iterator iter) {
  return ptr_ - iter.ptr_;
}

template <typename T>
bool vector<T>::VectorConstIterator::operator==(const_iterator iter) const {
  return ptr_ == iter.ptr_;
}

template <typename T>
bool vector<T>::VectorConstIterator::operator!=(const_iterator iter) const {
  return ptr_ != iter.ptr_;
}

template <typename T>
bool vector<T>::VectorConstIterator::operator>(const_iterator iter) const {
  return ptr_ > iter.ptr_;
}

template <typename T>
bool vector<T>::VectorConstIterator::operator<(const_iterator iter) const {
  return ptr_ < iter.ptr_;
}

template <typename T>
bool vector<T>::VectorConstIterator::operator>=(const_iterator iter) const {
  return ptr_ >= iter.ptr_;
}

template <typename T>
bool vector<T>::VectorConstIterator::operator<=(const_iterator iter) const {
  return ptr_ <= iter.ptr_;
}

}  // namespace s21

#endif