#ifndef S21_CONTAINERS_LIST_H
#define S21_CONTAINERS_LIST_H

#include <iostream>
#include <limits>
namespace s21 {
template <typename T>
class list {
 private:
  struct Node {
    T data;
    Node *prev;
    Node *next;
  };
  size_t list_size;
  Node *first_node;
  Node *last_node;
  Node *temp_node;

  class ListIterator {
    friend class list;

   private:
    Node *curr_node;

   public:
    ListIterator(){};
    explicit ListIterator(Node *other) { curr_node = other; }
    ListIterator(ListIterator &other) { curr_node = other.curr_node; }

    ListIterator operator=(ListIterator other) {
      if (this != &other) {
        curr_node = other.curr_node;
      }
      return *this;
    }
    // *iter: получение элемента, на который указывает итератор;
    T &operator*() { return curr_node->data; }
    // ++iter: перемещение итератора вперед для обращения к следующему элементу;
    ListIterator operator++() {
      curr_node = curr_node->next;
      return *this;
    }
    ListIterator operator++(int) {
      ListIterator temp(curr_node);
      curr_node = curr_node->next;
      return temp;
    }
    // --iter: перемещение итератора назад для обращения к предыдущему элементу;
    ListIterator operator--() {
      curr_node = curr_node->prev;
      return *this;
    }
    ListIterator operator--(int) {
      ListIterator temp(curr_node);
      curr_node = curr_node->prev;
      return temp;
    }
    // iter1 == iter2: два итератора равны, если они указывают на один и тот же
    bool operator==(const ListIterator &other) {
      return (curr_node == other.curr_node);
    }
    // элемент; iter1 != iter2: два итератора не равны, если они указывают на
    // разные элементы.
    bool operator!=(const ListIterator &other) {
      return (curr_node != other.curr_node);
    }
  };

  class ListConstIterator {
    friend class list;

   private:
    Node *curr_node;

   public:
    ListConstIterator(){};
    explicit ListConstIterator(Node *other) { curr_node = other; }
    ListConstIterator(const ListConstIterator &other) {
      curr_node = other.curr_node;
    }
    ListConstIterator(const ListIterator &other) {
      curr_node = other.curr_node;
    }

    ListConstIterator operator=(const ListConstIterator other) {
      if (this != &other) {
        curr_node = other.curr_node;
      }
      return *this;
    }
    // *iter: получение элемента, на который указывает итератор;
    T &operator*() { return curr_node->data; }
    // ++iter: перемещение итератора вперед для обращения к следующему элементу;
    ListConstIterator operator++() {
      curr_node = curr_node->next;
      return *this;
    }
    ListConstIterator operator++(int) {
      ListConstIterator temp(curr_node);
      curr_node = curr_node->next;
      return temp;
    }
    // --iter: перемещение итератора назад для обращения к предыдущему элементу;
    ListConstIterator operator--() {
      curr_node = curr_node->prev;
      return *this;
    }
    ListConstIterator operator--(int) {
      ListConstIterator temp(curr_node);
      curr_node = curr_node->prev;
      return temp;
    }
    // iter1 == iter2: два итератора равны, если они указывают на один и тот же
    bool operator==(const ListIterator &other) {
      return (curr_node == other.curr_node);
    }
    bool operator==(const ListConstIterator &other) {
      return (curr_node == other.curr_node);
    }
    // элемент; iter1 != iter2: два итератора не равны, если они указывают на
    // разные элементы.
    bool operator!=(const ListIterator &other) {
      return (curr_node != other.curr_node);
    }
    bool operator!=(const ListConstIterator &other) {
      return (curr_node != other.curr_node);
    }
  };

 public:
  // T defines the type of an element (T is template parameter)
  using value_type = T;
  // T & defines the type of the reference to an element
  using reference = T &;
  // const T & defines the type of the constant reference
  using const_reference = const T &;
  // size_t defines the type of the container size (standard type is size_t)
  using size_type = size_t;
  // internal class ListIterator<T> defines the type for iterating through the
  // container
  using iterator = ListIterator;
  // internal class ListConstIterator<T> defines the constant type for iterating
  // through the container
  using const_iterator = ListConstIterator;

  // default constructor, creates empty list 
  list() {
    list_size = 0;
    first_node = new Node{};
    last_node = new Node{};
    first_node->next = last_node;
    last_node->prev = first_node;
  };
  // parameterized constructor, creates the list of size n
  list(size_type n) : list() {
    for (size_type i = 0; i < n; ++i) {
      push_back(value_type());
    }
  };
  // initializer list constructor, creates list initizialized using
  // std::initializer_list
  list(std::initializer_list<value_type> const &items) : list() {
    for (const value_type &value : items) {
      push_back(value);
    }
  };
  // copy constructor
  list(const list &l) : list() {
    for (auto it = l.cbegin(); it != l.cend(); ++it) {
      push_back(*it);
    }
  };
  // move constructor
  list(list &&l) : list(l) { l.clear(); };
  // destructor
  ~list() {
    clear();
    delete first_node;
    delete last_node;
  };
  // assignment operator overload for moving object
  list<value_type> &operator=(list &&l) {
    swap(l);
    l.clear();
    return *this;
  };

