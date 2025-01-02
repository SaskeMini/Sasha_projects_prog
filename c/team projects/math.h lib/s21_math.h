#ifndef SRC_S21_MATH_H_
#define SRC_S21_MATH_H_

#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define S21_EPS 1e-25
#define S21_PI 3.141592653589793
#define S21_E 2.718281828459045
#define s21_LN10 2.3025850929940456840179914546843642
#define s21_PLUS_INF 1. / 0.
#define s21_MINUS_INF -1. / 0.
#define s21_NAN 0. / 0.

#define S21_INF __builtin_inf()
#define S21_NAN __builtin_nan("")
#define s21_is_inf __builtin_isinf
#define s21_is_nan __builtin_isnan

long double s21_sin(double x);   //| вычисляет синус |
long double s21_cos(double x);   //| вычисляет косинус |
long double s21_tan(double x);   // | вычисляет тангенс |
long double s21_atan(double x);  // | вычисляет арктангенс |
long double s21_asin(double x);  //| вычисляет арксинус |
long double s21_acos(double x);  //| вычисляет арккосинус |
long double s21_ceil(double x);  // | возвращает ближайшее целое число, не
                                 // меньшее заданного значения |
long double s21_exp(
    double x);  //| возвращает значение e, возведенное в заданную степень |
long double s21_fabs(
    double x);  //| вычисляет абсолютное значение числа с плавающей точкой |
int s21_abs(int x);  //| вычисляет абсолютное значение целого числа |
long double s21_floor(double x);  //| возвращает ближайшее целое число, не
                                  //превышающее заданное значение |
long double s21_fmod(
    double x, double y);  //| остаток операции деления с плавающей точкой |
long double s21_log(double x);  // | вычисляет натуральный логарифм |
long double s21_pow(double base,
                    double exp);  // | возводит число в заданную степень |
long double s21_sqrt(double x);  // | вычисляет квадратный корень |

#endif  //  SRC_S21_MATH_H_
