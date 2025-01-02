#ifndef S21_CONTAINERS_MY_VECTOR_H
#define S21_CONTAINERS_MY_VECTOR_H
#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>

namespace s21 {
template <typename T>
class vector {
 public:
  /*  Vector Member type */
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  /* Vector Member functions */
  vector() : s21_arr(new T[1]), s21_size(0), s21_capacity(0) {}

  vector(size_type n) : s21_arr(new T[n]), s21_size(n), s21_capacity(n) {}

  vector(std::initializer_list<value_type> const &items)
      : s21_arr(new value_type[items.size()]),
        s21_size(items.size()),
        s21_capacity(items.size()) {
    std::copy(items.begin(), items.end(), s21_arr);
  }

  vector(const vector &v)
      : s21_arr(new value_type[v.s21_capacity]),
        s21_size(v.s21_size),
        s21_capacity(v.s21_capacity) {
    std::copy(v.s21_arr, v.s21_arr + v.s21_size, s21_arr);
  }

  vector(vector &&v) noexcept
      : s21_arr(v.s21_arr), s21_size(v.s21_size), s21_capacity(v.s21_capacity) {
    v.s21_arr = nullptr;
    v.s21_size = 0;
    v.s21_capacity = 0;
  }

  ~vector() {
    delete[] s21_arr;
    s21_size = 0;
    s21_capacity = 0;
    s21_arr = nullptr;
  }

  vector &operator=(vector &&v) noexcept {
    if (this != &v) {  // Проверка на самоприсваивание
      delete[] s21_arr;     // Освобождаем старый массив
      s21_arr = v.s21_arr;  // "Перемещаем" указатель
      s21_size = v.s21_size;
      s21_capacity = v.s21_capacity;
      // "Обнуляем" временный объект
      v.s21_arr = nullptr;
      v.s21_size = 0;
      v.s21_capacity = 0;
    }
    return *this;
  }

  /* Vector Element access */

  // Доступ к элементу по индексу
  // Метод at с проверкой границ
  reference at(size_type pos) {
    if (pos >= s21_size || !s21_arr) {
      throw std::out_of_range("Index out of range");
    }
    return s21_arr[pos];
  }

  // Неконстантный operator[] без проверки границ
  reference operator[](size_type pos) {
    if (pos >= s21_size || !s21_arr) {
      throw std::out_of_range("Index out of range");
    }
    return s21_arr[pos];
  }

  const_reference front() const {
    if (s21_size == 0) {
      throw std::out_of_range("Vector is empty");
    }
    return s21_arr[0];
  }

  const_reference back() const {
    if (s21_size == 0) {
      throw std::out_of_range("Vector is empty");
    }
    return s21_arr[s21_size - 1];
  }

  T *data() { return s21_arr; }

  const T *data() const { return s21_arr; }

  /* Vector Iterators */

  iterator begin() noexcept { return &this->s21_arr[0]; }

  iterator end() noexcept { return &this->s21_arr[s21_size]; }

  /* Vector Capacity */

  bool empty() const { return s21_size == 0; }

  size_type size() const { return s21_size; }

  size_type max_size() const {
    return std::numeric_limits<std::size_t>::max() / sizeof(value_type);
  }

  void reserve(size_type size) {
    if (size <= s21_capacity) return;
    // выделяется "сырая память" достаточная для хранения size элементов типа Т
    T *new_arr = reinterpret_cast<T *>(new int8_t[size * sizeof(T)]);
    size_type i = 0;
    try {
      std::uninitialized_copy(s21_arr, s21_arr + s21_size, new_arr);
    } catch (...) {
      // здесь деструкторы не вызываются, тк reinterpret_cast<int8_t*>
      // представляет наш массив ввиде набора байт, а не объктов
      delete[] reinterpret_cast<int8_t *>(new_arr);
      throw;
    }
    for (; i < s21_size; ++i) {
      (s21_arr + i)->~T();
    }
    delete[] reinterpret_cast<int8_t *>(s21_arr);
    s21_arr = new_arr;
    s21_capacity = size;
  }

  size_type capacity() const { return s21_capacity; }

  void shrink_to_fit() {
    if (s21_size < s21_capacity) {
      iterator new_arr = new value_type[s21_size];
      std::copy(s21_arr, s21_arr + s21_size, new_arr);
      delete[] s21_arr;
      s21_arr = new_arr;
      s21_capacity = s21_size;
    }
  }

  /* Vector Modifiers */

  void clear() noexcept { s21_size = 0; }

  iterator insert(iterator pos, const_reference value) {
    if (pos < begin() || pos > end()) {
      throw std::out_of_range("Iterator out of range");
    }

    size_type index = std::distance(begin(), pos);

    if (s21_size == s21_capacity) {
      reserve(s21_capacity == 0 ? 1 : 2 * s21_capacity);
    }

    std::move_backward(s21_arr + index, s21_arr + s21_size,
                       s21_arr + s21_size + 1);

    new (s21_arr + index) T(value);
    ++s21_size;

    return iterator(s21_arr + index);
  }

  void erase(iterator pos) {
    size_type index = std::distance(begin(), pos);

    (s21_arr + index)->~T();
    std::move(s21_arr + index + 1, s21_arr + s21_size, s21_arr + index);

    --s21_size;
  }

  void push_back(const T &value) {
    if (s21_capacity == 0) {
      s21_capacity = 1;
    }

    if (s21_capacity == s21_size) {
      reserve(2 * s21_size);
    }

    new (s21_arr + s21_size) T(value);
    ++s21_size;
  }

  void pop_back() {
    (s21_arr + s21_size - 1)->~T();
    --s21_size;
  }  // pop_back  по пустому массиву - segmentation fault - в оригинале тоже так

  void swap(vector &other) {
    std::swap(other.s21_size, s21_size);
    std::swap(other.s21_capacity, s21_capacity);
    std::swap(other.s21_arr, s21_arr);
  }

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args) {
    auto args_v =
        std::initializer_list<value_type>{std::forward<Args>(args)...};
    iterator tmp_pos = (iterator)pos;
    for (auto &i : args_v) {
      tmp_pos = insert(tmp_pos, i) + 1;
    }
    return tmp_pos - 1;
  }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    insert_many(end(), args...);
  }

 private:
  T *s21_arr;  // Указатель на динамический массив
  size_t s21_size;  // Текущий размер вектора (количество элементов)
  size_t s21_capacity;  // Текущая вместимость вектора (выделенная память)

};  // class

}  // namespace s21

#endif  // S21_CONTAINERS_MY_VECTOR_H