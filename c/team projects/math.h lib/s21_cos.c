#include "s21_math.h"

long double s21_cos(double x) {
  long double xl = s21_fmod(x, 2.0 * S21_PI);
  long double sun = 1;

  if (x == 0 || xl == 0) {
    sun = 1;
  } else if (x == S21_INF || x == -S21_INF) {
    sun = -S21_NAN;
  } else if (s21_is_nan(x)) {
    sun = x * S21_NAN;
  }

  else {
    long double xl = s21_fmod(x, 2.0 * S21_PI);
    long double ep = 1.0;
    long double XN = 1;
    for (int n = 2; ep > S21_EPS; n = n + 2) {
      XN = -1 * XN * xl * xl / n / (n - 1);
      sun = XN + sun;
      if (XN < 0) {
        ep = -1 * XN;
      }
    }
  }
  return sun;
}