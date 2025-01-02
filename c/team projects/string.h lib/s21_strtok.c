#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  static char *dop = S21_NULL;
  if (!str && dop) {
    while (dop && *dop && s21_strchr(delim, *dop) != S21_NULL) {
      dop = dop + 1;
    }
    if (!dop || !*dop) {
      str = S21_NULL;
    } else {
      str = dop;
    }
  }
  if (str) {
    while (s21_strchr(delim, *str) != S21_NULL) {
      str = str + 1;
    }
  }
  char *res = S21_NULL;
  int flag = 0;
  if (str) {
    for (long unsigned j = 0; s21_strlen(str) > j && flag != 1; j++) {
      for (long unsigned i = 0; s21_strlen(delim) > i; i++) {
        if (str[j] == delim[i]) {
          flag = 1;
          res = str;
          res[j] = '\0';
          if (dop != S21_NULL) {
            dop = dop + j + 1;
          } else {
            dop = str + j + 1;
          }
          break;
        }
      }
      if (j == s21_strlen(str) - 1 && !res) {
        res = dop;
        dop = S21_NULL;
      }
    }
  }
  if (res) {
    if (res[0] == '\0') {
      return S21_NULL;
    }
  }
  return res;
}
