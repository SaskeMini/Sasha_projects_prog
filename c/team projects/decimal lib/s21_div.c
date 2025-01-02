#include "s21_decimal.h"
int is_greate(s21_big_decimal *ostatok, s21_big_decimal znam,
              s21_big_decimal *res, int shift);
int find_shift(s21_big_decimal big);

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int k = 0;
  s21_big_decimal big1 = {0};
  s21_from_dec_to_big(value_1, &big1);
  s21_big_decimal big2 = {0};
  s21_from_dec_to_big(value_2, &big2);
  s21_big_decimal res = {0};
  s21_big_decimal ed = {0};
  ed.bits[0] = 1;
  s21_big_decimal ten = {0};
  ten.bits[0] = 10;
  s21_big_decimal ostatok = {0};
  int res_scale = get_scale(value_1) - get_scale(value_2);

  s21_big_decimal znam = {0};
  big1.bits[7] = 0;
  big2.bits[7] = 0;

  if (res_scale < 0) {
    while (res_scale < 0) {
      s21_big_add_mul(ten, big1, &big1);
      res_scale++;
    }
  }

  int sdvig = find_shift(big2);
  int shift = find_shift(big1);

  ostatok = big1;

  shift = shift - sdvig;

  ostatok = big1;
  znam = big2;

  int sign = (get_sign(value_1) || get_sign(value_2));

  if (zero(&value_2)) {
    k = 3;
  } else if (value_2.bits[2] == 0 && value_2.bits[1] == 0 &&
             value_2.bits[0] == 1) {
    res = big1;
    big_set_scale(&res, res_scale);
    big_set_sign(&res, sign);
    k = s21_from_big_to_dec(res, result);
    // while (res_scale
  } else if (big_equal(big1, big2)) {
    s21_big_add_simple(res, ed, &res);
    big_set_scale(&res, res_scale);
    big_set_sign(&res, sign);
    k = s21_from_big_to_dec(res, result);
  } else {
    if (big_greater(big1, big2)) {
      is_greate(&ostatok, znam, &res, shift);
    }

    if (big_greater(big2, ostatok) && zerob(&ostatok) == 0) {
      while (zerob(&ostatok) == 0 && res.bits[3] < 429496729) {  // 4294967295

        s21_big_add_mul(ten, ostatok, &ostatok);
        s21_big_add_mul(ten, res, &res);

        res_scale++;
        s21_big_decimal resa = {0};
        shift = find_shift(ostatok);

        shift = shift - sdvig;

        if (big_greater(ostatok, big2)) {
          is_greate(&ostatok, big2, &resa, shift);
          s21_big_add_simple(res, resa, &res);

        }

        else if (big_greater(big2, ostatok)) {
        } else if (big_equal(ostatok, big2)) {
          big_shift_left(&res, 1);
          s21_big_add_simple(res, ed, &res);
          big_shift_left(&res, 1);
          s21_big_add_sub(ostatok, big2, &ostatok);
        }
      }
    }
    if (big_equal(ostatok, big2)) {
      big_shift_left(&res, 1);
      s21_big_add_simple(res, ed, &res);
      big_shift_left(&res, 1);
    }

    //}

    big_set_scale(&res, res_scale);
    big_set_sign(&res, sign);
    k = s21_from_big_to_dec(res, result);
  }  // dobavila

  zero(result);
  return k;
}
int is_greate(s21_big_decimal *ostatok, s21_big_decimal znam,
              s21_big_decimal *res, int shift) {
  s21_big_decimal keep = znam;

  s21_big_decimal ed = {0};
  ed.bits[0] = 1;
  big_shift_left(&znam, shift);

  if (big_greater(znam, *ostatok)) {
    big_shift_right(&znam, 1);
    shift = shift - 1;
  }
  s21_big_add_sub(*ostatok, znam, ostatok);
  big_shift_left(res, 1);
  s21_big_add_simple(*res, ed, res);
  shift--;

  znam = keep;

  while (shift > -1) {
    znam = keep;
    big_shift_left(&znam, shift);
    if (big_greater(*ostatok, znam) == 1) {
      s21_big_add_sub(*ostatok, znam, ostatok);

      big_shift_left(res, 1);
      s21_big_add_simple(*res, ed, res);

    } else if (big_equal(*ostatok, znam)) {
      big_shift_left(res, 1);
      s21_big_add_simple(*res, ed, res);

      ostatok->bits[6] = 0;
      ostatok->bits[5] = 0;
      ostatok->bits[4] = 0;
      ostatok->bits[3] = 0;
      ostatok->bits[2] = 0;
      ostatok->bits[1] = 0;
      ostatok->bits[0] = 0;

    }

    else {
      big_shift_left(res, 1);
    }

    shift--;
  }

  return 0;
}

int find_shift(s21_big_decimal big) {
  int shift = 0;
  for (int i = 223; i >= 0; i--) {
    if (big_get_bit(big, i) == 1) {
      shift = i;
      break;
    }
  }

  return shift;
}
