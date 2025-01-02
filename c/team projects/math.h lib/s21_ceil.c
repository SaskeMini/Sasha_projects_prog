#include "s21_math.h"

long double s21_ceil(double x) {
  long double rounding;
  long long example = x;
  if (x == s21_PLUS_INF) {
    rounding = s21_PLUS_INF;
  } else if (x == s21_MINUS_INF) {
    rounding = s21_MINUS_INF;
  } else if (x != x) {
    rounding = s21_NAN;
  } else {
    rounding = example;
    if (x < 0 && x > -1) {
      rounding *= -1;
    }
    if (x != example && x > 0) {
      rounding += 1;
    }
  }
  return rounding;
}
