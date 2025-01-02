#include "s21_string.h"

void *s21_memchr(const void *str, int c, size_t n) {
  const unsigned char *st = (unsigned char *)str;
  unsigned char *res = S21_NULL;
  if (str != S21_NULL) {
    while (n-- > 0) {
      if (*st == c) {
        res = (void *)st;
        break;
      }
      st++;
    }
  }
  return res;
}