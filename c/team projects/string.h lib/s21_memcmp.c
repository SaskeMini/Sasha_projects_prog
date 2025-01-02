#include "s21_string.h"

int s21_memcmp(const void *str1, const void *str2, size_t n) {
  const unsigned char *string1 = str1;
  const unsigned char *string2 = str2;
  size_t res = 0;
  for (size_t i = 0; i < n; i++) {
    if (*string1 == *string2) {
      string1++;
      string2++;
    } else {
      res = (*string1 - *string2);
    }
  }
  return res;
}