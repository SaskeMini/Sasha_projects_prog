#include "s21_string.h"

void *s21_insert(const char *src, const char *str, size_t start_index) {
  if (!src || !str) {
    return S21_NULL;
  }
  size_t len_str = s21_strlen(src);
  size_t len_temp = s21_strlen(str);
  if (start_index >= len_str) {
    return S21_NULL;
  }
  char *temp_string = malloc(sizeof(char) * (len_temp + len_str + 1));
  char check = 0;
  for (size_t i = 0; i < len_str; i++) {
    if (i == start_index && !check) {
      check = 1;
      for (size_t j = 0; j < len_temp; j++) {
        temp_string[i + j] = str[j];
      }
      temp_string[i + len_temp] = src[i];
    } else {
      if (check) {
        temp_string[i + len_temp] = src[i];
      } else {
        temp_string[i] = src[i];
      }
    }
  }
  temp_string[len_temp + len_str] = '\0';
  return (char *)temp_string;
}