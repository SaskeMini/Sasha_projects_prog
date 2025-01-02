#include "s21_math.h"
long double s21_pow(double x, double exp) {
  long double sun = 1;
  if (exp == 0)
    sun = 1;
  else if ((s21_is_nan(x) && exp != 0) ||
           (x < 0 && exp < 0 && exp - s21_floor(exp) != 0))
    sun = s21_NAN;
  else if (x == 1)
    sun = 1;
  else if (x == -1 && exp == S21_INF)
    sun = 1.0;
  else if ((long int)exp == exp) {
    if (exp > 0)
      for (; exp >= 1; exp--) sun *= x;
    else
      for (; exp <= -1; exp++) sun /= x;
  } else {
    sun = s21_exp(exp * s21_log(x));
  }
  return sun;
}