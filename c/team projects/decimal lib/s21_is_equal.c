#include "s21_decimal.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  zero(&value_1);
  zero(&value_2);
  s21_big_decimal val_1 = {{0, 0, 0, 0, 0, 0, 0}};
  s21_big_decimal val_2 = {{0, 0, 0, 0, 0, 0, 0}};

  s21_from_dec_to_big(value_1, &val_1);
  s21_from_dec_to_big(value_2, &val_2);
  big_normalize(&val_1, &val_2);
  char check = 1;
  for (int i = 0; i < 8; i++) {
    if (val_1.bits[i] != val_2.bits[i]) {
      check = 0;
      break;
    }
  }
  return check;
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  char check = !s21_is_equal(value_1, value_2);
  return check;
}

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  char check = 0;

  if (get_sign(value_1) == 1 && get_sign(value_2) == 0) {
    check = 1;
  }
  if (get_sign(value_1) == 0 && get_sign(value_2) == 1) {
    check = 0;
  }
  if (get_sign(value_1) == get_sign(value_2)) {
    s21_big_decimal val_1 = {{0, 0, 0, 0, 0, 0, 0}};
    s21_big_decimal val_2 = {{0, 0, 0, 0, 0, 0, 0}};
    // s21_big_decimal res = {{0, 0, 0, 0, 0, 0, 0}};
    s21_from_dec_to_big(value_1, &val_1);
    s21_from_dec_to_big(value_2, &val_2);
    big_normalize(&val_1, &val_2);
    int bit_v1;
    int bit_v2;
    for (int i = 223; i >= 0; i--) {
      bit_v1 = big_get_bit(val_1, i);
      bit_v2 = big_get_bit(val_2, i);
      if (bit_v1 < bit_v2) {
        check = 1;
        if (big_get_sign(val_1) == 1) check = 0;
        break;
      } else if (bit_v1 > bit_v2) {
        check = 0;
        if (big_get_sign(val_1) == 1) check = 1;
        break;
      }
    }
  }
  return check;
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  zero(&value_1);
  zero(&value_2);
  char check = 0;
  if (s21_is_less(value_1, value_2)) {
    check = 1;
  }
  if (s21_is_equal(value_1, value_2)) {
    check = 1;
  }
  return check;
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  char check = 0;
  if (get_sign(value_1) && get_sign(value_2) == 0) {
    check = 0;
  }
  if (get_sign(value_1) == 0 && get_sign(value_2)) {
    check = 1;
  }
  if (get_sign(value_1) == get_sign(value_2)) {
    s21_big_decimal val_1 = {{0, 0, 0, 0, 0, 0, 0}};
    s21_big_decimal val_2 = {{0, 0, 0, 0, 0, 0, 0}};
    // s21_big_decimal res = {{0, 0, 0, 0, 0, 0, 0}};
    s21_from_dec_to_big(value_1, &val_1);
    s21_from_dec_to_big(value_2, &val_2);
    big_normalize(&val_1, &val_2);
    int bit_v1;
    int bit_v2;
    for (int i = 223; i >= 0; i--) {
      bit_v1 = big_get_bit(val_1, i);
      bit_v2 = big_get_bit(val_2, i);
      if (bit_v1 > bit_v2) {
        check = 1;
        if (big_get_sign(val_1) == 1) {
          check = 0;
        }
        break;
      } else if (bit_v1 < bit_v2) {
        check = 0;
        if (big_get_sign(val_1) == 1) {
          check = 1;
        }
        break;
      }
    }
  }
  return check;
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  char check = 0;
  if (s21_is_greater(value_1, value_2)) {
    check = 1;
  }
  if (s21_is_equal(value_1, value_2)) {
    check = 1;
  }
  return check;
}
