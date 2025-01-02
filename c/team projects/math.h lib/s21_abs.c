#include "s21_math.h"

int s21_abs(int x) {
  int result;
  if (x < 0)
    result = x * (-1);
  else
    result = x;
  return result;
}
