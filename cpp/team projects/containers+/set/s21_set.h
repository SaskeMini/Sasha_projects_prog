#include <initializer_list>
#include <limits>
#include <vector>

#include "../tree/tree.h"

namespace s21 {
template <typename Key>
class set : public tree<Key, Key> {
 public:
  using key_type = Key;
  using size_type = size_t;
  using value_type = Key;
  using reference = Key &;
  using const_reference = const Key &;
  using iterator = typename tree<Key, Key>::iterator;
  using const_iterator = typename tree<Key, Key>::iterator;

  set()
      : tree<Key, Key>(){};  //     конструктор по умолчанию, создает пустое
                             //     множество
  set(std::initializer_list<value_type> const
          &items);  //  конструктор списка инициализаторов, создает множество,
                    //  инициализированный с использованием
                    //  std::initializer_list<T>  |
  set(const set &s) : tree<Key, Key>(s){};  // конструктор копирования
  set(set &&s) noexcept : tree<Key, Key>(std::move(s)){};
  ;  // конструктор перемещения|

  size_type max_size() {
    return (std::numeric_limits<size_type>::max() / sizeof(Key) / 2);
  };
  // оператор перемещения
  set &operator=(set &&s) noexcept;
  set &operator=(const set &s);
  ~set() = default;

  std::pair<iterator, bool> insert(const value_type &value) {
    return tree<Key, Key>::insert(
        std::make_pair(value, value));  // Вставка с дублированием ключа
  };  // вставляет узел и возвращает итератор туда, где
      //  элемент находится в контейнере, а значение bool указывает, имела ли
      //  место вставка.

  void clear() {
    for (auto it = set::begin(); it != set::end();
         ++it) {  // перебор всех элементов

      set::erase(it);
    }
  }

  iterator find(const Key &key) {
    return tree<Key, Key>::find(key);
  };  // находит элемент с определенным ключомy

  iterator operator++(int) { return tree<Key, Key>::iterator::operator++; };

  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    std::vector<std::pair<typename set<Key>::iterator, bool>> xz;
    for (const auto &arg : {args...}) {
      xz.push_back(insert(arg));
    }
    return xz;
  };
};
};  // namespace s21

//    конструктор по умолчанию, создает пустое множество
namespace s21 {
//  конструктор списка инициализаторов, создает множество, инициализированный с
//  использованием std::initializer_list<T>  |
template <typename Key>
set<Key>::set(std::initializer_list<value_type> const &items) {
  for (auto i = items.begin(); i != items.end(); ++i) {
    this->insert(*i);
  }
}

}  // namespace s21