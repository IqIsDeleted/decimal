#include "s21_decimal.h"

/*
Return value:
0 — FALSE;
1 — TRUE.
*/
int s21_is_equal(s21_decimal a, s21_decimal b) {
  normalization(&a, &b);  // ???
  return (get_sign(a) == get_sign(b) && a.bits[0] == b.bits[0] &&
          a.bits[1] == b.bits[1] && a.bits[2] == b.bits[2]);
}

int s21_is_less(s21_decimal a, s21_decimal b) {
  return (__builtin_comparison_fun(a, b) == -1);
}

int s21_is_less_or_equal(s21_decimal a, s21_decimal b) {
  return (__builtin_comparison_fun(a, b) <= 0);
}

int s21_is_greater(s21_decimal a, s21_decimal b) {
  return (__builtin_comparison_fun(a, b) == 1);
}

int s21_is_greater_or_equal(s21_decimal a, s21_decimal b) {
  return (__builtin_comparison_fun(a, b) >= 0);
}

int s21_is_not_equal(s21_decimal a, s21_decimal b) {
  normalization(&a, &b);  // ???
  return !(get_sign(a) == get_sign(b) && a.bits[0] == b.bits[0] &&
           a.bits[1] == b.bits[1] && a.bits[2] == b.bits[2]);
}
