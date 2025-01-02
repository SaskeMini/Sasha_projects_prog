#include <gtest/gtest.h>

#include <list>

#include "../s21_containers.h"

TEST(constructors, 1) {
  s21::list<int> l21{};
  std::list<int> l{};
  EXPECT_EQ(l21.empty(), l.empty());
}
TEST(constructors, 2) {
  s21::list<double> l21(5);
  std::list<double> l(5);
  EXPECT_EQ(l21.size(), l.size());
  auto it21 = l21.begin();
  for (auto it = l.begin(); it != l.end(); ++it, ++it21) {
    EXPECT_EQ(*it21, *it);
  }
}
TEST(constructors, 3) {
  s21::list<std::string> l21({"aaaa", "baaa", "CAA", "daa"});
  std::list<std::string> l({"aaaa", "baaa", "CAA", "daa"});
  EXPECT_EQ(l21.size(), l.size());
  auto it21 = l21.begin();
  for (auto it = l.begin(); it != l.end(); ++it, ++it21) {
    EXPECT_EQ(*it21, *it);
  }
}
TEST(constructors, 4) {
  s21::list<char> m21({'a', 'b', 'c'});
  std::list<char> m({'a', 'b', 'c'});
  s21::list<char> l21(m21);
  std::list<char> l(m);
  EXPECT_EQ(l21.size(), l.size());
  auto it21 = l21.begin();
  for (auto it = l.begin(); it != l.end(); ++it, ++it21) {
    EXPECT_EQ(*it21, *it);
  }
  EXPECT_EQ(m21.size(), m.size());
  it21 = m21.begin();
  for (auto it = m.begin(); it != m.end(); ++it, ++it21) {
    EXPECT_EQ(*it21, *it);
  }
}
TEST(constructors, 5) {
  s21::list<std::string> m21({"aaaa", "baaa", "CAA", "daa"});
  std::list<std::string> m({"aaaa", "baaa", "CAA", "daa"});
  s21::list<std::string> l21(std::move(m21));
  std::list<std::string> l(std::move(m));
  EXPECT_EQ(l21.size(), l.size());
  auto it21 = l21.begin();
  for (auto it = l.begin(); it != l.end(); ++it, ++it21) {
    EXPECT_EQ(*it21, *it);
  }
  EXPECT_EQ(m21.empty(), m.empty());
}
TEST(constructors, 6) {
  s21::list<char> m21({'a', 'b', 'c', 'd', 'e', 'f'});
  std::list<char> m({'a', 'b', 'c', 'd', 'e', 'f'});
  s21::list<char> l21 = std::move(m21);
  std::list<char> l = std::move(m);
  EXPECT_EQ(l21.size(), l.size());
  auto it21 = l21.begin();
  for (auto it = l.begin(); it != l.end(); ++it, ++it21) {
    EXPECT_EQ(*it21, *it);
    EXPECT_EQ(m21.empty(), m.empty());
  }
}
TEST(constructors, 7) {
  s21::list<int> m21{};
  std::list<int> m{};
  s21::list<int> l21(std::move(m21));
  std::list<int> l(std::move(m));
  EXPECT_EQ(l21.size(), l.size());
  EXPECT_EQ(l21.empty(), l.empty());
  EXPECT_EQ(m21.empty(), m.empty());
}
TEST(size_func, 1) {
  s21::list<std::string> l21({"aaaa", "baaa", "CAA", "daa"});
  std::list<std::string> l({"aaaa", "baaa", "CAA", "daa"});
  EXPECT_EQ(l21.empty(), l.empty());
  EXPECT_EQ(l21.size(), l.size());
  EXPECT_EQ(l21.max_size(), l.max_size());
  EXPECT_EQ(l21.front(), l.front());
  EXPECT_EQ(l21.back(), l.back());
  EXPECT_EQ(*l21.begin(), *l.begin());
  EXPECT_EQ(*(--l21.end()), *(--l.end()));
}
TEST(size_func, 2) {
  s21::list<int> l21{};
  std::list<int> l{};
  EXPECT_EQ(l21.empty(), l.empty());
  EXPECT_EQ(l21.size(), l.size());
  EXPECT_EQ(l21.max_size(), l.max_size());
  EXPECT_EQ(l21.front(), l.front());
  EXPECT_EQ(l21.back(), l.back());
  EXPECT_EQ(*l21.begin(), *l.begin());
  EXPECT_EQ(*(--l21.end()), *(--l.end()));
}
TEST(push_pop_func, 1) {
  s21::list<char> l21({'a', 'b', 'c', 'd', 'e', 'f'});
  std::list<char> l({'a', 'b', 'c', 'd', 'e', 'f'});
  auto i21 = l21.begin();
  i21++;
  i21++;
  l21.insert(i21++, 'i');
  l21.push_front('f');
  l21.push_back('b');
  auto i = l.begin();
  i++;
  i++;
  l.insert(i++, 'i');
  l.push_front('f');
  l.push_back('b');
  EXPECT_EQ(l21.size(), l.size());
  EXPECT_EQ(*i21, *i);
  auto it21 = l21.begin();
  for (auto it = l.begin(); it != l.end(); ++it, ++it21) {
    EXPECT_EQ(*it21, *it);
  }
  l21.erase(i21);
  l21.pop_front();
  l21.pop_back();
  l.erase(i);
  l.pop_front();
  l.pop_back();
  it21 = l21.begin();
  for (auto it = l.begin(); it != l.end(); ++it, ++it21) {
    EXPECT_EQ(*it21, *it);
  }
  l21.clear();
  l.clear();
  EXPECT_EQ(l21.empty(), l.empty());
}
TEST(push_pop_func, 2) {
  s21::list<double> l21({15.6, 8.01});
  std::list<double> l({15.6, 8.01});
  auto i21 = l21.begin();
  l21.insert(i21, 12.8889);
  l21.push_front(1.693);
  l21.push_back(1.0 / 0.0);
  auto i = l.begin();
  l.insert(i, 12.8889);
  l.push_front(1.693);
  l.push_back(1.0 / 0.0);
  EXPECT_EQ(l21.size(), l.size());
  EXPECT_EQ(*i21, *i);
  auto it21 = l21.begin();
  for (auto it = l.begin(); it != l.end(); ++it, ++it21) {
    EXPECT_EQ(*it21, *it);
  }
  l21.pop_front();
  l21.pop_back();
  l21.erase(i21);
  l.pop_front();
  l.pop_back();
  l.erase(i);
  it21 = l21.begin();
  for (auto it = l.begin(); it != l.end(); ++it, ++it21) {
    EXPECT_EQ(*it21, *it);
  }
  l21.clear();
  l.clear();
  EXPECT_EQ(l21.empty(), l.empty());
}
TEST(other_modif_func, 1) {
  s21::list<double> m21({1899.8952, 0.0008, 15.6});
  std::list<double> m({1899.8952, 0.0008, 15.6});
  s21::list<double> l21({15.6, 8.01});
  std::list<double> l({15.6, 8.01});
  l21.swap(m21);
  l.swap(m);
  EXPECT_EQ(l21.size(), l.size());
  auto it21 = l21.begin();
  for (auto it = l.begin(); it != l.end(); ++it, ++it21) {
    EXPECT_EQ(*it21, *it);
  }
  EXPECT_EQ(m21.size(), m.size());
  it21 = m21.begin();
  for (auto it = m.begin(); it != m.end(); ++it, ++it21) {
    EXPECT_EQ(*it21, *it);
  }
}
TEST(other_modif_func, 2) {
  s21::list<double> m21({1899.8952, 0.0008, 15.6});
  std::list<double> m({1899.8952, 0.0008, 15.6});
  s21::list<double> l21{};
  std::list<double> l{};
  l21.swap(m21);
  l.swap(m);
  EXPECT_EQ(l21.size(), l.size());
  auto it21 = l21.begin();
  for (auto it = l.begin(); it != l.end(); ++it, ++it21) {
    EXPECT_EQ(*it21, *it);
  }
  EXPECT_EQ(m21.empty(), m.empty());
}
TEST(other_modif_func, 3) {
  s21::list<char> m21({'c', 'a', 'b', 'f', 'd', 'e'});
  std::list<char> m({'c', 'a', 'b', 'f', 'd', 'e'});
  s21::list<char> l21({'k', 'a', 'l'});
  std::list<char> l({'k', 'a', 'l'});
  l21.sort();
  l.sort();
  EXPECT_EQ(l21.size(), l.size());
  auto it21 = l21.begin();
  for (auto it = l.begin(); it != l.end(); ++it, ++it21) {
    EXPECT_EQ(*it21, *it);
  }
  m21.sort();
  m.sort();
  EXPECT_EQ(m21.size(), m.size());
  it21 = m21.begin();
  for (auto it = m.begin(); it != m.end(); ++it, ++it21) {
    EXPECT_EQ(*it21, *it);
  }
  l21.merge(m21);
  l.merge(m);
  EXPECT_EQ(l21.size(), l.size());
  it21 = l21.begin();
  for (auto it = l.begin(); it != l.end(); ++it, ++it21) {
    EXPECT_EQ(*it21, *it);
  }
  EXPECT_EQ(m21.empty(), m.empty());
}
TEST(other_modif_func, 4) {
  s21::list<std::string> m21{};
  std::list<std::string> m{};
  s21::list<std::string> l21({"aaaa", "baaa", "CAA", "daa"});
  std::list<std::string> l({"aaaa", "baaa", "CAA", "daa"});
  l21.sort();
  l.sort();
  EXPECT_EQ(l21.size(), l.size());
  auto it21 = l21.begin();
  for (auto it = l.begin(); it != l.end(); ++it, ++it21) {
    EXPECT_EQ(*it21, *it);
  }
  l21.merge(m21);
  l.merge(m);
  EXPECT_EQ(l21.size(), l.size());
  it21 = l21.begin();
  for (auto it = l.begin(); it != l.end(); ++it, ++it21) {
    EXPECT_EQ(*it21, *it);
  }
  EXPECT_EQ(m21.empty(), m.empty());
}
TEST(other_modif_func, 5) {
  s21::list<int> m21({5, 0, 9, 12, 7, 9});
  std::list<int> m{{5, 0, 9, 12, 7, 9}};
  s21::list<int> l21({13, 8, 8, 8, 8, 8, 8});
  std::list<int> l{{13, 8, 8, 8, 8, 8, 8}};
  auto i21 = l21.end();
  --i21;
  --i21;
  l21.splice(i21, m21);
  auto i = l.end();
  --i;
  --i;
  l.splice(i, m);
  EXPECT_EQ(l21.size(), l.size());
  auto it21 = l21.begin();
  for (auto it = l.begin(); it != l.end(); ++it, ++it21) {
    EXPECT_EQ(*it21, *it);
  }
  l21.unique();
  l.unique();
  EXPECT_EQ(l21.size(), l.size());
  it21 = l21.begin();
  for (auto it = l.begin(); it != l.end(); ++it, ++it21) {
    EXPECT_EQ(*it21, *it);
  }
  EXPECT_EQ(m21.empty(), m.empty());
}
TEST(other_modif_func, 6) {
  s21::list<int> m21{};
  std::list<int> m{};
  s21::list<int> l21({13, 8, 8, 8, 8, 8, 8});
  std::list<int> l{{13, 8, 8, 8, 8, 8, 8}};
  auto i21 = l21.begin();
  ++i21;
  ++i21;
  l21.splice(i21--, m21);
  auto i = l.begin();
  ++i;
  ++i;
  l.splice(i--, m);
  EXPECT_EQ(l21.size(), l.size());
  auto it21 = l21.begin();
  for (auto it = l.begin(); it != l.end(); ++it, ++it21) {
    EXPECT_EQ(*it21, *it);
  }
  l21.reverse();
  l.reverse();
  EXPECT_EQ(l21.size(), l.size());
  it21 = l21.begin();
  for (auto it = l.begin(); it != l.end(); ++it, ++it21) {
    EXPECT_EQ(*it21, *it);
  }
  EXPECT_EQ(m21.empty(), m.empty());
}
TEST(bonus_func, 1) {
  s21::list<char> l21({'a', 'b', 'c', 'd', 'e', 'f'});
  std::list<char> l(
      {'f', 'p', 'y', 'a', 'b', 'i', 'k', 's', 'c', 'd', 'e', 'f', 'b', 'i'});
  auto i21 = l21.begin();
  ++i21;
  ++i21;
  l21.insert_many(i21, 'i', 'k', 's');
  l21.insert_many_front('f', 'p', 'y');
  l21.insert_many_back('b', 'i');
  auto i = l.begin();
  ++i;
  ++i;
  EXPECT_EQ(l21.size(), l.size());
  auto it21 = l21.begin();
  for (auto it = l.begin(); it != l.end(); ++it, ++it21) {
    EXPECT_EQ(*it21, *it);
  }
}
TEST(bonus_func, 2) {
  s21::list<double> l21({15.6, 8.01});
  std::list<double> l({1.693, 9.6389, 1896573.9237, 0.8963, 12.8889, 15.6, 8.01,
                       1.0 / 0.0, -1.0 / 0.0});
  auto i21 = l21.begin();
  l21.insert_many(i21, 0.8963, 12.8889);
  l21.insert_many_front(1.693, 9.6389, 1896573.9237);
  l21.insert_many_back(1.0 / 0.0, -1.0 / 0.0);
  EXPECT_EQ(l21.size(), l.size());
  auto it21 = l21.begin();
  for (auto it = l.begin(); it != l.end(); ++it, ++it21) {
    EXPECT_EQ(*it21, *it);
  }
}