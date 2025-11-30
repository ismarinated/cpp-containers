#ifndef __S21_ARRAY_CPP__
#define __S21_ARRAY_CPP__

namespace s21 {

// --  Конструкторы

template <typename T, size_t N>
array<T, N>::array(std::initializer_list<value_type> const &items) {
  if (items.size() > N) {
    throw std::invalid_argument("too many initializers for array");
  }
  size_type i = 0;
  for (const auto &item : items) {
    data_[i] = item;
    i++;
  }
}

template <typename T, size_t N>
array<T, N>::array() : array({}) {}

template <typename T, size_t N>
array<T, N>::array(const array &a) {
  for (size_type i = 0; i < N; i++) {
    data_[i] = a.data_[i];
  }
}

template <typename T, size_t N>
array<T, N>::array(array &&a) {
  for (size_type i = 0; i < N; i++) {
    data_[i] = std::move(a.data_[i]);
  }
}

template <typename T, size_t N>
typename array<T, N>::array array<T, N>::operator=(array &&a) {
  for (size_type i = 0; i < N; i++) {
    data_[i] = std::move(a.data_[i]);
  }
  return *this;
}

// --  Итераторы

template <typename T, size_t N>
typename array<T, N>::iterator array<T, N>::begin() {
  return iterator(data_);
}

template <typename T, size_t N>
typename array<T, N>::iterator array<T, N>::end() {
  return iterator(data_ + N);
}

// -- Доступ к элементам класса

template <typename T, size_t N>
typename array<T, N>::reference array<T, N>::operator[](size_type pos) {
  return data_[pos];
}

template <typename T, size_t N>
typename array<T, N>::reference array<T, N>::at(size_type pos) {
  if (pos >= N) {
    throw std::out_of_range("array::at: __n (which is " + std::to_string(pos) +
                            ") >= _Nm (which is " + std::to_string(N) + ")");
  }
  auto res = iterator(data_ + (int)pos);
  return *res;
}

template <typename T, size_t N>
typename array<T, N>::const_reference array<T, N>::front() {
  return at(0);
}

template <typename T, size_t N>
typename array<T, N>::const_reference array<T, N>::back() {
  return at(N - 1);
}

// -- Методы для изменения

template <typename T, size_t N>
void array<T, N>::swap(array &other) {
  for (size_type i = 0; i < N; ++i) {
    value_type temp = data_[i];
    data_[i] = other.data_[i];
    other.data_[i] = temp;
  }
}

template <typename T, size_t N>
void array<T, N>::fill(const_reference value) {
  for (size_type i = 0; i < N; i++) {
    data_[i] = value;
  }
}

// -- Информации о наполнении массива

template <typename T, size_t N>
bool array<T, N>::empty() const {
  return N == 0;
}

template <typename T, size_t N>
typename array<T, N>::iterator array<T, N>::data() {
  return data_;
}

template <typename T, size_t N>
typename array<T, N>::size_type array<T, N>::size() const {
  return N;
}

template <typename T, size_t N>
typename array<T, N>::size_type array<T, N>::max_size() const {
  return N;
}

}  // namespace s21

#endif