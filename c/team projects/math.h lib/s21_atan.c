#include "s21_math.h"

long double s21_atan(double x) {
  long double XN = x;
  long double sun = XN;
  if (x == 0) {
    sun = 0;
  }
  if (x == -1.0) {
    sun = -S21_PI / 4;
  }
  if (x == 1.0) {
    sun = S21_PI / 4;
  }
  if (x < 1 && x > -1 && x != 0) {
    long double ep = 1.0;
    for (int n = 3; ep > S21_EPS; n = n + 2) {
      XN = -1 * XN * x * x;
      sun = (XN / n) + sun;
      if (XN < 0) {
        ep = -1 * XN;
      }
    }
  }
  if (x > 1.0) {
    sun = S21_PI / 2 - s21_atan(1.0 / x);
  }
  if (x < -1.0) {
    sun = -S21_PI / 2 - s21_atan(1.0 / x);
  }

  return sun;
}
