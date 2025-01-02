#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../s21_containers.h"

TEST(queue, queue_construct) {
  s21::queue<int> ss = {10, 3};
  s21::queue<int> s;
  s = std::move(ss);
  ss.push(4);
  ss.swap(s);
  ASSERT_EQ(ss.back(), 3);
  ASSERT_EQ(s.back(), 4);
  s21::queue<int> xz = std::move(ss);
  ASSERT_EQ(xz.front(), 10);
  ASSERT_EQ(xz.back(), 3);
  ASSERT_TRUE(ss.empty());
  s.pop();
  ASSERT_EQ(s.size(), 2);
  s.pop();
  s.pop();
  ASSERT_TRUE(s.empty());
  s21::queue<char> z;
  s21::queue<char> o = std::move(z);
  s21::queue<char> v;
  o.push('a');
  ASSERT_EQ(o.back(), 'a');
  ASSERT_ANY_THROW(v.pop());
  ASSERT_ANY_THROW(v.front());
  ASSERT_ANY_THROW(v.back());
  o.insert_many_back('1', '2', '3');
  ASSERT_EQ(o.back(), '3');
}