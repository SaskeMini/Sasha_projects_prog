#include "s21_string.h"

char *s21_strncat(char *dest, const char *src, size_t n) {
  int count = s21_strlen(dest);
  int i = 0, value = n;
  while (i < value) {
    dest[count] = src[i];
    i++;
    count++;
  }
  return dest;
}