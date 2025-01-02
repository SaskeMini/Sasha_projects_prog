#ifndef S21_CONTAINERS_MY_ARRAY_H
#define S21_CONTAINERS_MY_ARRAY_H

#include <iostream>
#include <limits>

namespace s21 {
template <typename T, size_t N>
class array {
 public:
  /* Array Member type */
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = const T*;
  using const_iterator = const T*;
  using size_type = size_t;

  /* Array Member functions */
  array() : s21_size(N) {}
  array(std::initializer_list<value_type> const& items) {
    std::copy(items.begin(), items.end(), s21_arr);
  }
  array(const array& a) {
    for (size_type i = 0; i < s21_size; ++i) {
      s21_arr[i] = a.s21_arr[i];
    }
  }
  array(array&& a) noexcept {
    for (size_t i = 0; i < N; ++i) {
      s21_arr[i] = std::move(a.s21_arr[i]);
    }
  }
  ~array() {}

  array& operator=(array&& a) noexcept {
    if (this != &a) {  // Проверка на самоприсваивание
      for (size_t i = 0; i < N; ++i) {
        s21_arr[i] = std::move(a.s21_arr[i]);
      }
    }
    return *this;
  }

  /* Array Element access */
  reference at(size_type pos) {
    if (pos >= s21_size || s21_size == 0) {
      throw std::out_of_range("Index out range");
    }
    return s21_arr[pos];
  }

  reference operator[](size_type pos) { return *(s21_arr + pos); }

  const_reference front() const { return s21_arr[0]; }
  const_reference back() const { return s21_arr[s21_size - 1]; }
  const_iterator data() const { return s21_arr; }

  /* Array Iterators */
  iterator begin() noexcept { return &this->s21_arr[0]; }
  iterator end() noexcept { return &this->s21_arr[s21_size]; }
  const_iterator begin() const noexcept { return &s21_arr[0]; }
  const_iterator end() const noexcept { return &s21_arr[s21_size]; }

  /* Array Capacity */
  bool empty() { return s21_size == 0; }
  size_type size() const { return s21_size; }
  size_type max_size() const noexcept { return N; }

  /* Array Modifiers */
  void swap(array& other) {
    if (this != &other) {
      for (size_t i = 0; i < N; ++i) {
        std::swap(s21_arr[i], other.s21_arr[i]);
      }
    }
  }

  void fill(const_reference value) {
    for (size_t i = 0; i < s21_size; ++i) {
      s21_arr[i] = value;
    }
  }

 private:
  value_type s21_arr[N];
  size_type s21_size = N;
};  // class array

}  // namespace s21

#endif  // S21_CONTAINERS_MY_ARRAY_H