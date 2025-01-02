#include <gtest/gtest.h>

#include <vector>

#include "../s21_containers.h"

TEST(default_constructor_vector, 1) {
  s21::vector<int> my_vector{};
  std::vector<int> original{};
  EXPECT_EQ(my_vector.empty(), original.empty());
  EXPECT_EQ(my_vector.size(), original.size());
  EXPECT_EQ(my_vector.capacity(), original.capacity());
  my_vector.push_back(10);
  original.push_back(10);
  EXPECT_EQ(my_vector.empty(), original.empty());
  EXPECT_EQ(my_vector.size(), original.size());
  EXPECT_EQ(my_vector.capacity(), original.capacity());
  my_vector.push_back(30);
  original.push_back(30);
  EXPECT_EQ(my_vector.empty(), original.empty());
  EXPECT_EQ(my_vector.size(), original.size());
  EXPECT_EQ(my_vector.capacity(), original.capacity());
}
TEST(constructors_vector, 2) {
  s21::vector<double> my_vector(5);
  std::vector<double> original(5);
  EXPECT_EQ(my_vector.size(), original.size());
  EXPECT_EQ(my_vector.capacity(), original.capacity());
  my_vector.push_back(10.2);
  original.push_back(10.2);
  my_vector.push_back(11.2);
  original.push_back(11.2);
  EXPECT_EQ(my_vector.size(), original.size());
  EXPECT_EQ(my_vector.capacity(), original.capacity());
  my_vector.pop_back();
  original.pop_back();
  EXPECT_EQ(my_vector.size(), original.size());
  EXPECT_EQ(my_vector.capacity(), original.capacity());
}

TEST(initializer_list_constructor_vector, 1) {
  s21::vector<double> my_vector{1.1, 2.2, 3.3, 4.4, 5.5};
  std::vector<double> original{1.1, 2.2, 3.3, 4.4, 5.5};
  EXPECT_EQ(my_vector.size(), original.size());
  EXPECT_EQ(my_vector.capacity(), original.capacity());
}

TEST(copy_constructor_vector, 1) {
  s21::vector<int> my_vector = {1, 2, 3};
  std::vector<int> original = {1, 2, 3};
  s21::vector<int> my_vector_2(my_vector);
  std::vector<int> original_2(original);
  EXPECT_EQ(my_vector_2.capacity(), original_2.capacity());
  EXPECT_EQ(my_vector_2.size(), original_2.size());
}

TEST(move_constructor_vector, 1) {
  s21::vector<int> my_vector(0);
  s21::vector<int> my_vector_2(std::move(my_vector));
  std::vector<int> original(0);
  std::vector<int> original_2(std::move(original));
  EXPECT_EQ(my_vector_2.capacity(), original_2.capacity());
  EXPECT_EQ(my_vector_2.size(), original_2.size());
}

TEST(at_vector, 1) {
  s21::vector<int> my_vector = {1, 2, 3};
  ASSERT_EQ(my_vector.at(1), 2);
  ASSERT_THROW(my_vector.at(5), std::out_of_range);
}

TEST(operator_brackets_vector, 1) {
  s21::vector<int> my_vector = {1, 2, 3};
  ASSERT_EQ(my_vector[1], 2);
}

TEST(front_vector, 1) {
  s21::vector<int> my_vector = {1, 2, 3};
  ASSERT_EQ(my_vector.front(), 1);
}

TEST(back_vector, 1) {
  s21::vector<int> my_vector = {1, 2, 3};
  ASSERT_EQ(my_vector.back(), 3);
}

TEST(reserve_vector, 1) {
  std::vector<int> original{};
  s21::vector<int> my_vector{};
  original.reserve(10);
  my_vector.reserve(10);

  ASSERT_EQ(original.capacity(), 10u);
  ASSERT_EQ(my_vector.capacity(), 10u);
  ASSERT_EQ(original.size(), 0u);
  ASSERT_EQ(my_vector.size(), 0u);
}

TEST(move_assignment_vector, 1) {
  s21::vector<int> origin({1, 2, 3, 4});
  s21::vector<int> vec(15);

  vec = std::move(origin);

  int* data = vec.data();
  int* ordata = origin.data();

  EXPECT_NE(data, nullptr);
  EXPECT_EQ(ordata, nullptr);

  EXPECT_EQ(4U, vec.size());

  for (size_t i = 0; i < vec.size(); ++i) {
    unsigned long temp = data[i];
    EXPECT_EQ(static_cast<unsigned long>(i + 1), temp);
  }
}

