#include "s21_math.h"

long double s21_fmod(double x, double y) {
  long double dev = x / y;
  long double remainder;
  if (x != x || y != y)
    remainder = s21_NAN;
  else if (x == s21_PLUS_INF || x == s21_MINUS_INF || y == s21_PLUS_INF ||
           y == s21_MINUS_INF)
    remainder = s21_NAN;
  else {
    if (dev > 0)
      dev = s21_floor(dev);
    else
      dev = s21_ceil(dev);
    remainder = (x - dev * y);
    if (y == 0) remainder = s21_NAN;
  }
  return remainder;
}
