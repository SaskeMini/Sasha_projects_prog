#include "s21_string.h"

size_t s21_strlen(const char *str) {
  size_t len = 0;
  if (str) {
    while (str[len] != '\0' && str[len]) {
      len++;
    }
  }
  return len;
}