#include "s21_math.h"

long double s21_floor(double x) {
  long double example = (long long)x;
  if (x == s21_MINUS_INF) example = s21_MINUS_INF;
  if (x == s21_PLUS_INF) example = s21_PLUS_INF;
  if (x != x) example = s21_NAN;
  if (example > x) example--;
  return example;
}
