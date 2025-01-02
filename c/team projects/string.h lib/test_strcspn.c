/*
 * DO NOT EDIT THIS FILE. Generated by checkmk.
 * Edit the original source file "test_strcspn.check" instead.
 */

#include <check.h>
#include <string.h>

#include "s21_string.h"

const char a[] = "Lorem ipsum dolor sit amet";
const char b[] = "Lorem Hello ipsum dolor sit amet";
const char c[] = "Lorem ipsum dolor  amet";
const char d[] = "Lorem ipsum cat dolor sit amet";
const char e[] = "Hello, World";
const char f[] = "Lorem ipsum dolor sit amet";
const char g[] = "Lorem upsum dolor sit amet";

START_TEST(strcspn1) { ck_assert_int_eq(strcspn(b, a), s21_strcspn(b, a)); }
END_TEST

START_TEST(strcspn2) { ck_assert_int_eq(strcspn(b, c), s21_strcspn(b, c)); }
END_TEST

START_TEST(strcspn3) { ck_assert_int_eq(strcspn(b, d), s21_strcspn(b, d)); }
END_TEST

START_TEST(strcspn4) { ck_assert_int_eq(strcspn(f, a), s21_strcspn(f, a)); }
END_TEST

START_TEST(strcspn5) { ck_assert_int_eq(strcspn(a, e), s21_strcspn(a, e)); }
END_TEST

START_TEST(strcspn6) { ck_assert_int_eq(strcspn(f, g), s21_strcspn(f, g)); }
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, strcspn1);
  tcase_add_test(tc1_1, strcspn2);
  tcase_add_test(tc1_1, strcspn3);
  tcase_add_test(tc1_1, strcspn4);
  tcase_add_test(tc1_1, strcspn5);
  tcase_add_test(tc1_1, strcspn6);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}