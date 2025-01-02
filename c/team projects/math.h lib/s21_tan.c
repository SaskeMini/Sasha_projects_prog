#include "s21_math.h"

long double s21_tan(double x) {
  long double sun;
  if (s21_is_inf(x)) {
    sun = s21_NAN;
  } else if (s21_is_nan(x)) {
    sun = s21_NAN;
  } else {
    sun = s21_sin(x) / s21_cos(x);
  }
  return sun;
}
