#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../s21_containers.h"

TEST(stack, stack_construct) {
  s21::stack<int> ss = {10, 3};
  s21::stack<int> s;
  s = std::move(ss);
  ss.push(4);
  ss.swap(s);
  ASSERT_EQ(ss.top(), 3);
  ASSERT_EQ(s.top(), 4);
  s21::stack<int> xz = std::move(ss);
  ASSERT_EQ(xz.top(), 3);
  ASSERT_TRUE(ss.empty());
  s.pop();
  ASSERT_EQ(s.size(), 2);
  s.pop();
  s.pop();
  ASSERT_TRUE(s.empty());
  s21::stack<char> z;
  s21::stack<char> o = std::move(z);
  s21::stack<char> v;
  o.push('a');
  ASSERT_EQ(o.top(), 'a');
  ASSERT_ANY_THROW(v.pop());
  ASSERT_ANY_THROW(v.top());
  o.insert_many_back('1', '2', '3');
  ASSERT_EQ(o.top(), '3');
}