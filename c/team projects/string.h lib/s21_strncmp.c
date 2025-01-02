// 7
// Сравнивает не более первых n байтов str1 и str2.

#include "s21_string.h"

int s21_strncmp(const char* str1, const char* str2, size_t n) {
  int bool_result = 0;

  for (unsigned int index = 0; index < n; index++)
    if (str1[index] != str2[index]) {
      bool_result = str1[index] - str2[index];
      break;
    }
  if (bool_result != 0) {
    printf("%d", bool_result);
  } else {
    printf("%d", bool_result);
  }

  return bool_result;
}