  // access the first element
  const_reference front() { return first_node->next->data; };
  // access the last element
  const_reference back() { return last_node->prev->data; };

  // returns an iterator to the beginning
  iterator begin() { return iterator(first_node->next); };
  // returns an iterator to the end
  iterator end() { return iterator(last_node); };

  // checks whether the container is empty
  bool empty() { return (list_size == 0); };
  // returns the number of elements
  size_type size() { return list_size; };
  // returns the maximum possible number of elements
  size_type max_size() {
    return (std::numeric_limits<size_type>::max() / sizeof(Node) / 2);
  };

  // clears the contents
  void clear() {
    while (first_node->next != last_node) {
      pop_front();
    }
  };
  // inserts element into concrete pos and returns the iterator that points to
  // the new element
  iterator insert(iterator pos, const_reference value) {
    Node *new_node = new Node;
    ++list_size;
    new_node->data = value;
    new_node->prev = pos.curr_node->prev;
    new_node->next = pos.curr_node;
    pos.curr_node->prev->next = new_node;
    pos.curr_node->prev = new_node;
    return pos;
  };
  // erases element at pos
  void erase(iterator pos) {
    if (pos.curr_node != last_node) {
      --list_size;
      pos.curr_node->prev->next = pos.curr_node->next;
      pos.curr_node->next->prev = pos.curr_node->prev;
      delete pos.curr_node;
    }
  };
  // adds an element to the end
  void push_back(const_reference value) { insert(end(), value); };
  // removes the last element
  void pop_back() { erase(--end()); };
  // adds an element to the head
  void push_front(const_reference value) { insert(begin(), value); };
  // removes the first element
  void pop_front() { erase(begin()); };

  // swaps the contents
  void swap(list &other) {
    temp_node = first_node;
    first_node = other.first_node;
    other.first_node = temp_node;
    temp_node = last_node;
    last_node = other.last_node;
    other.last_node = temp_node;
    size_type s = list_size;
    list_size = other.list_size;
    other.list_size = s;
  };
  // merges two sorted lists
  void merge(list &other) {
    for (auto it = begin(), jt = other.begin(); jt != other.end();) {
      if (*it > *jt || it == end()) {
        insert(it, *jt);
        ++jt;
      } else {
        ++it;
      }
    }
    other.clear();
  };
  // transfers elements from list other starting from pos
  void splice(const_iterator pos, list &other) {
    if (!other.empty()) {
      iterator it = begin();
      while (pos != it) {
        ++it;
      }
      for (auto jt = other.begin(); jt != other.end(); ++jt) {
        insert(it, *jt);
      }
      other.clear();
    }
  };
  // reverses the order of the elements
  void reverse() {
    Node *curr_node = first_node;
    while (curr_node != nullptr) {
      temp_node = curr_node->next;
      curr_node->next = curr_node->prev;
      curr_node->prev = temp_node;
      curr_node = curr_node->prev;
    }
    temp_node = first_node;
    first_node = last_node;
    last_node = temp_node;
  };
  // removes consecutive duplicate elements
  void unique() {
    for (auto it = begin(); it != end(); ++it) {
      auto tempi = ++it;
      --it;
      for (auto jt = tempi; *jt == *it && jt != end();) {
        auto tempj = jt;
        ++jt;
        erase(tempj);
      }
    }
  };
  // sorts the elements
  void sort() {
    for (auto it = begin(); it != end(); ++it) {
      for (auto jt = begin(); jt != --end(); ++jt) {
        auto temp_jt = ++jt;
        --jt;
        if (*jt > *temp_jt) {
          value_type temp = *jt;
          *jt = *temp_jt;
          *temp_jt = temp;
        }
      }
    }
  };

  // доп. функции
  const_iterator cbegin() const { return const_iterator(first_node->next); };
  const_iterator cend() const { return const_iterator(last_node); };

  // bonus part
  // Inserts new elements into the container directly before pos.
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args) {
    iterator it = begin();
    while (pos != it) {
      ++it;
    }
    for (const value_type &value : {args...}) {
      insert(it, value);
    }
    return it;
  };
  // Appends new elements to the end of the container.
  template <typename... Args>
  void insert_many_back(Args &&...args) {
    insert_many(cend(), args...);
  };
  // Appends new elements to the top of the container.
  template <typename... Args>
  void insert_many_front(Args &&...args) {
    insert_many(cbegin(), args...);
  };
};
}  // namespace s21

#endif
