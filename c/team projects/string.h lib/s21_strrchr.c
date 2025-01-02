#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
  const char *res = 0;
  if (str != 0) {
    do {
      if (*str == (char)c) {
        res = str;
      }
    } while (*str++);
  }
  return (char *)res;
}
