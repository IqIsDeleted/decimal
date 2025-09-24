#include "test.h"

START_TEST(one_bits_div) {
  s21_decimal a = {{{3, 0, 0, 0}}}, b = {{{40, 0, 0, 0}}};
  s21_decimal res = {{{75, 0, 0, 0}}};
  set_scale(&res, 4);

  ck_assert_int_eq(s21_div(a, b, &a), SUCCESS);
  ck_assert_int_eq(s21_is_equal(a, res), SUCCESS);
}
END_TEST

START_TEST(div_err) {
  s21_decimal a = {{{3, 0, 0, 0}}}, b = {{{3, 4, 5, 0}}};

  ck_assert_int_ne(s21_div(a, a, NULL), SUCCESS);
  set_scale(&b, 29);
  ck_assert_int_ne(s21_div(b, a, NULL), SUCCESS);
}
END_TEST

START_TEST(div_error_scale_29) {
  s21_decimal a = {{{3, 0, 0, 0}}};
  set_scale(&a, 29);

  ck_assert_int_ne(s21_div(a, a, NULL), SUCCESS);
}
END_TEST

START_TEST(div_by_zero) {
  s21_decimal a = {{{3, 0, 0, 0}}}, b = {{{0, 0, 0, 0}}};
  set_scale(&b, 27);
  set_sign(&b, 1);

  ck_assert_int_eq(s21_div(a, b, &a), DIVISION_BY_ZERO);
}
END_TEST

Suite *test_div() {
  Suite *s = suite_create("Div");
  TCase *tcase_core = tcase_create("Div");

  tcase_add_test(tcase_core, one_bits_div);
  tcase_add_test(tcase_core, div_err);
  tcase_add_test(tcase_core, div_error_scale_29);
  tcase_add_test(tcase_core, div_by_zero);

  suite_add_tcase(s, tcase_core);

  return s;
}
