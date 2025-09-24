#include "test.h"

START_TEST(add_min) {
  s21_decimal a = {{{1, 1, 1, 0}}}, res = {{{2, 2, 2, 0}}};

  ck_assert_int_eq(s21_add(a, a, &a), SUCCESS);
  ck_assert_int_eq(s21_is_equal(a, res), true);
}
END_TEST

START_TEST(add_two_negative_int) {
  s21_decimal a = {{{1, 1, 1, 0}}}, res = {{{2, 2, 2, 0}}};
  set_sign(&a, 1);
  set_sign(&res, 1);

  ck_assert_int_eq(s21_add(a, a, &a), SUCCESS);
  ck_assert_int_eq(s21_is_equal(a, res), true);
}
END_TEST

START_TEST(add_first_negative_int) {
  s21_decimal a = {{{3, 3, 3, 0}}}, b = {{{1, 1, 1, 0}}},
              res = {{{2, 2, 2, 0}}};
  set_sign(&a, 1);
  set_sign(&res, 1);

  ck_assert_int_eq(s21_add(a, b, &a), SUCCESS);
  ck_assert_int_eq(s21_is_equal(a, res), true);
}
END_TEST

START_TEST(add_second_negative_int) {
  s21_decimal a = {{{3, 3, 3, 0}}}, b = {{{1, 1, 1, 0}}},
              res = {{{2, 2, 2, 0}}};
  set_sign(&b, 1);

  ck_assert_int_eq(s21_add(a, b, &a), SUCCESS);
  ck_assert_int_eq(s21_is_equal(a, res), true);
}
END_TEST

START_TEST(add_diff_scale) {
  s21_decimal a = {{{1, 1, 1, 0}}}, b = {{{10, 10, 10, 0}}},
              res = {{{2, 2, 2, 0}}};
  set_scale(&b, 1);

  ck_assert_int_eq(s21_add(a, b, &a), SUCCESS);
  ck_assert_int_eq(s21_is_equal(a, res), true);
}
END_TEST

START_TEST(add_move_bits) {
  s21_decimal a = {{{1 << 31, 1, 1, 0}}}, b = {{{1 << 31, 0, 1 << 30, 0}}},
              res = {{{0, 2, 1 << 30 | 1, 0}}};

  ck_assert_int_eq(s21_add(a, b, &a), SUCCESS);
  ck_assert_int_eq(s21_is_equal(a, res), true);
}
END_TEST

START_TEST(add_overflow) {
  s21_decimal a = {{{UINT32_MAX, UINT32_MAX, UINT32_MAX, 0}}},
              b = {{{1, 0, 0, 0}}};
  ck_assert_int_eq(s21_add(a, b, &a), FAILURE);
}
END_TEST

START_TEST(add_plus_null) {
  s21_decimal a = {{{UINT32_MAX, UINT32_MAX, UINT32_MAX, 0}}},
              b = {{{0, 0, 0, 0}}};
  set_scale(&a, 1);
  set_scale(&b, 14);
  s21_decimal res = a;

  ck_assert_int_eq(s21_add(a, b, &a), SUCCESS);
  ck_assert_int_eq(s21_is_equal(a, res), true);

  b = a;
  null_decimal(&a, 3);
  ck_assert_int_eq(s21_add(a, b, &a), SUCCESS);
  ck_assert_int_eq(s21_is_equal(a, res), true);
}
END_TEST

START_TEST(sub_min) {
  s21_decimal a = {{{1, 1, 1, 0}}}, b = {{{10, 10, 10, 0}}},
              res = {{{0, 0, 0, 0}}};
  set_scale(&b, 1);
  ck_assert_int_eq(s21_sub(a, b, &a), SUCCESS);
  ck_assert_int_eq(s21_is_equal(a, res), true);
}
END_TEST

START_TEST(sub_reverse_sign) {
  s21_decimal a = {{{1, 1, 1, 0}}}, b = {{{10, 10, 10, 0}}},
              res = {{{9, 9, 9, 0}}};
  set_sign(&res, 1);
  ck_assert_int_eq(s21_sub(a, b, &a), SUCCESS);
  ck_assert_int_eq(s21_is_equal(a, res), true);
}
END_TEST

START_TEST(sub_overflow) {
  s21_decimal a = {{{UINT32_MAX, UINT32_MAX, UINT32_MAX, 0}}},
              b = {{{1, 0, 0, 0}}};
  set_sign(&a, 1);
  ck_assert_int_eq(s21_sub(a, b, &a), TOO_SMALL);
}
END_TEST

START_TEST(sub_move_bits) {
  s21_decimal a = {{{0, 1, 0, 0}}}, b = {{{1, 0, 0, 0}}},
              res = {{{UINT32_MAX, 0, 0, 0}}};
  ck_assert_int_eq(s21_sub(a, b, &a), SUCCESS);
  ck_assert_int_eq(s21_is_equal(a, res), true);
}
END_TEST

