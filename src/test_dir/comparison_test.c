#include "test.h"

START_TEST(equal) {
  s21_decimal a = {{{14, 13, 12, 0}}}, b = {{{14, 13, 12, 0}}};
  ck_assert_int_eq(s21_is_equal(a, b), true);
}
END_TEST

START_TEST(equal_with_sign) {
  s21_decimal a = {{{14, 13, 12, 0}}}, b = {{{14, 13, 12, 0}}};
  set_sign(&a, 1);
  ck_assert_int_eq(s21_is_equal(a, b), false);
}
END_TEST

START_TEST(equal_with_scale) {
  s21_decimal a = {{{14, 13, 12, 0}}}, b = {{{140, 130, 120, 0}}};
  set_scale(&b, 1);
  ck_assert_int_eq(s21_is_equal(a, b), true);
}
END_TEST

START_TEST(equal_with_scale_false) {
  s21_decimal a = {{{14, 13, 12, 0}}}, b = {{{141, 130, 120, 0}}};
  set_scale(&b, 1);
  ck_assert_int_eq(s21_is_equal(a, b), false);
}
END_TEST

START_TEST(equal_two_null) {
  s21_decimal a = {{{0, 0, 0, 0}}}, b = {{{0, 0, 0, 0}}};
  set_sign(&a, 1);
  ck_assert_int_eq(s21_is_equal(a, b), true);
}
END_TEST

START_TEST(less) {
  s21_decimal a = {{{0, UINT32_MAX, UINT32_MAX, 0}}}, b = {{{1, 0, 0, 0}}};
  ck_assert_int_eq(s21_is_less(a, b), false);
}
END_TEST

START_TEST(less_with_scale) {
  s21_decimal a = {{{100, 100, 100, 0}}}, b = {{{1, 1, 1, 0}}};
  set_scale(&a, 4);
  ck_assert_int_eq(s21_is_less(a, b), true);
}
END_TEST

START_TEST(less_with_sign) {
  s21_decimal a = {{{100, 100, 100, 0}}}, b = {{{1, 1, 1, 0}}};
  set_sign(&a, 1);
  ck_assert_int_eq(s21_is_less(a, b), true);
}
END_TEST

START_TEST(less_with_sign_and_scale) {
  s21_decimal a = {{{100, 100, 100, 0}}}, b = {{{1, 1, 1, 0}}};
  set_sign(&a, 1);
  set_scale(&b, 10);
  ck_assert_int_eq(s21_is_less(a, b), true);
}
END_TEST

START_TEST(greater) {
  s21_decimal a = {{{0, UINT32_MAX, UINT32_MAX, 0}}}, b = {{{1, 0, 0, 0}}};
  ck_assert_int_eq(s21_is_greater(a, b), true);
}
END_TEST

START_TEST(greater_with_scale) {
  s21_decimal a = {{{100, 100, 100, 0}}}, b = {{{1, 1, 1, 0}}};
  set_scale(&a, 4);
  ck_assert_int_eq(s21_is_greater(a, b), false);
}
END_TEST

START_TEST(greater_with_sign) {
  s21_decimal a = {{{100, 100, 100, 0}}}, b = {{{1, 1, 1, 0}}};
  set_sign(&a, 1);
  ck_assert_int_eq(s21_is_greater(a, b), false);
}
END_TEST

START_TEST(greater_with_sign_and_scale) {
  s21_decimal a = {{{100, 100, 100, 0}}}, b = {{{1, 1, 1, 0}}};
  set_sign(&a, 1);
  set_scale(&b, 10);
  ck_assert_int_eq(s21_is_greater(a, b), false);
}
END_TEST

START_TEST(less_or_equal) {
  s21_decimal a = {{{100, 100, 100, 0}}}, b = {{{1000, 1000, 1000, 0}}};
  set_scale(&b, 1);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), true);
}
END_TEST

START_TEST(less_or_equal_with_sign) {
  s21_decimal a = {{{100, 100, 100, 0}}}, b = {{{1000, 1000, 1000, 0}}};
  set_scale(&b, 1);
  set_sign(&a, 1);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), true);
}
END_TEST

START_TEST(less_or_equal_false) {
  s21_decimal a = {{{100, 100, 100, 0}}}, b = {{{1000, 1000, 1000, 0}}};
  set_scale(&b, 1);
  set_sign(&b, 1);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), false);
}
END_TEST

START_TEST(greater_or_equal) {
  s21_decimal a = {{{100, 100, 100, 0}}}, b = {{{1000, 1000, 1000, 0}}};
  set_scale(&b, 1);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), true);
}
END_TEST

START_TEST(greater_or_equal_with_sign) {
  s21_decimal a = {{{100, 100, 100, 0}}}, b = {{{1000, 1000, 1000, 0}}};
  set_scale(&b, 1);
  set_sign(&b, 1);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), true);
}
END_TEST

START_TEST(greater_or_equal_false) {
  s21_decimal a = {{{100, 100, 100, 0}}}, b = {{{1000, 1000, 1000, 0}}};
  set_scale(&b, 1);
  set_sign(&a, 1);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), false);
}
END_TEST

