#include "test.h"

START_TEST(mul_overflow) {
  s21_decimal a = {{{1, 1, 1, 0}}};

  ck_assert_int_eq(s21_mul(a, a, &a), FAILURE);
}
END_TEST

START_TEST(mul) {
  s21_decimal a = {{{UINT32_MAX, 0, 0, 0}}}, b = {{{2, 0, 0, 0}}},
              res = {{{UINT32_MAX - 1, 1, 0, 0}}};

  ck_assert_int_eq(s21_mul(a, b, &a), SUCCESS);
  ck_assert_int_eq(s21_is_equal(a, res), true);
}
END_TEST

START_TEST(mul_two_float) {
  s21_decimal a = {{{1, 0, 0, 0}}}, b = {{{2, 0, 0, 0}}},
              res = {{{2, 0, 0, 0}}};
  set_scale(&a, 1);
  set_scale(&b, 2);
  set_scale(&res, 3);
  ck_assert_int_eq(s21_mul(a, b, &a), SUCCESS);
  ck_assert_int_eq(s21_is_equal(a, res), true);
}
END_TEST

START_TEST(mul_overflow_2) {
  s21_decimal a = {{{3, 5, 2, 0}}}, b = {{{2, 5, 0, 0}}};
  set_sign(&b, 1);

  ck_assert_int_eq(s21_mul(a, b, &a), TOO_SMALL);
}
END_TEST

START_TEST(big_number) {
  s21_decimal a = {{{3, 5, 0, 0}}}, b = {{{2, 4, 0, 0}}},
              res = {{{6, 22, 20, 0}}};

  ck_assert_int_eq(s21_mul(a, b, &a), SUCCESS);
  ck_assert_int_eq(s21_is_equal(a, res), true);
}
END_TEST

START_TEST(diff_sign_mul) {
  s21_decimal a = {{{1, 1, 0, 0}}}, b = {{{1, 1, 0, 0}}},
              res = {{{1, 2, 1, 0}}};
  set_sign(&a, 1);
  set_sign(&res, 1);

  ck_assert_int_eq(s21_mul(a, b, &a), SUCCESS);
  ck_assert_int_eq(s21_is_equal(a, res), true);
}
END_TEST

START_TEST(max_dec_mul) {
  s21_decimal a = {{{UINT32_MAX, UINT32_MAX, UINT32_MAX, 0}}},
              b = {{{1, 0, 0, 0}}},
              res = {{{UINT32_MAX, UINT32_MAX, UINT32_MAX, 0}}};

  ck_assert_int_eq(s21_mul(a, b, &a), SUCCESS);
  ck_assert_int_eq(s21_is_equal(a, res), true);
}
END_TEST

START_TEST(mul_inf) {
  s21_decimal a = {{{UINT32_MAX, UINT32_MAX, UINT32_MAX, 0}}},
              b = {{{2, 0, 0, 0}}};

  ck_assert_int_eq(s21_mul(a, b, &a), FAILURE);
}
END_TEST

START_TEST(mul_negative_inf) {
  s21_decimal a = {{{UINT32_MAX, UINT32_MAX, UINT32_MAX, 0}}},
              b = {{{2, 0, 0, 0}}};
  set_sign(&a, 1);

  ck_assert_int_eq(s21_mul(a, b, &a), 2);
}
END_TEST

START_TEST(mul_too_small_res) {
  s21_decimal a = {{{1, 0, 0, 0}}}, b = {{{1, 0, 0, 0}}};
  set_sign(&a, 1);
  set_scale(&a, 28);
  set_scale(&b, 28);

  ck_assert_int_eq(s21_mul(a, b, &a), TOO_SMALL);
}
END_TEST

START_TEST(mul_scale_28) {
  s21_decimal a = {{{UINT32_MAX, UINT32_MAX, UINT32_MAX, 0}}},
              b = {{{0, 0, 0, 0}}}, res = {{{0, 0, 0, 0}}};
  set_scale(&a, 14);
  set_scale(&b, 14);
  set_scale(&res, 28);

  ck_assert_int_eq(s21_mul(a, b, &a), SUCCESS);
  ck_assert_int_eq(s21_is_equal(a, res), true);
}
END_TEST

START_TEST(mul_err) {
  s21_decimal a = {{{UINT32_MAX, UINT32_MAX, UINT32_MAX, 0}}},
              b = {{{0, 0, 0, 0}}};
  set_scale(&a, 29);
  set_scale(&b, 14);

  ck_assert_int_ne(s21_mul(a, b, &a), SUCCESS);
  ck_assert_int_ne(s21_mul(a, b, NULL), SUCCESS);
}
END_TEST

Suite *test_mul() {
  Suite *s = suite_create("Mul");
  TCase *tcase_core = tcase_create("Mul");

  tcase_add_test(tcase_core, mul_overflow);
  tcase_add_test(tcase_core, mul);
  tcase_add_test(tcase_core, mul_two_float);
  tcase_add_test(tcase_core, mul_overflow_2);
  tcase_add_test(tcase_core, big_number);
  tcase_add_test(tcase_core, diff_sign_mul);
  tcase_add_test(tcase_core, max_dec_mul);
  tcase_add_test(tcase_core, mul_inf);
  tcase_add_test(tcase_core, mul_negative_inf);
  tcase_add_test(tcase_core, mul_too_small_res);
  tcase_add_test(tcase_core, mul_scale_28);
  tcase_add_test(tcase_core, mul_err);

  suite_add_tcase(s, tcase_core);

  return s;
}