START_TEST(sub_first_negative) {
  s21_decimal a = {{{2, 0, 0, 0}}}, b = {{{6, 0, 0, 0}}},
              res = {{{8, 0, 0, 0}}};
  set_sign(&a, 1);
  set_sign(&res, 1);
  ck_assert_int_eq(s21_sub(a, b, &a), SUCCESS);
  ck_assert_int_eq(s21_is_equal(a, res), true);
}
END_TEST

START_TEST(sub_second_negative) {
  s21_decimal a = {{{2, 0, 0, 0}}}, b = {{{6, 0, 0, 0}}},
              res = {{{8, 0, 0, 0}}};
  set_sign(&b, 1);
  ck_assert_int_eq(s21_sub(a, b, &a), SUCCESS);
  ck_assert_int_eq(s21_is_equal(a, res), true);
}
END_TEST

START_TEST(sub_two_negative) {
  s21_decimal a = {{{2, 0, 0, 0}}}, b = {{{6, 0, 0, 0}}},
              res = {{{4, 0, 0, 0}}};
  set_sign(&a, 1);
  set_sign(&b, 1);
  ck_assert_int_eq(s21_sub(a, b, &a), SUCCESS);
  ck_assert_int_eq(s21_is_equal(a, res), true);
}
END_TEST

START_TEST(add_big_num_1) {
  // 79228162514264337593543950335
  s21_decimal a = {{{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}}};
  // -0.5
  s21_decimal b = {{{0x5, 0x0, 0x0, 0x80010000}}};
  // 79228162514264337593543950334
  s21_decimal res = {{{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}}};

  ck_assert_int_eq(s21_add(a, b, &a), SUCCESS);
  ck_assert_int_eq(s21_is_equal(a, res), true);
}

START_TEST(add_big_num_3) {
  // -79228162514264337593543950335
  s21_decimal a = {{{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}}};
  // -3.6336660283201536
  s21_decimal b = {{{0x811800, 0x811800, 0x0, 0x80100000}}};
  // overflow
  int check = 2;

  ck_assert_int_eq(s21_add(a, b, &a), check);
}

START_TEST(add_big_num_2) {
  // 79228162514264337593543950335
  s21_decimal a = {{{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}}};
  // 0.4999999999999999999999999999
  s21_decimal b = {{{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}}};
  // 79228162514264337593543950335
  s21_decimal res = {{{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}}};

  ck_assert_int_eq(s21_add(a, b, &a), SUCCESS);
  ck_assert_int_eq(s21_is_equal(a, res), true);
}

START_TEST(add_err) {
  s21_decimal a = {{{1, 1, 1, 0}}};

  ck_assert_int_eq(s21_add(a, a, NULL), INPUT_ERROR);
}
END_TEST

START_TEST(sub_err) {
  s21_decimal a = {{{1, 1, 1, 0}}};

  ck_assert_int_eq(s21_sub(a, a, NULL), INPUT_ERROR);
}
END_TEST

START_TEST(sub_plus_null) {
  s21_decimal a = {{{UINT32_MAX, UINT32_MAX, UINT32_MAX, 0}}},
              b = {{{0, 0, 0, 0}}};
  set_scale(&a, 1);
  set_scale(&b, 14);
  s21_decimal res = a;

  ck_assert_int_eq(s21_sub(a, b, &a), SUCCESS);
  ck_assert_int_eq(s21_is_equal(a, res), true);
}
END_TEST

Suite *test_add() {
  Suite *s = suite_create("Add_Sub");
  TCase *tcase_core = tcase_create("Add_Sub");

  tcase_add_test(tcase_core, add_min);
  tcase_add_test(tcase_core, add_first_negative_int);
  tcase_add_test(tcase_core, add_second_negative_int);
  tcase_add_test(tcase_core, add_two_negative_int);
  tcase_add_test(tcase_core, add_diff_scale);
  tcase_add_test(tcase_core, add_move_bits);
  tcase_add_test(tcase_core, add_overflow);
  tcase_add_test(tcase_core, add_big_num_3);
  tcase_add_test(tcase_core, add_plus_null);

  tcase_add_test(tcase_core, sub_min);
  tcase_add_test(tcase_core, sub_overflow);
  tcase_add_test(tcase_core, sub_move_bits);
  tcase_add_test(tcase_core, sub_two_negative);

  tcase_add_test(tcase_core, sub_reverse_sign);

  tcase_add_test(tcase_core, sub_first_negative);
  tcase_add_test(tcase_core, sub_second_negative);
  tcase_add_test(tcase_core, add_big_num_1);
  tcase_add_test(tcase_core, add_big_num_2);
  tcase_add_test(tcase_core, add_err);
  tcase_add_test(tcase_core, sub_err);
  tcase_add_test(tcase_core, sub_plus_null);

  suite_add_tcase(s, tcase_core);

  return s;
}
