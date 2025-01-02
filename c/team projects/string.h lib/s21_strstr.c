#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  char *res = S21_NULL;
  int n = s21_strlen(needle);
  if (*needle == 0) res = (char *)haystack;
  while (*haystack != '\0' && *needle != '\0') {
    if (s21_memcmp(haystack, needle, n) != 0) {
      haystack++;
    } else {
      res = (char *)haystack;
      break;
    }
  }
  return res;
}
