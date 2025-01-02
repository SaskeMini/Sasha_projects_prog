#include "../s21_decimal.h"

void notation_2(unsigned int x) {
  char str[32];
  for (int i = 0; i < 32; i++) {
    str[i] = x % 2 + '0';
    x /= 2;
  }
  printf("[ ");
  for (int i = 0; i < 32; i++) printf("%c", str[31 - i]);
  printf(" ]\n");
}
void print_decimal(s21_decimal dst) {
  printf("bits\t%5d%25d\n", 10, 2);
  for (int i = 0; i < 4; i++) {
    printf("[%d] = [%10u]", i, dst.bits[i]);
    notation_2(dst.bits[i]);
  }
}
void big_shift_right(s21_big_decimal* number, int shift_value) {
  unsigned memory = 0;
  for (int i = 7; i > -1; i--) {
    unsigned temp = number->bits[i];
    number->bits[i] = number->bits[i] >> shift_value;
    number->bits[i] = number->bits[i] | memory;
    memory = temp << (32 - shift_value);
  }
}
int zerob(s21_big_decimal* res) {
  int k = 0;

  if (res->bits[6] == 0 && res->bits[5] == 0 && res->bits[4] == 0 &&
      res->bits[3] == 0 && res->bits[2] == 0 && res->bits[1] == 0 &&
      res->bits[0] == 0) {
    res->bits[7] = 0;
    k = 1;
  }
  return k;
}
int s21_big_add_sub(s21_big_decimal big, s21_big_decimal small,
                    s21_big_decimal* res) {
  // s21_big_decimal result={0};
  res->bits[6] = 0;
  res->bits[5] = 0;
  res->bits[4] = 0;
  res->bits[3] = 0;
  res->bits[2] = 0;
  res->bits[1] = 0;
  res->bits[0] = 0;
  int bit_big = 0;
  int bit_small = 0;
  char memory = 0;
  // int num_result;

  for (int i = 0; i < 224; i++) {
    bit_big = big_get_bit(big, i);
    bit_small = big_get_bit(small, i);
    if (bit_big == 0 && bit_small == 1 && !memory) {
      memory = 1;
      res->bits[i / 32] += (int)pow(2, i % 32);
    } else if ((bit_big == 1 && bit_small == 1 && memory) ||
               (bit_big == 1 && bit_small == 0 && !memory) ||
               (bit_big == 0 && bit_small == 0 && memory)) {
      res->bits[i / 32] += (int)pow(2, i % 32);
    } else if (bit_big == 1 && bit_small == 0 && memory) {
      memory = 0;
    }
  }

  return 0;
}

int s21_big_add_mul(s21_big_decimal decimal_1, s21_big_decimal decimal_2,
                    s21_big_decimal* res) {
  s21_big_decimal result = {0};

  for (int i = 0; i < 224; i++) {  // идем по всей мантиссе

    if (big_get_bit(decimal_1, i)) {
      s21_big_add_simple(result, decimal_2, &result);
    }

    big_shift_left(&decimal_2, 1);
  }
  res->bits[6] = result.bits[6];
  res->bits[5] = result.bits[5];
  res->bits[4] = result.bits[4];
  res->bits[3] = result.bits[3];
  res->bits[2] = result.bits[2];
  res->bits[1] = result.bits[1];
  res->bits[0] = result.bits[0];

  return 0;
}
int big_greater(s21_big_decimal val_1, s21_big_decimal val_2) {
  char check = 0;
  int bit_v1;
  int bit_v2;
  for (int i = 224; i >= 0; i--) {
    bit_v1 = big_get_bit(val_1, i);
    bit_v2 = big_get_bit(val_2, i);
    if (bit_v1 > bit_v2) {
      check = 1;

      break;
    }
    if (bit_v1 < bit_v2) {
      check = 0;

      break;
    }
  }

  return check;
}

int big_equal(s21_big_decimal value_1, s21_big_decimal value_2) {
  char check = 1;
  for (int i = 0; i < 8; i++) {
    if (value_1.bits[i] != value_2.bits[i]) {
      check = 0;
      break;
    }
  }
  return check;
}
