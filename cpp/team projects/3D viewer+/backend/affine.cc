#include "object.h"

namespace s21 {

void Object::rotateX(double angleX) {
  for (unsigned int i = 0; i < number_vertex; i++) {
    double t_y, t_z;
    t_y = vertices(i, 1), t_z = vertices(i, 2);
    vertices(i, 1) = cos(angleX) * t_y - sin(angleX) * t_z;
    vertices(i, 2) = sin(angleX) * t_y + cos(angleX) * t_z;
  }
}

void Object::rotateY(double angleY) {
  for (unsigned int i = 0; i < number_vertex; i++) {
    double t_x, t_z;
    t_x = vertices(i, 0), t_z = vertices(i, 2);
    vertices(i, 0) = cos(angleY) * t_x + sin(angleY) * t_z;
    vertices(i, 2) = -sin(angleY) * t_x + cos(angleY) * t_z;
  }
}

void Object::rotateZ(double angleZ) {
  for (unsigned int i = 0; i < number_vertex; i++) {
    double t_x, t_y;
    t_x = vertices(i, 0), t_y = vertices(i, 1);
    vertices(i, 0) = cos(angleZ) * t_x - sin(angleZ) * t_y;
    vertices(i, 1) = sin(angleZ) * t_x + cos(angleZ) * t_y;
  }
}

void Object::translate(double x, double y, double z) {
  for (unsigned int i = 0; i < number_vertex; i++) {
    vertices(i, 0) += x;
    vertices(i, 1) += y;
    vertices(i, 2) += z;
  }
}
}  // namespace s21