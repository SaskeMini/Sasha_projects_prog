#include "s21_string.h"

void *s21_memcpy(void *dest, const void *src, size_t n) {
  unsigned char *str1 = (unsigned char *)dest;
  unsigned char *str2 = (unsigned char *)src;
  int count = n;
  for (int i = 0; i < count; i++) {
    str1[i] = str2[i];
  }
  return str1;
}