#ifndef __S21_VECTOR_CPP__
#define __S21_VECTOR_CPP__

namespace s21 {

//-- Конструкторы

template <typename T>
vector<T>::vector(size_type size) {
  size_ = size;
  capacity_ = size;

  data_ = new value_type[size];
  for (size_type i = 0; i < size; i++) {
    data_[i] = value_type();
  }
}

template <typename T>
vector<T>::vector() : vector(0) {}

template <typename T>
vector<T>::vector(const vector &v) : vector(v.size_) {
  for (size_type i = 0; i < size_; i++) {
    data_[i] = v.data_[i];
  }
}

template <typename T>
vector<T>::vector(std::initializer_list<value_type> const &items)
    : vector(items.size()) {
  auto it = items.begin();
  for (size_type i = 0; i < size_; i++) {
    data_[i] = *it;
    it++;
  }
}

template <typename T>
vector<T>::vector(vector &&v) {
  size_ = v.size_;
  capacity_ = v.capacity_;
  data_ = v.data_;

  v.size_ = 0;
  v.capacity_ = 0;
  v.data_ = nullptr;
}

template <typename T>
vector<T>::~vector() {
  delete[] data_;
}

template <typename T>
typename vector<T>::vector vector<T>::operator=(vector &&v) {
  delete[] data_;
  size_ = v.size_;
  capacity_ = v.capacity_;
  data_ = v.data_;

  v.size_ = 0;
  v.capacity_ = 0;
  v.data_ = nullptr;

  return *this;
}

// -- Итераторы

template <typename T>
typename vector<T>::iterator vector<T>::begin() {
  return iterator(data_);
}

template <typename T>
typename vector<T>::iterator vector<T>::end() {
  return iterator(data_ + size_);
}

template <typename T>
typename vector<T>::const_iterator vector<T>::cbegin() {
  return const_iterator(data_);
}

template <typename T>
typename vector<T>::const_iterator vector<T>::cend() {
  return const_iterator(data_ + size_);
}

// -- Капасити

template <typename T>
bool vector<T>::empty() const {
  return size_ == 0;
}

template <typename T>
typename vector<T>::size_type vector<T>::max_size() const {
  return std::numeric_limits<size_type>::max() / sizeof(T) / 2;
}

template <typename T>
void vector<T>::reserve(size_type size) {
  if (size < capacity_) {
    return;
  }

  value_type *temp_data = new value_type[size];
  capacity_ = size;
  for (size_type i = 0; i < size_; i++) {
    temp_data[i] = data_[i];
  }

  delete[] data_;
  data_ = temp_data;
}

template <typename T>
void vector<T>::shrink_to_fit() {
  value_type *temp_data = new value_type[size_];
  for (size_type i = 0; i < size_; i++) {
    temp_data[i] = data_[i];
  }
  delete[] data_;
  data_ = temp_data;
  capacity_ = size_;
}

// -- Методы доступа к эементам

template <typename T>
typename vector<T>::reference vector<T>::operator[](size_type pos) {
  return data_[pos];
}

template <typename T>
typename vector<T>::reference vector<T>::at(size_type pos) {
  if (pos >= size_) {
    throw std::out_of_range(
        "vector::_M_range_check: __n (which is " + std::to_string(pos) +
        ") >= this->size() (which is " + std::to_string(size_) + ")");
  }
  auto res = iterator(data_ + (int)pos);
  return *res;
}

template <typename T>
typename vector<T>::const_reference vector<T>::front() {
  return at(0);
}

template <typename T>
typename vector<T>::const_reference vector<T>::back() {
  return at(size_ - 1);
}

// -- Методы работы с данными вектора

template <typename T>
void vector<T>::clear() {
  size_ = 0;
}

template <typename T>
void vector<T>::erase(iterator pos) {
  if (pos >= begin() && pos < end()) {
    for (iterator it = pos; it != end() - 1; ++it) {
      *it = *(it + 1);
    }
    size_--;
  }
}

template <typename T>
void vector<T>::swap(vector &other) {
  auto temp_data = data();
  auto temp_size = size();
  auto temp_capacity = capacity();

  data_ = other.data();
  size_ = other.size();
  capacity_ = other.capacity();

  other.data_ = temp_data;
  other.size_ = temp_size;
  other.capacity_ = temp_capacity;
}

template <typename T>
void vector<T>::pop_back() {
  if (size_ == 0) {
    return;
  }
  size_--;
}

template <typename T>
void vector<T>::push_back(const_reference value) {
  if (size_ == 0 && capacity_ == 0) {
    reserve(1);
  } else if (size_ + 1 > capacity_) {
    reserve(size_ * 2);
  }

  data_[size_] = value;
  size_++;
}

template <typename T>
template <typename... Args>
void vector<T>::insert_many_back(Args &&...args) {
  size_type size_args = sizeof...(args);
  if (size_ + size_args > capacity_) {
    reserve((size_ + size_args) * 2);
  }

  value_type temp[] = {std::forward<Args>(args)...};

  for (size_type i = 0; i < size_args; i++) {
    data_[size_++] = std::move(temp[i]);
  }
}

template <typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos,
                                               const_reference value) {
  if (size_ + 1 > capacity_) {
    int iterator_count = 0;
    for (iterator it = begin(); it != pos; ++it) {
      iterator_count++;
    }
    reserve(size_ * 2);
    pos = begin() + iterator_count;
  }
  size_++;

  for (iterator it = end() - 1; it > pos; --it) {
    *it = *(it - 1);
  }

  *pos = value;
  return pos;
}

template <typename T>
template <typename... Args>
typename vector<T>::iterator vector<T>::insert_many(const_iterator pos,
                                                    Args &&...args) {
  size_type pos_index = cend() - pos;

  if (pos_index > size_) {
    throw std::out_of_range("pos is out of vector");
  }

  size_type size_args = sizeof...(args);
  if (size_ + size_args > capacity_) {
    reserve((size_ + size_args) * 2);
  }
  size_ += size_args;

  for (size_type i = size_ - 1; i >= pos_index + size_args; i--) {
    data_[i] = data_[i - size_args];
  }

  value_type temp[] = {std::forward<Args>(args)...};

  for (size_type i = 0; i < size_args; i++) {
    data_[pos_index + i] = temp[i];
  }

  return iterator(&data_[pos_index]);
}

template <typename T>
typename vector<T>::size_type vector<T>::size() const {
  return size_;
}

template <typename T>
typename vector<T>::size_type vector<T>::capacity() const {
  return capacity_;
}

template <typename T>
typename vector<T>::value_type *vector<T>::data() const {
  return data_;
}

}  // namespace s21

#endif