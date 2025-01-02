#include "test.h"

// Тест для метода setObject
TEST_F(ModelTest, SetObject_Success) {
  std::string testFilePath = "obj/cube.obj";
  bool result = model.setObject(testFilePath);
  EXPECT_TRUE(result);
  EXPECT_EQ(model.getFilePath(), testFilePath);
  EXPECT_EQ(model.getNumberVertex(), 8);
  EXPECT_EQ(model.getNumberFace(), 12);
  EXPECT_EQ(model.getMaxFaceSize(), 9);
}

TEST_F(ModelTest, SetObject_Failure) {
  std::string invalidFilePath = "nonexistent_file.obj";
  bool result = model.setObject(invalidFilePath);
  EXPECT_FALSE(result);
  EXPECT_EQ(model.getFilePath(), invalidFilePath);
  EXPECT_EQ(model.getNumberVertex(), 0);
  EXPECT_EQ(model.getNumberFace(), 0);
  EXPECT_EQ(model.getMaxFaceSize(), 0);
}

// Тест для метода transform
TEST_F(ModelTest, Transform_TranslateX) {
  model.transform(0, 1.0);
  std::vector<std::vector<double>> expected_src = {
      {2.0, -1.0, -1.0}, {2.0, -1.0, 1.0}, {0.0, -1.0, 1.0}, {0.0, -1.0, -1.0},
      {2.0, 1.0, -1.0},  {2.0, 1.0, 1.0},  {0.0, 1.0, 1.0},  {0.0, 1.0, -1.0}};
  S21Matrix expectedVertices(8, 3);
  for (int i = 0; i < 8; ++i)
    for (int j = 0; j < 3; ++j) expectedVertices(i, j) = expected_src[i][j];
  EXPECT_TRUE(model.getObject().vertices == expectedVertices);
}

TEST_F(ModelTest, Transform_TranslateY) {
  model.transform(1, 2.0);
  std::vector<std::vector<double>> expected_src = {
      {1.0, 1.0, -1.0}, {1.0, 1.0, 1.0}, {-1.0, 1.0, 1.0}, {-1.0, 1.0, -1.0},
      {1.0, 3.0, -1.0}, {1.0, 3.0, 1.0}, {-1.0, 3.0, 1.0}, {-1.0, 3.0, -1.0}};
  S21Matrix expectedVertices(8, 3);
  for (int i = 0; i < 8; ++i)
    for (int j = 0; j < 3; ++j) expectedVertices(i, j) = expected_src[i][j];
  EXPECT_TRUE(model.getObject().vertices == expectedVertices);
}

TEST_F(ModelTest, Transform_TranslateZ) {
  model.transform(2, 3.0);
  std::vector<std::vector<double>> expected_src = {
      {1.0, -1.0, 2.0}, {1.0, -1.0, 4.0}, {-1.0, -1.0, 4.0}, {-1.0, -1.0, 2.0},
      {1.0, 1.0, 2.0},  {1.0, 1.0, 4.0},  {-1.0, 1.0, 4.0},  {-1.0, 1.0, 2.0}};
  S21Matrix expectedVertices(8, 3);
  for (int i = 0; i < 8; ++i)
    for (int j = 0; j < 3; ++j) expectedVertices(i, j) = expected_src[i][j];
  EXPECT_TRUE(model.getObject().vertices == expectedVertices);
}

TEST_F(ModelTest, Transform_Scale) {
  model.transform(3, 2.0);
  std::vector<std::vector<double>> expected_src = {
      {2.0, -2.0, -2.0},  {2.0, -2.0, 2.0}, {-2.0, -2.0, 2.0},
      {-2.0, -2.0, -2.0}, {2.0, 2.0, -2.0}, {2.0, 2.0, 2.0},
      {-2.0, 2.0, 2.0},   {-2.0, 2.0, -2.0}};
  S21Matrix expectedVertices(8, 3);
  for (int i = 0; i < 8; ++i)
    for (int j = 0; j < 3; ++j) expectedVertices(i, j) = expected_src[i][j];
  EXPECT_TRUE(model.getObject().vertices == expectedVertices);
}

