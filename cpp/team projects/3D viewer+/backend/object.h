#ifndef __S21_OBJECT_H__
#define __S21_OBJECT_H__

#include <math.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "s21_matrix.h"

#define MAX_VERTEX 1000000  // миллион

namespace s21 {

class Object {
 private:
  int CountNumber(std::string& line);
  void ParseVertex(std::string& line, int row);
  void ParseFace(std::string& line);

 public:
  S21Matrix vertices;  // значение вершин (xyz)
  std::vector<std::vector<unsigned int>*> faces;  // значение face
  unsigned int amount_vertex;  // количество координат вершин
  unsigned int number_vertex;  // количество вершин
  unsigned int number_face;    // количество ребер
  unsigned int amount_face;    // итоговое количество face

  Object();
  bool readObject(const std::string path);
  ~Object();

  /// @brief Центрирует объект в 0, 0, 0
  void center();

  /// @brief Нормализует объект в рамку 1, 1, 1
  void normalize();

  /// @brief Масштабирует объект
  /// @param scope - коэфицент увеличения
  void scale(double scope = 1);

  /// @brief Возвращает длину максимального полигона
  /// @return Длина макс. полигона для массива вершин
  unsigned int getMaxFaceSize() const;

  void rotateX(double angleX);
  void rotateY(double angleY);
  void rotateZ(double angleZ);

  void translate(double x, double y, double z);
};  // class object

};  // namespace s21

#endif  // __S21_OBJECT_H__