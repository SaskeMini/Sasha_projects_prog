#include "s21_math.h"

long double s21_asin(double x) {
  long double sun = 0.0;
  if (x < -1.0 || x > 1.0) {
    sun = S21_NAN;
  } else if (x == 1.0) {
    sun = S21_PI / 2;
  } else if (x == -1.0) {
    sun = -S21_PI / 2;
  } else if (x == 0) {
    sun = 0;
  } else {
    sun = s21_atan(x / s21_sqrt(1.0 - x * x));
  }

  return sun;
}