TEST_F(ModelTest, Transform_RotateX) {
  model.transform(4, M_PI / 2);
  std::vector<std::vector<double>> expected_src = {
      {1, 1, -1}, {1, -1, -1}, {-1, -1, -1}, {-1, 1, -1},
      {1, 1, 1},  {1, -1, 1},  {-1, -1, 1},  {-1, 1, 1}};
  S21Matrix expectedVertices(8, 3);
  for (int i = 0; i < 8; ++i)
    for (int j = 0; j < 3; ++j) expectedVertices(i, j) = expected_src[i][j];
  EXPECT_TRUE(model.getObject().vertices == expectedVertices);
}

TEST_F(ModelTest, Transform_RotateY) {
  model.transform(5, M_PI / 2);
  std::vector<std::vector<double>> expected_src = {
      {-1.0, -1.0, -1.0}, {1.0, -1.0, -1.0}, {1.0, -1.0, 1.0},
      {-1.0, -1.0, 1.0},  {-1, 1, -1},       {1, 1, -1},
      {1, 1, 1},          {-1, 1, 1}};
  S21Matrix expectedVertices(8, 3);
  for (int i = 0; i < 8; ++i)
    for (int j = 0; j < 3; ++j) expectedVertices(i, j) = expected_src[i][j];
  EXPECT_TRUE(model.getObject().vertices == expectedVertices);
}

TEST_F(ModelTest, Transform_RotateZ) {
  model.transform(6, M_PI / 2);
  std::vector<std::vector<double>> expected_src = {
      {1, 1, -1},  {1, 1, 1},  {1, -1, 1},  {1, -1, -1},
      {-1, 1, -1}, {-1, 1, 1}, {-1, -1, 1}, {-1, -1, -1}};
  S21Matrix expectedVertices(8, 3);
  for (int i = 0; i < 8; ++i)
    for (int j = 0; j < 3; ++j) expectedVertices(i, j) = expected_src[i][j];
  EXPECT_TRUE(model.getObject().vertices == expectedVertices);
}

// Тест для метода getFaceData
TEST_F(ModelTest, GetFaceData) {
  double face[9];
  model.getFaceData(0, face);
  std::vector<double> expectedFace = {1.0, -1.0, 1.0,  -1.0, -1.0,
                                      1.0, -1.0, -1.0, -1.0};
  bool result = true;
  for (int i = 0; i < 9; ++i)
    if (face[i] != expectedFace[i]) result = false;
  EXPECT_TRUE(result);
}

// Тест для метода toNormal
TEST_F(ModelTest, ToNormal) {
  S21Matrix expectedVertices = model.getObject().vertices;
  model.transform(3, 2.0);  // Масштабируем на 2
  model.toNormal();
  S21Matrix vertices = model.getObject().vertices;
  EXPECT_TRUE(vertices == expectedVertices);
  EXPECT_DOUBLE_EQ(model.getScale(), 1.0);
}

// Тест для метода getVertex
TEST_F(ModelTest, GetVertex) {
  EXPECT_DOUBLE_EQ(model.getVertex(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(model.getVertex(0, 1), -1.0);
  EXPECT_DOUBLE_EQ(model.getVertex(0, 2), -1.0);
  EXPECT_DOUBLE_EQ(model.getVertex(1, 0), 1.0);
  EXPECT_DOUBLE_EQ(model.getVertex(1, 1), -1.0);
  EXPECT_DOUBLE_EQ(model.getVertex(1, 2), 1.0);
}

// Тест для метода getFaceSize
TEST_F(ModelTest, GetFaceSize) {
  EXPECT_EQ(model.getFaceSize(0), 9);  // 3 вершины * 3 координаты
}