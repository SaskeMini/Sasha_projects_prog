#include "s21_math.h"

long double s21_exp(double x) {
  long double sun = 1.0;
  int k = 0;

  if (x == S21_INF) {
    sun = S21_INF;
  }

  else if (x != x) {
    sun = S21_NAN;
  }

  else if (x == -S21_INF) {
    sun = 0;
  }

  else {
    long double XN = x;

    if (x < 0.0) {
      XN = -x;
      x = -x;
      k = 1;
    }
    sun = 1 + XN;

    for (int n = 2; n < 10000; n++) {  // for подчёркивается красным
      XN = XN * x / n;
      sun = sun + XN;
    }
    // Если x отрицательный, вычислить обратное значение
    if (k == 1) sun = 1 / sun;
  }

  return sun;
}
