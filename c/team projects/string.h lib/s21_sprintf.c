#include <math.h>

#include "s21_string.h"

struct spec {
  int c;
  int d;
  int f;
  int s;
  int u;
  int plus;
  int minus;
  int spase;
  int drob;
  long unsigned int width;
  int accuracy;
  long unsigned int accuracylen;
  int len_h;
  int len_l;
  int zero;
} spec;
size_t to_narrow(const wchar_t *src, char *dest);
void s21_formatSTR(char *str, const char *format, va_list p_args);
void init_options();
void itoa(char *a, long long int x);
void change_D(char *a, long double x);
int s21_sprintf(char *str, const char *format, ...) {
  str[0] = '\0';
  init_options();
  va_list var;
  va_start(var, format);

  s21_formatSTR(str, format, var);

  va_end(var);
  return (int)s21_strlen(str);
}

void s21_formatSTR(char *str, const char *format, va_list var) {
  char w[1000000] = {0};
  int j = 0;
  for (long unsigned int i = 0; i < s21_strlen(format); i++) {
    if (format[i] != '%') {
      w[j] = format[i];
      j++;

    } else {
      if (s21_strpbrk("sdcfu", &format[i]) == NULL) {
        w[j] = format[i];
        j++;
        ++i;
        continue;
      }
      init_options();
      ++i;

      while (s21_strchr("sdcfu", format[i]) == NULL) {
        if (format[i] == '-') {
          spec.minus = 1;
          ++i;
          continue;
        }
        if (format[i] == '+') {
          spec.plus = 1;
          ++i;
          continue;
        }
        if (format[i] == ' ') {
          spec.spase = 1;
          ++i;
          continue;
        }

        if (s21_strchr("0123456789", format[i]) != NULL) {
          if (format[i] == '0') {
            spec.zero = 1;
          }
          spec.width = format[i] - 48;

          ++i;
          while (s21_strchr(".sdcfuhl", format[i]) == NULL) {
            spec.width = spec.width * 10 + format[i] - 48;

            ++i;
          }
        }
        if (format[i] == '.') {
          spec.accuracy = 1;
          ++i;
          if (s21_strchr("0123456789", format[i]) != NULL) {
            spec.accuracylen = format[i] - 48;
            ++i;

            while (s21_strchr("sdcfuhl", format[i]) == NULL) {
              spec.accuracylen = spec.accuracylen * 10 + format[i] - 48;
              ++i;
            }
          }
        }
        if (format[i] == 'l') {
          spec.len_l = 1;
          ++i;
        }

        if (format[i] == 'h') {
          spec.len_h = 1;
          ++i;
        }
      }
      char p[10000] = {0};

      if (format[i] == 's') {
        spec.s = 1;
        if (spec.len_l) {
          wchar_t *l = {0};
          l = va_arg(var, wchar_t *);
          char k[1024] = "";
          to_narrow(l, k);
          if (spec.accuracy && s21_strlen(k) > spec.accuracylen) {
            s21_strncat(p, k, spec.accuracylen);
          } else {
            s21_strcat(p, k);
          }
        } else {
          char *l = NULL;
          l = va_arg(var, char *);
          if (spec.accuracy && s21_strlen(l) > spec.accuracylen) {
            s21_strncat(p, l, spec.accuracylen);
          } else {
            s21_strcat(p, l);
          }
        }
      }

      if (format[i] == 'c') {
        spec.c = 1;
        if (spec.len_l) {
          wchar_t l = 12;
          l = va_arg(var, wchar_t);
          p[0] = l;
        } else {
          char u = {0};
          u = va_arg(var, int);
          p[0] = u;
        }
      }

      if (format[i] == 'd') {
        spec.d = 1;

        if (!spec.len_h && !spec.len_l) {
          int x = 0;
          x = va_arg(var, int);
          itoa(p, x);
        }
        if (spec.len_h) {
          short int x = 0;
          x = va_arg(var, int);
          itoa(p, x);
        }
        if (spec.len_l) {
          long int x = 0;
          x = va_arg(var, long int);
          itoa(p, x);
        }

        // itoa(p,x);
      }
      if (format[i] == 'f') {
        spec.f = 1;
        double x = 0;
        x = va_arg(var, double);
        change_D(p, x);
      }
      if (format[i] == 'u') {
        spec.u = 1;

        if (!spec.len_h && !spec.len_l) {
          unsigned int x = 0;
          x = va_arg(var, unsigned int);
          itoa(p, x);
        }
        if (spec.len_h) {
          unsigned short x = 0;
          x = va_arg(var, unsigned int);
          itoa(p, x);
        }
        if (spec.len_l) {
          unsigned long int x = 0;
          x = va_arg(var, unsigned long int);
          itoa(p, x);
        }
      }
      char prob[1000] = {0};
      char zero[1000] = {0};
      long unsigned int m = 0;
      long unsigned int k = spec.width;
      if (spec.accuracylen > s21_strlen(p)) {
        while (spec.accuracylen - s21_strlen(p) > 0) {
          spec.accuracylen--;
          zero[m] = '0';
          ++m;
        }
        if (m && (p[0] == '-' || p[0] == '+' || p[0] == ' ')) {
          zero[0] = p[0];
          p[0] = '0';
          s21_strcat(zero, "0");
          spec.accuracylen = m;
          k = k - m - 1;
        }
      }

      if (spec.width > s21_strlen(p) && spec.width >= s21_strlen(zero)) {
        int o = 0;
        if (spec.len_h && !spec.u) {
          k = k - 3;
        }
        while (k - s21_strlen(p) > 0) {
          if (spec.zero)
            prob[o] = '0';
          else
            prob[o] = ' ';
          ++o;
          k--;
        }
        if (prob[0] == '0' && (p[0] == '-' || p[0] == '+' || p[0] == ' ')) {
          prob[0] = p[0];
          p[0] = '0';
        }
      }

      if (spec.minus == 0 && s21_strlen(prob) > m) {
        s21_strcat(w, prob);
        j = j + s21_strlen(prob);
      }
      if (spec.d || spec.u || spec.f) {
        s21_strcat(w, zero);
        j = j + s21_strlen(zero);
      }
      s21_strcat(w, p);
      if (spec.minus && s21_strlen(prob) > m) {
        s21_strcat(w, prob);
        j = j + s21_strlen(prob);
      }
      j = j + s21_strlen(p);  // strcat(w, p);
    }
  }
  w[s21_strlen(w) + 1] = '\0';
  // a[i++] = '\0'
  s21_strcat(str, w);
}

