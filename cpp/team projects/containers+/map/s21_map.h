#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <vector>

#include "../tree/tree.h"

namespace s21 {
template <typename Key, typename T>
class map : public tree<Key, T> {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename tree<Key, T>::iterator;
  using const_iterator = typename tree<Key, T>::iterator;
  using size_type = size_t;

  map() : tree<Key, T>(){};

  map(std::initializer_list<value_type> const &items) {
    for (auto i = items.begin(); i != items.end(); ++i) {
      insert(*i);
    }
  };

  map(const map &other) : tree<Key, T>(other){};

  map(map &&other) noexcept : tree<Key, T>(std::move(other)){};

  map &operator=(map &&other) {
    tree<Key, T>::operator=(std::move(other));
    return *this;
  };

  ~map() = default;

  iterator begin() { return tree<Key, T>::begin(); };

  iterator end() { return tree<Key, T>::end(); };

  bool empty() { return tree<Key, T>::empty(); };

  size_type size() { return tree<Key, T>::size(); };

  size_type max_size() { return tree<Key, T>::size(); };

  T &at(const Key &key) {
    if (!contains(key)) {
      throw std::out_of_range("No");
    }
    auto xz = find(key);
    return xz.curr_node->data;
  };

  T &operator[](const Key &key) {
    if (!contains(key)) {
      insert(std::make_pair(key, T()));
      auto xz = find(key);
      return xz.curr_node->data;
    }
    auto xz = find(key);
    return xz.curr_node->data;
  };

  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    std::vector<std::pair<typename map<Key, T>::iterator, bool>> xz;
    for (const auto &arg : {args...}) {
      xz.push_back(insert(arg));
    }
    return xz;
  };

  void merge(map &other) { tree<Key, T>::merge(other); };

  void erase(iterator pos) { tree<Key, T>::erase(pos); };

  void swap(map &other) { tree<Key, T>::swap(other); };

  void clear() { tree<Key, T>::clear(); };

  std::pair<iterator, bool> insert(const value_type &value) {
    return tree<Key, T>::insert(std::make_pair(value.first, value.second));
  };

  std::pair<iterator, bool> insert(const Key &key, const T &obj) {
    return tree<Key, T>::insert(std::make_pair(key, obj));
  };

  std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj) {
    if (!contains(key)) {
      auto xz = find(key);
      erase(xz);
      auto xz_2 = insert(key, obj);
      xz_2.second = false;
      return xz_2;
    }
    return insert(key, obj);
  };

  bool contains(const Key &key) { return tree<Key, T>::contains(key); };

 private:
  iterator find(const Key &key) { return tree<Key, T>::find(key); };
};

}  // namespace s21
