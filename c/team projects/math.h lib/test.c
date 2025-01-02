#include <check.h>
#include <math.h>

#include "s21_math.h"

long double okrygl(long double x) {
  x *= 1000000;
  x = nearbyint(x);
  x /= 1000000;
  return x;
}

START_TEST(test_cos) {
  long double j = 0;
  for (long double i = -3 * S21_PI; i < 3 * S21_PI; i += 0.001) {
    if (okrygl(s21_cos(i)) != okrygl(cos(i))) {
      ck_assert_double_eq(okrygl(s21_cos(i)), okrygl(cos(i)));
    }
    j = i;
  }
  ck_assert_double_eq(okrygl(s21_cos(j)), okrygl(cos(j)));
}
END_TEST
START_TEST(test_cos_NAN) { ck_assert_double_nan(s21_cos(NAN)); }
END_TEST
START_TEST(test_cos_0) {
  ck_assert_double_eq(okrygl(s21_cos(0)), okrygl(cos(0)));
}
END_TEST
START_TEST(test_cos_PLUS_INF) { ck_assert_double_nan(s21_cos(s21_PLUS_INF)); }
END_TEST
START_TEST(test_cos_MINUS_INF) { ck_assert_double_nan(s21_cos(s21_MINUS_INF)); }
END_TEST
START_TEST(test_sin) {
  long double j = 0;
  for (long double i = -3 * S21_PI; i < 3 * S21_PI; i += 0.001) {
    if (okrygl(s21_sin(i)) != okrygl(sin(i))) {
      ck_assert_double_eq(okrygl(s21_sin(i)), okrygl(sin(i)));
    }
    j = i;
  }
  ck_assert_double_eq(okrygl(s21_sin(j)), okrygl(sin(j)));
}
END_TEST
START_TEST(test_sin_NAN) { ck_assert_double_nan(s21_sin(NAN)); }
END_TEST
START_TEST(test_sin_PLUS_INF) { ck_assert_double_nan(s21_sin(s21_PLUS_INF)); }
END_TEST
START_TEST(test_sin_MINUS_INF) { ck_assert_double_nan(s21_sin(s21_MINUS_INF)); }
END_TEST
START_TEST(test_sin_0) {
  ck_assert_double_eq(okrygl(s21_sin(0)), okrygl(sin(0)));
}
END_TEST
START_TEST(test_abs) {
  int j = 0;
  for (int i = -100; i < 100; i++) {
    if (abs(i) != s21_abs(i)) {
      ck_assert_int_eq(abs(i), s21_abs(i));
    }
    j = i;
  }
  ck_assert_int_eq(abs(j), s21_abs(j));
}
END_TEST
END_TEST
START_TEST(test_tan) {
  long double j = 0;
  for (long double i = -3 * S21_PI; i < 3 * S21_PI; i += 0.001) {
    if (okrygl(s21_tan(i)) != okrygl(tan(i))) {
      ck_assert_double_eq(okrygl(s21_tan(i)), okrygl(tan(i)));
    }
    j = i;
  }
  for (long double i = 1; i < 30; i++) {
    if (okrygl(s21_tan(i)) != okrygl(tan(i))) {
      if (!(isnan(s21_tan(i)) != 0 && isnan(tan(i)) != 0)) {
        ck_assert_double_eq(okrygl(s21_tan(i)), okrygl(tan(i)));
      }
    }
    j = i;
  }
  ck_assert_double_eq(okrygl(s21_tan(j)), okrygl(tan(j)));
}
END_TEST
START_TEST(test_tan_NAN) { ck_assert_double_nan(s21_tan(NAN)); }
END_TEST
START_TEST(test_tan_PLUS_INF) { ck_assert_double_nan(s21_tan(s21_PLUS_INF)); }
END_TEST
START_TEST(test_tan_MINUS_INF) { ck_assert_double_nan(s21_tan(s21_MINUS_INF)); }
END_TEST
START_TEST(test_sqrt) {
  long double j = 0;
  for (long double i = -3 * S21_PI; i < 3 * S21_PI; i += 0.001) {
    if (okrygl(s21_sqrt(i)) != okrygl(sqrt(i))) {
      if (!(isnan(s21_sqrt(i)) != 0 && isnan(sqrt(i)) != 0)) {
        ck_assert_double_eq(okrygl(s21_sqrt(i)), okrygl(sqrt(i)));
      }
    }
    j = i;
  }
  ck_assert_double_eq(okrygl(s21_sqrt(j)), okrygl(sqrt(j)));
}
END_TEST
START_TEST(test_sqrt_NAN) { ck_assert_double_nan(s21_sqrt(NAN)); }
END_TEST
START_TEST(test_sqrt_PLUS_INF) {
  ck_assert_double_infinite(s21_sqrt(s21_PLUS_INF));
}
END_TEST
START_TEST(test_sqrt_MINUS_INF) {
  ck_assert_double_nan(s21_sqrt(s21_MINUS_INF));
}
END_TEST
START_TEST(test_pow) {
  for (long double i = -2.0; i < -1; i += 0.01) {
    for (long double x = -2.0; x < -1; x += 0.01) {
      if (okrygl(s21_pow(i, x)) != okrygl(pow(i, x))) {
        if (!(isnan(s21_pow(i, x)) != 0 && isnan(pow(i, x)) != 0)) {
          printf("%Lf %Lf\n", i, x);
          ck_assert_double_eq(okrygl(s21_pow(i, x)), okrygl(pow(i, x)));
        }
      }
    }
  }
  for (long double i = 1.0; i < 2; i += 0.01) {
    for (long double x = 1; x < 2; x += 0.01) {
      if (okrygl(s21_pow(i, x)) != okrygl(pow(i, x))) {
        if (!(isnan(s21_pow(i, x)) != 0 && isnan(pow(i, x)) != 0)) {
          printf("%Lf %Lf\n", i, x);
          ck_assert_double_eq(okrygl(s21_pow(i, x)), okrygl(pow(i, x)));
        }
      }
    }
  }
  ck_assert_double_eq(okrygl(s21_pow(-1, 0)), okrygl(pow(-1, 0)));
}
END_TEST
START_TEST(test_pow_NAN) { ck_assert_double_nan(s21_pow(NAN, NAN)); }
END_TEST
START_TEST(test_pow_PLUS_INF) {
  ck_assert_double_infinite(s21_pow(s21_PLUS_INF, s21_PLUS_INF));
}
END_TEST
START_TEST(test_pow_1) {
  ck_assert_double_eq(okrygl(s21_pow(-1, s21_PLUS_INF)),
                      okrygl(pow(-1, s21_PLUS_INF)));
}
END_TEST
START_TEST(test_pow_MINUS_INF) {
  ck_assert_double_nan(s21_pow(s21_MINUS_INF, s21_MINUS_INF));
}
END_TEST
START_TEST(test_log) {
  long double j = 0;
  for (long double i = -3 * S21_PI; i < 3 * S21_PI; i += 0.001) {
    if (okrygl(s21_log(i)) != okrygl(log(i))) {
      if (!(isnan(s21_log(i)) != 0 && isnan(log(i)) != 0)) {
        ck_assert_double_eq(okrygl(s21_log(i)), okrygl(log(i)));
      }
    }
    j = i;
  }
  for (long double i = 0; i < 30.0; i++) {
    if (okrygl(s21_log(i)) != okrygl(log(i))) {
      if (!(isnan(s21_log(i)) != 0 && isnan(log(i)) != 0)) {
        ck_assert_double_eq(okrygl(s21_log(i)), okrygl(log(i)));
      }
    }
    j = i;
  }
  ck_assert_double_eq(okrygl(s21_log(j)), okrygl(log(j)));
}
END_TEST
START_TEST(test_log_NAN) { ck_assert_double_nan(s21_log(NAN)); }
END_TEST
START_TEST(test_log_PLUS_INF) {
  ck_assert_double_infinite(s21_log(s21_PLUS_INF));
}
END_TEST
START_TEST(test_log_MINUS_INF) { ck_assert_double_nan(s21_log(s21_MINUS_INF)); }
END_TEST
START_TEST(test_asin) {
  long double j = 0;
  for (long double i = -3 * S21_PI; i < 3 * S21_PI; i += 0.001) {
    if (okrygl(s21_asin(i)) != okrygl(asin(i))) {
      if (!(isnan(s21_asin(i)) != 0 && isnan(asin(i)) != 0)) {
        ck_assert_double_eq(okrygl(s21_asin(i)), okrygl(asin(i)));
      }
    } else {
      j = i;
    }
  }
  for (long double i = -100; i < 100; i += 1) {
    if (okrygl(s21_asin(i)) != okrygl(asin(i))) {
      if (!(isnan(s21_asin(i)) != 0 && isnan(asin(i)) != 0)) {
        ck_assert_double_eq(okrygl(s21_asin(i)), okrygl(asin(i)));
      }
    } else {
      j = i;
    }
  }
  ck_assert_double_eq(okrygl(s21_asin(j)), okrygl(asin(j)));
}
END_TEST
START_TEST(test_asin_NAN) { ck_assert_double_nan(s21_asin(NAN)); }
END_TEST
START_TEST(test_asin_PLUS_INF) { ck_assert_double_nan(s21_asin(s21_PLUS_INF)); }
END_TEST
START_TEST(test_asin_MINUS_INF) {
  ck_assert_double_nan(s21_asin(s21_MINUS_INF));
}
END_TEST
START_TEST(test_acos) {
  long double j = 0;
  for (long double i = -3 * S21_PI; i < 3 * S21_PI; i += 0.001) {
    if (okrygl(s21_acos(i)) != okrygl(acos(i))) {
      if (!(isnan(s21_acos(i)) != 0 && isnan(acos(i)) != 0)) {
        ck_assert_double_eq(okrygl(s21_acos(i)), okrygl(acos(i)));
      }
    } else {
      j = i;
    }
  }
  for (long double i = -100; i < 100; i += 1) {
    if (okrygl(s21_acos(i)) != okrygl(acos(i))) {
      if (!(isnan(s21_acos(i)) != 0 && isnan(acos(i)) != 0)) {
        ck_assert_double_eq(okrygl(s21_acos(i)), okrygl(acos(i)));
      }
    } else {
      j = i;
    }
  }
  ck_assert_double_eq(okrygl(s21_acos(j)), okrygl(acos(j)));
}
START_TEST(test_acos_NAN) { ck_assert_double_nan(s21_acos(NAN)); }
END_TEST
START_TEST(test_acos_PLUS_INF) { ck_assert_double_nan(s21_acos(s21_PLUS_INF)); }
END_TEST
START_TEST(test_acos_MINUS_INF) {
  ck_assert_double_nan(s21_acos(s21_MINUS_INF));
}
END_TEST
END_TEST
START_TEST(test_atan) {
  long double j = 0;
  for (long double i = -3 * S21_PI; i < 3 * S21_PI; i += 0.001) {
    if (okrygl(s21_atan(i)) != okrygl(atan(i))) {
      if (!(isnan(s21_atan(i)) != 0 && isnan(atan(i)) != 0)) {
        ck_assert_double_eq(okrygl(s21_atan(i)), okrygl(atan(i)));
      }
    } else {
      j = i;
    }
  }
  ck_assert_double_eq(okrygl(s21_atan(j)), okrygl(atan(j)));
}
END_TEST
START_TEST(test_atan_NAN) { ck_assert_double_nan(s21_atan(NAN)); }
END_TEST
START_TEST(test_atan_1) {
  ck_assert_double_eq(okrygl(s21_atan(1)), okrygl(atan(1)));
}
END_TEST
START_TEST(test_atan_0) {
  ck_assert_double_eq(okrygl(s21_atan(0)), okrygl(atan(0)));
}
END_TEST
START_TEST(test_atan_2) {
  ck_assert_double_eq(okrygl(s21_atan(-1)), okrygl(atan(-1)));
}
END_TEST
START_TEST(test_exp_1) { ck_assert_double_nan(s21_exp(s21_NAN)); }
END_TEST
START_TEST(test_exp_2) {
  ck_assert_double_eq(okrygl(s21_atan(s21_MINUS_INF)),
                      okrygl(atan(s21_MINUS_INF)));
}
END_TEST
START_TEST(test_ceil) {
  long double j = 0;
  for (long double i = -3 * S21_PI; i < 3 * S21_PI; i += 0.001) {
    if (okrygl(s21_ceil(i)) != okrygl(ceil(i))) {
      if (!(isnan(s21_ceil(i)) != 0 && isnan(ceil(i)) != 0)) {
        ck_assert_double_eq(okrygl(s21_ceil(i)), okrygl(ceil(i)));
      }
    } else {
      j = i;
    }
  }
  ck_assert_double_eq(okrygl(s21_ceil(j)), okrygl(ceil(j)));
}
END_TEST
START_TEST(test_ceil_NAN) { ck_assert_double_nan(s21_ceil(NAN)); }
END_TEST
START_TEST(test_ceil_PLUS_INF) {
  ck_assert_double_infinite(s21_ceil(s21_PLUS_INF));
}
END_TEST
START_TEST(test_ceil_MINUS_INF) {
  ck_assert_double_infinite(s21_ceil(s21_MINUS_INF));
}
END_TEST
START_TEST(test_fabs) {
  double j = 0;
  for (double i = -3 * S21_PI; i < 3 * S21_PI; i += 0.001) {
    if (okrygl(s21_fabs(i)) != okrygl(fabs(i))) {
      if (!(isnan(s21_fabs(i)) != 0 && isnan(fabs(i)) != 0)) {
        ck_assert_double_eq(okrygl(s21_fabs(i)), okrygl(fabs(i)));
      }
    } else {
      j = i;
    }
  }
  ck_assert_double_eq(okrygl(s21_fabs(j)), okrygl(fabs(j)));
}
END_TEST
START_TEST(test_fabs_NAN) { ck_assert_double_nan(s21_fabs(NAN)); }
END_TEST
START_TEST(test_fabs_PLUS_INF) {
  ck_assert_double_infinite(s21_fabs(s21_PLUS_INF));
}
END_TEST
START_TEST(test_fabs_MINUS_INF) {
  ck_assert_double_infinite(s21_fabs(s21_MINUS_INF));
}
END_TEST
START_TEST(test_floor) {
  long double j = 0;
  for (long double i = -3 * S21_PI; i < 3 * S21_PI; i += 0.001) {
    if (okrygl(s21_floor(i)) != okrygl(floor(i))) {
      if (!(isnan(s21_floor(i)) != 0 && isnan(floor(i)) != 0)) {
        ck_assert_double_eq(okrygl(s21_floor(i)), okrygl(floor(i)));
      }
    } else {
      j = i;
    }
  }
  ck_assert_double_eq(okrygl(s21_floor(j)), okrygl(floor(j)));
}
END_TEST
START_TEST(test_floor_NAN) { ck_assert_double_nan(s21_floor(NAN)); }
END_TEST
START_TEST(test_floor_PLUS_INF) {
  ck_assert_double_infinite(s21_floor(s21_PLUS_INF));
}
END_TEST
START_TEST(test_floor_MINUS_INF) {
  ck_assert_double_infinite(s21_floor(s21_MINUS_INF));
}
END_TEST
START_TEST(test_fmod) {
  long double j = 0, k = 0;
  for (long double i = -5; i < 5; i += 0.01) {
    for (long double x = -30; x < 30; x += 0.01) {
      if (okrygl(s21_fmod(i, x)) != okrygl(fmod(i, x))) {
        if (!(isnan(s21_fmod(i, x)) != 0 && isnan(fmod(i, x)) != 0)) {
          printf("%Lf %Lf\n", i, x);
          ck_assert_double_eq(okrygl(s21_fmod(i, x)), okrygl(fmod(i, x)));
        }
      }
      j = i;
      k = x;
    }
  }
  ck_assert_double_eq(okrygl(s21_fmod(j, k)), okrygl(fmod(j, k)));
}
END_TEST
START_TEST(test_fmod_NAN) { ck_assert_double_nan(s21_fmod(NAN, NAN)); }
END_TEST
START_TEST(test_fmod_PLUS_INF) {
  ck_assert_double_nan(s21_fmod(s21_PLUS_INF, s21_PLUS_INF));
}
END_TEST
START_TEST(test_fmod_MINUS_INF) {
  ck_assert_double_nan(s21_fmod(s21_MINUS_INF, s21_MINUS_INF));
}
END_TEST

