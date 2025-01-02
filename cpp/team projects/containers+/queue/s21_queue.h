#include <stdlib.h>
#include <string.h>

#include <iostream>

namespace s21 {

class queue_exception : public std::exception {
 private:
  std::string message_;

 public:
  explicit queue_exception(const std::string &message) : message_(message){};
};

template <class T>
class queue {
 public:
  using size_type = size_t;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;

  queue() {
    queue_first = NULL;
    queue_last = NULL;
    lenn = 0;
    queue_list = NULL;
  }

  queue(std::initializer_list<value_type> const &items) {
    queue_list = NULL;
    queue_last = NULL;
    queue_first = NULL;
    lenn = 0;
    queue_list = (value_type *)malloc(items.size() * sizeof(value_type));
    for (const auto i : items) {
      queue_list[lenn] = i;
      lenn++;
    }
    queue_first = queue_list;
    queue_last = queue_list + (lenn - 1);
  }

  queue(const queue &q) {
    lenn = q.lenn;
    queue_list = (value_type *)malloc(q.lenn * sizeof(value_type));
    for (size_type i = 0; i < lenn; i++) {
      queue_list[i] = q.queue_list[i];
    }
    queue_first = queue_list;
    queue_last = queue_list + (lenn - 1);
  }

  queue(queue &&q) {
    std::swap(queue_list, q.queue_list);
    std::swap(queue_first, q.queue_first);
    std::swap(queue_last, q.queue_last);
    std::swap(lenn, q.lenn);
    q.queue_list = nullptr;
    q.queue_last = nullptr;
    q.queue_first = nullptr;
    q.lenn = 0;
  }

  ~queue() {
    queue_first = NULL;
    queue_last = NULL;
    free(queue_list);
    queue_list = NULL;
  }

  queue<T> &operator=(queue &&q) {
    if (this == &q) {
      return *this;
    }
    if (queue_list) {
      queue_first = NULL;
      queue_last = NULL;
      free(queue_list);
      queue_list = NULL;
    }
    lenn = q.lenn;
    queue_list = (value_type *)malloc(lenn * sizeof(value_type));
    for (size_type i = 0; i < lenn; i++) {
      queue_list[i] = q.queue_list[i];
    }
    queue_first = queue_list;
    queue_last = queue_list + (lenn - 1);
    return *this;
  }

  bool empty() { return lenn == 0 ? true : false; }

  size_type size() { return lenn; }

  const_reference front() {
    if (!queue_first) {
      throw queue_exception("Empty queue");
    }
    return *queue_first;
  }

  const_reference back() {
    if (!queue_last) {
      throw queue_exception("Empty queue");
    }
    return *queue_last;
  }

  void push(const_reference value) {
    if (!queue_list) {
      queue_first = NULL;
      queue_last = NULL;
      queue_list = (value_type *)malloc(sizeof(value_type));
      lenn = 1;
    } else {
      queue_last = NULL;
      queue_list =
          (value_type *)realloc(queue_list, sizeof(value_type) * (lenn + 1));
      lenn++;
    }
    queue_list[lenn - 1] = value;
    queue_last = queue_list + (lenn - 1);
    queue_first = queue_list;
  }

  void pop() {
    if (!queue_list || lenn < 1) {
      throw queue_exception("Empty queue");
    } else if (lenn > 1) {
      queue_first = NULL;
      queue_last = NULL;
      value_type *new_list =
          (value_type *)malloc(sizeof(value_type) * (lenn - 1));
      memcpy(new_list, queue_list + 1, sizeof(value_type) * (lenn - 1));
      lenn--;
      free(queue_list);
      queue_list = (value_type *)malloc(sizeof(value_type) * lenn);
      memcpy(queue_list, new_list, sizeof(value_type) * lenn);
      free(new_list);
      queue_first = queue_list;
      queue_last = queue_list + (lenn - 1);
    } else {
      lenn = 0;
      queue_last = NULL;
      queue_first = NULL;
      free(queue_list);
      queue_list = (value_type *)malloc(sizeof(value_type));
    }
  }

  void swap(queue &other) {
    queue<value_type> temp{other};
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
  value_type *queue_first;
  value_type *queue_last;
  value_type *queue_list;
  size_type lenn;
};

}  // namespace s21