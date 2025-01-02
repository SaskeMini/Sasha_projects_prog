#include "s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  size_t len_str = s21_strlen(src);
  size_t len_temp = s21_strlen(trim_chars);
  if (!src) {
    return S21_NULL;
  }
  char *temp_string;
  char mass_trim[len_str];
  for (size_t i = 0; i < len_str; i++) {
    mass_trim[i] = 0;
  }
  for (size_t i = 0; i < len_str; i++) {
    for (size_t j = 0; j < len_temp; j++) {
      if (trim_chars[j] == src[i]) {
        mass_trim[i] = 1;
        break;
      }
    }
  }
  char check = 0;
  for (size_t i = 0; i < len_str; i++) {
    if (mass_trim[i] == 1) {
      check = 1;
    }
  }
  if (check == 0 && trim_chars[0] == '\0') {
    size_t check_left = 0;
    for (size_t i = 0; i < len_str; i++) {
      if (src[i] == ' ' || src[i] == '\n' || src[i] == '\t') {
        mass_trim[i] = 1;
      } else if (check_left == 0) {
        check_left = i;
      } else {
        for (size_t z = check_left; z < i; z++) {
          mass_trim[z] = 0;
        }
      }
    }
  }
  size_t count_res = 0;
  for (size_t i = 0; i < len_str; i++) {
    if (mass_trim[i] == 0) {
      count_res++;
    }
  }
  temp_string = malloc(sizeof(char) * (count_res + 1));
  size_t count_passed_trims = 0;
  for (size_t i = 0; i < len_str; i++) {
    if (mass_trim[i] == 0) {
      temp_string[i - count_passed_trims] = src[i];
    } else {
      count_passed_trims++;
    }
  }
  temp_string[count_res] = '\0';
  return temp_string;
}