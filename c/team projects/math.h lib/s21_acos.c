#include "s21_math.h"

long double s21_acos(double x) {
  long double sun = 0;
  if (s21_is_inf(x)) {
    sun = s21_NAN;
  } else if (s21_is_nan(x)) {
    sun = s21_NAN;
  } else if (x < -1.0 || x > 1.0) {
    sun = S21_NAN;
  } else if (x == 1.0) {
    sun = 0.0;
  } else if (x == -1.0) {
    sun = S21_PI;
  } else {
    sun = S21_PI / 2 - s21_asin(x);
  }

  return sun;
}