TEST(reserve_vector, 2) {
  std::vector<int> original{};
  s21::vector<int> my_vector{};

  original.reserve(5);
  my_vector.reserve(5);
  EXPECT_EQ(my_vector.capacity(), original.capacity());
  EXPECT_EQ(my_vector.size(), original.size());
}

TEST(empty_vector, 1) {
  s21::vector<long double> vector1 = {1.1, -222.22, 0.123};
  EXPECT_FALSE(vector1.empty());
}

TEST(empty_vector, 2) {
  s21::vector<long double> vector1;
  EXPECT_TRUE(vector1.empty());
}

TEST(shrink_to_fit_vector, 1) {
  s21::vector<int> my_vector = {1, 2, 3};
  std::vector<int> original = {1, 2, 3};
  my_vector.reserve(50);
  original.reserve(50);
  my_vector.shrink_to_fit();
  original.shrink_to_fit();
  EXPECT_EQ(my_vector.size(), original.size());
  EXPECT_EQ(my_vector.capacity(), original.capacity());
}

TEST(shrink_to_fit_vector, 2) {
  s21::vector<int> my_vector = {1, 2, 3, 4, 5, 6};
  std::vector<int> original = {1, 2, 3, 4, 5, 6};
  my_vector.reserve(1);
  original.reserve(1);
  my_vector.shrink_to_fit();
  original.shrink_to_fit();
  EXPECT_EQ(my_vector.size(), original.size());
  EXPECT_EQ(my_vector.capacity(), original.capacity());
}

TEST(clear_vector, 1) {
  s21::vector<int> my_vector = {1, 2, 3, 4, 5, 6};
  std::vector<int> original = {1, 2, 3, 4, 5, 6};
  my_vector.clear();
  original.clear();
  EXPECT_EQ(my_vector.size(), original.size());
  EXPECT_EQ(my_vector.capacity(), original.capacity());
}

TEST(erase_vector, 1) {
  s21::vector<int> my_vector = {1, 2, 3, 4, 5, 6};
  std::vector<int> original = {1, 2, 3, 4, 5, 6};
  my_vector.erase(my_vector.end() - 1);
  original.erase(original.end() - 1);
  EXPECT_EQ(my_vector.size(), original.size());
  EXPECT_EQ(my_vector.capacity(), original.capacity());
}

TEST(erase_vector, 2) {
  s21::vector<int> my_vector = {1, 2, 3, 4, 5, 6};
  std::vector<int> original = {1, 2, 3, 4, 5, 6};
  my_vector.erase(my_vector.begin());
  original.erase(original.begin());
  EXPECT_EQ(my_vector.size(), original.size());
  EXPECT_EQ(my_vector.capacity(), original.capacity());
}

TEST(test_vector, swap_1) {
  s21::vector<int> my_vector = {1, 2, 3, 4, 5, 6};
  s21::vector<int> my_vector_2 = {1, 2, 3};
  std::vector<int> original = {1, 2, 3, 4, 5, 6};
  std::vector<int> original_2 = {1, 2, 3};
  my_vector.swap(my_vector_2);
  original.swap(original_2);
  EXPECT_EQ(my_vector.size(), original.size());
  EXPECT_EQ(my_vector.capacity(), original.capacity());
  EXPECT_EQ(my_vector_2.size(), original_2.size());
  EXPECT_EQ(my_vector_2.capacity(), original_2.capacity());
}

TEST(test_vector, insert_many_1) {
  s21::vector<int> my_vector = {1, 2, 3, 4, 5, 6};
  my_vector.insert_many(my_vector.begin(), -1);
  EXPECT_EQ(my_vector[0], -1);
  EXPECT_EQ(my_vector[1], 1);
  EXPECT_EQ(my_vector.size(), (size_t)7);
}

TEST(test_vector, insert_many_2) {
  s21::vector<int> my_vector = {1, 2, 3, 4, 5, 6};
  my_vector.insert_many(my_vector.begin(), -2, -1);
  EXPECT_EQ(my_vector[0], -2);
  EXPECT_EQ(my_vector[1], -1);
  EXPECT_EQ(my_vector[2], 1);
  EXPECT_EQ(my_vector.size(), (size_t)8);
}

TEST(testVector, insert_many_Back_1) {
  s21::vector<int> my_vector = {1, 2, 3, 4, 5, 6};
  s21::vector<int> my_vector_2 = {1, 2, 3, 4, 5, 6, 6, 5, 4, 3, 2, 1};
  std::vector<int> original = {1, 2, 3, 4, 5, 6, 6, 5, 4, 3, 2, 1};
  my_vector.insert_many_back(6, 5, 4, 3, 2, 1);
  EXPECT_EQ(my_vector.size(), original.size());
  EXPECT_EQ(my_vector.capacity(), original.capacity());
}
