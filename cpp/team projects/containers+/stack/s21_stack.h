#include <stdlib.h>
#include <string.h>

#include <iostream>

namespace s21 {

class stack_exception : public std::exception {
 private:
  std::string message_;

 public:
  explicit stack_exception(const std::string &message) : message_(message){};
};

template <class T>
class stack {
 public:
  using size_type = size_t;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  stack() {
    stack_last = NULL;
    lenn = 0;
    stack_list = NULL;
  }

  stack(std::initializer_list<value_type> const &items) {
    stack_list = NULL;
    stack_last = NULL;
    lenn = 0;
    stack_list = (value_type *)malloc(items.size() * sizeof(value_type));
    for (const auto i : items) {
      stack_list[lenn] = i;
      lenn++;
    }
    stack_last = stack_list + (lenn - 1);
  }

  stack(const stack &q) {
    lenn = q.lenn;
    stack_list = (value_type *)malloc(q.lenn * sizeof(value_type));
    for (size_type i = 0; i < lenn; i++) {
      stack_list[i] = q.stack_list[i];
    }
    stack_last = stack_list + (lenn - 1);
  }

  stack(stack &&q) {
    std::swap(stack_list, q.stack_list);
    std::swap(stack_last, q.stack_last);
    std::swap(lenn, q.lenn);
    q.stack_list = nullptr;
    q.stack_last = nullptr;
    q.lenn = 0;
  }

  ~stack() {
    stack_last = NULL;
    free(stack_list);
    stack_list = NULL;
  }

  stack<T> &operator=(stack &&q) {
    if (this == &q) {
      return *this;
    }
    if (stack_list) {
      stack_last = NULL;
      free(stack_list);
      stack_list = NULL;
    }
    lenn = q.lenn;
    stack_list = (value_type *)malloc(lenn * sizeof(value_type));
    for (size_type i = 0; i < lenn; i++) {
      stack_list[i] = q.stack_list[i];
    }
    stack_last = stack_list + (lenn - 1);
    return *this;
  }

  bool empty() { return lenn == 0 ? true : false; }

  size_type size() { return lenn; }

  const_reference top() {
    if (!stack_last) {
      throw stack_exception("Empty stack");
    }
    return *stack_last;
  }

  void push(const_reference value) {
    if (!stack_list) {
      stack_last = NULL;
      stack_list = (value_type *)malloc(sizeof(value_type));
      lenn = 1;
    } else {
      stack_last = NULL;
      stack_list =
          (value_type *)realloc(stack_list, sizeof(value_type) * (lenn + 1));
      lenn++;
    }
    stack_list[lenn - 1] = value;
    stack_last = stack_list + (lenn - 1);
  }

  void pop() {
    if (!stack_list || lenn < 1) {
      throw stack_exception("Empty stack");
    } else if (lenn > 1) {
      stack_last = NULL;
      value_type *new_list =
          (value_type *)malloc(sizeof(value_type) * (lenn - 1));
      memcpy(new_list, stack_list, sizeof(value_type) * (lenn - 1));
      lenn--;
      free(stack_list);
      stack_list = (value_type *)malloc(sizeof(value_type) * lenn);
      memcpy(stack_list, new_list, sizeof(value_type) * lenn);
      free(new_list);
      stack_last = stack_list + (lenn - 1);
    } else {
      lenn = 0;
      stack_last = NULL;
      free(stack_list);
      stack_list = (value_type *)malloc(sizeof(value_type));
    }
  }

  void swap(stack &other) {
    stack<value_type> temp{other};
    other = std::move(*this);
    *this = std::move(temp);
  }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    for (auto i : {args...}) {
      push(i);
    }
  }

 private:
  value_type *stack_last;
  value_type *stack_list;
  size_type lenn;
};

}  // namespace s21