START_TEST(not_equal) {
  s21_decimal a = {{{14, 13, 12, 0}}}, b = {{{14, 13, 12, 0}}};
  ck_assert_int_eq(s21_is_not_equal(a, b), false);
}
END_TEST

START_TEST(not_equal_with_sign) {
  s21_decimal a = {{{14, 13, 12, 0}}}, b = {{{14, 13, 12, 0}}};
  set_sign(&a, 1);
  ck_assert_int_eq(s21_is_not_equal(a, b), true);
}
END_TEST

START_TEST(not_equal_with_scale_false) {
  s21_decimal a = {{{14, 13, 12, 0}}}, b = {{{140, 130, 120, 0}}};
  set_scale(&b, 1);
  ck_assert_int_eq(s21_is_not_equal(a, b), false);
}
END_TEST

START_TEST(not_equal_with_scale) {
  s21_decimal a = {{{14, 13, 12, 0}}}, b = {{{141, 130, 120, 0}}};
  set_scale(&b, 1);
  ck_assert_int_eq(s21_is_not_equal(a, b), true);
}
END_TEST

START_TEST(not_equal_two_null) {
  s21_decimal a = {{{0, 0, 0, 0}}}, b = {{{0, 0, 0, 0}}};
  set_sign(&a, 1);
  ck_assert_int_eq(s21_is_not_equal(a, b), false);
}
END_TEST

START_TEST(test_is_less_ok353) {
  // -52818775009509558395695966890
  s21_decimal decimal1 = {{{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}}};
  // 5281877500950955839569596689
  s21_decimal decimal2 = {{{0x11111111, 0x11111111, 0x11111111, 0x0}}};

  ck_assert_int_eq(s21_is_less(decimal1, decimal2), true);
}

START_TEST(test_is_less_ok400) {
  // -1.23000
  s21_decimal decimal1 = {{{0x1E078, 0x0, 0x0, 0x80050000}}};
  // -52818775009509558395695966890
  s21_decimal decimal2 = {{{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}}};

  ck_assert_int_eq(s21_is_less(decimal1, decimal2), false);
}

START_TEST(test_is_less_normalization_1) {
  // -0
  s21_decimal decimal1 = {{{0x0, 0x0, 0x0, 0x80000000}}};
  // 0
  s21_decimal decimal2 = {{{0x0, 0x0, 0x0, 0x0}}};

  ck_assert_int_eq(s21_is_less(decimal1, decimal2), false);
}

START_TEST(test_is_less_normalization_2) {
  // 0
  s21_decimal decimal1 = {{{0x0, 0x0, 0x0, 0x0}}};
  // -0.00000000000000
  s21_decimal decimal2 = {{{0x0, 0x0, 0x0, 0x800E0000}}};

  ck_assert_int_eq(s21_is_less(decimal1, decimal2), false);
}

START_TEST(test_is_less_normalization_3) {
  // -0.00000000000000
  s21_decimal decimal1 = {{{0x0, 0x0, 0x0, 0x800E0000}}};
  // 0
  s21_decimal decimal2 = {{{0x0, 0x0, 0x0, 0x0}}};

  ck_assert_int_eq(s21_is_less(decimal1, decimal2), false);
}

Suite *test_comp() {
  Suite *s = suite_create("Comparison");
  TCase *tcase_core = tcase_create("Comparison");

  tcase_add_test(tcase_core, equal);
  tcase_add_test(tcase_core, equal_with_sign);
  tcase_add_test(tcase_core, equal_with_scale);
  tcase_add_test(tcase_core, equal_with_scale_false);
  tcase_add_test(tcase_core, less);
  tcase_add_test(tcase_core, less_with_scale);
  tcase_add_test(tcase_core, less_with_sign);
  tcase_add_test(tcase_core, less_with_sign_and_scale);
  tcase_add_test(tcase_core, greater);
  tcase_add_test(tcase_core, greater_with_scale);
  tcase_add_test(tcase_core, greater_with_sign);
  tcase_add_test(tcase_core, greater_with_sign_and_scale);
  tcase_add_test(tcase_core, less_or_equal);
  tcase_add_test(tcase_core, less_or_equal_with_sign);
  tcase_add_test(tcase_core, less_or_equal_false);
  tcase_add_test(tcase_core, greater_or_equal);
  tcase_add_test(tcase_core, greater_or_equal_with_sign);
  tcase_add_test(tcase_core, greater_or_equal_false);
  tcase_add_test(tcase_core, not_equal);
  tcase_add_test(tcase_core, not_equal_with_sign);
  tcase_add_test(tcase_core, not_equal_with_scale_false);
  tcase_add_test(tcase_core, not_equal_with_scale);
  tcase_add_test(tcase_core, equal_two_null);
  tcase_add_test(tcase_core, not_equal_two_null);
  tcase_add_test(tcase_core, test_is_less_ok353);
  tcase_add_test(tcase_core, test_is_less_ok400);
  tcase_add_test(tcase_core, test_is_less_normalization_1);
  tcase_add_test(tcase_core, test_is_less_normalization_2);
  tcase_add_test(tcase_core, test_is_less_normalization_3);

  suite_add_tcase(s, tcase_core);

  return s;
}