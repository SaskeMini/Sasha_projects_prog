#include "s21_string.h"

void *s21_memset(void *str, int c, size_t n) {
  unsigned char *buff = (unsigned char *)str;
  for (unsigned int i = 0; i < n; i++) {
    buff[i] = c;
  }
  return buff;
}