#ifndef __S21_VIEWER_TEST_H__
#define __S21_VIEWER_TEST_H__

#include <gtest/gtest.h>

#include "../backend/model.h"

using namespace s21;

class ModelTest : public ::testing::Test {
 protected:
  void SetUp() override {
    model = Model();
    model.setObject("obj/cube.obj");
  }

  Model model;
};

#endif