void init_options() {
  spec.c = 0;
  spec.d = 0;
  spec.f = 0;
  spec.s = 0;
  spec.u = 0;
  spec.minus = 0;
  spec.plus = 0;
  spec.zero = 0;
  spec.spase = 0;
  spec.width = 0;
  spec.accuracy = 0;
  spec.accuracylen = 0;
  spec.drob = 0;
  spec.len_h = 0;
  spec.len_l = 0;
}
size_t to_narrow(const wchar_t *src, char *dest) {
  size_t i;
  wchar_t code;

  i = 0;

  while (src[i] != '\0') {
    code = src[i];
    if (code < 128)
      dest[i] = (char)code;
    else {
      dest[i] = '?';
      if (code >= 0xD800 && code <= 0xD8FF) i++;
    }
    i++;
  }

  dest[i] = '\0';

  return i - 1;
}
void change_D(char *a, long double x) {
  long double sign;
  char b[1000] = {0};
  char v[1000] = {0};
  if ((sign = x) < 0) /* записываем знак */
  {
    x = -x;
  }
  long int acur = 100000;
  if (spec.accuracy) {
    acur = pow(10, spec.accuracylen);
    if (acur > 100000) acur = 100000;
  }

  if (acur < 0) {
    acur = 100000;
  }

  long long int inta = (long long int)(x * acur + 0.5) / acur;

  long double flo = x - (long long int)x;

  if (sign < 0) {
    inta = -inta;
  }
  itoa(b, inta);

  if (spec.accuracylen != 0) s21_strcat(b, ".");

  s21_strcat(a, b);
  if (flo < 0) {
    flo = -flo;
  }
  if (flo == 0 && spec.accuracylen != 0) {  // inta=round(flo);
    spec.drob = 1;
    int acuraa = acur * 10;
    while (acuraa > 1) {
      s21_strcat(a, "0");
      acuraa = acuraa / 10;
    }
  }

  else {  // inta=round(flo);
    if (spec.accuracylen != 0) {
      spec.drob = 1;

      while (flo < acur / 10) {
        flo = flo * 10;
      }
      if (5 < spec.accuracylen) {
        long long int zer = 0;
        long double fut = 0;

        zer = (int)(flo);

        fut = pow(10, spec.accuracylen - 5);

        flo = (flo * fut + 0.5);
        zer = (unsigned long)(flo);

        itoa(v, zer);
      } else
        itoa(v, (unsigned long)(flo + 0.5));
      s21_strcat(a, v);
    }
  }

  // s21_strcat(a, v);
}

void itoa(char *a, long long int x) {
  int i = 0;
  long long int sign;
  if (x == 0) {
    s21_strcat(a, "0");
  }

  if ((sign = x) < 0) /* записываем знак */
    x = -x;
  for (; x > 0;) {
    a[i] = x % 10 + '0';
    x = x / 10;
    i++;
  }
  // --i;
  if (sign < 0) {
    a[i++] = '-';
    // s21_strcat(a, "-");
  }
  if (sign > 0 && spec.plus && !spec.drob) {
    a[i++] = '+';

    // s21_strcat(a, "+");
  }
  if (sign > 0 && spec.spase && !spec.drob) {
    a[i++] = ' ';
    // s21_strcat(a, " ");
  }
  *(a + i + 1) = '\0';
  int k = i;
  char c;
  int j = 0;
  for (i = 0, j = k - 1; i < j; i++, j--) {
    c = a[i];
    a[i] = a[j];
    a[j] = c;
  }
}
