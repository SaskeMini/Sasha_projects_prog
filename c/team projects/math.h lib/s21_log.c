#include "s21_math.h"

long double s21_log(double x) {
  long double XN = x - 1;
  long double sun = x - 1;
  if (x == 0) {
    sun = s21_MINUS_INF;
  } else if (x < 0 || s21_is_nan(x)) {
    sun = -S21_NAN;
  } else if (x == S21_INF) {
    sun = s21_PLUS_INF;
  } else if (x == 1.0) {
    sun = 0.0;
  } else if (x - 1 > -1 && x - 1 < 1 && x != 1) {
    long double ep = 1.0;
    for (int n = 2; ep > S21_EPS; n = n + 1) {
      XN = -1 * XN * (x - 1);
      sun = XN / n + sun;
      if (XN < 0) {
        ep = -1 * XN;
      }
    }
  } else if (x - 1 >= 1) {
    sun = -1 * s21_log(1 / x);
  }

  return sun;
}