int main(void) {
  Suite *s = suite_create("Core");
  TCase *tc = tcase_create("Core");
  SRunner *srun = srunner_create(s);
  int sf = 0;
  suite_add_tcase(s, tc);
  tcase_add_test(tc, test_cos);
  tcase_add_test(tc, test_cos_0);
  tcase_add_test(tc, test_cos_NAN);
  tcase_add_test(tc, test_cos_PLUS_INF);
  tcase_add_test(tc, test_cos_MINUS_INF);
  tcase_add_test(tc, test_abs);
  tcase_add_test(tc, test_sin);
  tcase_add_test(tc, test_sin_NAN);
  tcase_add_test(tc, test_sin_PLUS_INF);
  tcase_add_test(tc, test_sin_MINUS_INF);
  tcase_add_test(tc, test_sin_0);
  tcase_add_test(tc, test_tan);
  tcase_add_test(tc, test_tan_NAN);
  tcase_add_test(tc, test_tan_PLUS_INF);
  tcase_add_test(tc, test_tan_MINUS_INF);
  tcase_add_test(tc, test_sqrt);
  tcase_add_test(tc, test_sqrt_NAN);
  tcase_add_test(tc, test_sqrt_PLUS_INF);
  tcase_add_test(tc, test_sqrt_MINUS_INF);
  tcase_add_test(tc, test_pow);
  tcase_add_test(tc, test_pow_NAN);
  tcase_add_test(tc, test_pow_PLUS_INF);
  tcase_add_test(tc, test_pow_MINUS_INF);
  tcase_add_test(tc, test_pow_1);
  tcase_add_test(tc, test_log);
  tcase_add_test(tc, test_log_NAN);
  tcase_add_test(tc, test_log_PLUS_INF);
  tcase_add_test(tc, test_log_MINUS_INF);
  tcase_add_test(tc, test_asin);
  tcase_add_test(tc, test_asin_NAN);
  tcase_add_test(tc, test_asin_PLUS_INF);
  tcase_add_test(tc, test_asin_MINUS_INF);
  tcase_add_test(tc, test_acos);
  tcase_add_test(tc, test_acos_NAN);
  tcase_add_test(tc, test_acos_PLUS_INF);
  tcase_add_test(tc, test_acos_MINUS_INF);
  tcase_add_test(tc, test_atan);
  tcase_add_test(tc, test_atan_NAN);
  tcase_add_test(tc, test_atan_0);
  tcase_add_test(tc, test_atan_1);
  tcase_add_test(tc, test_atan_2);
  tcase_add_test(tc, test_ceil);
  tcase_add_test(tc, test_ceil_NAN);
  tcase_add_test(tc, test_ceil_PLUS_INF);
  tcase_add_test(tc, test_ceil_MINUS_INF);
  tcase_add_test(tc, test_fmod);
  tcase_add_test(tc, test_fmod_NAN);
  tcase_add_test(tc, test_fmod_PLUS_INF);
  tcase_add_test(tc, test_fmod_MINUS_INF);
  tcase_add_test(tc, test_fabs);
  tcase_add_test(tc, test_fabs_NAN);
  tcase_add_test(tc, test_fabs_PLUS_INF);
  tcase_add_test(tc, test_fabs_MINUS_INF);
  tcase_add_test(tc, test_floor);
  tcase_add_test(tc, test_floor_NAN);
  tcase_add_test(tc, test_floor_PLUS_INF);
  tcase_add_test(tc, test_floor_MINUS_INF);
  tcase_add_test(tc, test_exp_1);
  tcase_add_test(tc, test_exp_2);
  srunner_run_all(srun, CK_ENV);
  sf = srunner_ntests_failed(srun);
  srunner_free(srun);
  return sf == 0 ? 0 : 1;
}
