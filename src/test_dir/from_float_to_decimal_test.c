#include "test.h"

START_TEST(float_to_decimal_2) {
  float a = 123456789012345678901234567.8;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {0};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_3) {
  float a = 12345678901234567890123456.78;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {0};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_4) {
  float a = 1234567890123456789012345.678;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {0};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_5) {
  float a = 123456789012345678901234.5678;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {0};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_6) {
  float a = 12345678901234567890123.45678;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {0};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_7) {
  float a = 1234567890123456789012.345678;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {0};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_8) {
  float a = 123456789012345678901.2345678;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {0};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_9) {
  float a = 12345678901234567890.12345678;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {0};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_10) {
  float a = 1234567890123456789.012345678;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {0};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_11) {
  float a = 123456789012345678.9012345678;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {0};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_12) {
  float a = 12345678901234567.89012345678;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {0};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_13) {
  float a = 1234567890123456.7890123456780;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {0};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_16) {
  float a = 1234567890123.4567890123456780;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {0};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_17) {
  float a = 123456789012.34567890123456780;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {0};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_18) {
  float a = 12345678901.234567890123456780;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {0};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_19) {
  float a = 1234567890.1234567890123456780;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {0};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_20) {
  float a = 123456789.01234567890123456780;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {0};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_21) {
  float a = 12345678.901234567890123456780;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {0};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_31) {
  float a = 1.2e-26;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {{{0}}};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_32) {
  float a = 1.2e-25;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {{{0}}};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_33) {
  float a = 1.2e-24;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {{{0}}};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_35) {
  float a = 1.2e-22;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {{{0}}};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_39) {
  float a = 1.2e-18;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {{{0}}};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_40) {
  float a = 1.2e-17;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {{{0}}};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_41) {
  float a = 1.2e-16;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {{{0}}};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_42) {
  float a = 1.2e-15;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {{{0}}};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_49) {
  float a = 1.2e-8;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {{{0}}};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_52) {
  float a = 0.0;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {{{0}}};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_58) {
  s21_decimal val = {0};
  s21_from_float_to_decimal(1.02E+09, &val);
  ck_assert_int_eq(val.bits[0], 1020000000);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(float_to_decimal_60) {
  s21_decimal val = {0};
  float a = 1.0 / 0.0;
  s21_from_float_to_decimal(a, &val);
  ck_assert_int_eq(val.bits[0], 0);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(float_to_decimal_61) {
  s21_decimal val = {0};
  float a = -1.0 / 0.0;
  s21_from_float_to_decimal(a, &val);
  ck_assert_int_eq(val.bits[0], 0);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(float_to_decimal_62) {
  s21_decimal val = {0};
  float a = 1e-30;
  s21_from_float_to_decimal(a, &val);
  ck_assert_int_eq(val.bits[0], 0);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(float_to_decimal_63) {
  s21_decimal dec = {0};
  float tmp = 0;
  float tmp1 = 0.03;
  s21_from_float_to_decimal(tmp1, &dec);
  s21_from_decimal_to_float(dec, &tmp);
  ck_assert_float_eq_tol(tmp, tmp1, 1e-06);
}
END_TEST

START_TEST(float_to_decimal_67) {
  s21_decimal dec = {0};
  s21_from_float_to_decimal(1.02E+08, &dec);
  float tmp = 0;
  s21_from_decimal_to_float(dec, &tmp);
  ck_assert_float_eq_tol(tmp, 1.02E+08, 1e-06);
}
END_TEST

START_TEST(float_to_decimal_69) {
  s21_decimal dec = {0};
  float a = 1.0 / 0.0;
  int ret = s21_from_float_to_decimal(a, &dec);
  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(float_to_decimal_70) {
  s21_decimal dec = {0};
  float a = -1.0 / 0.0;
  s21_from_float_to_decimal(a, &dec);
  ck_assert_int_eq(dec.bits[0], 0);
  ck_assert_int_eq(dec.bits[1], 0);
  ck_assert_int_eq(dec.bits[2], 0);
  ck_assert_int_eq(dec.bits[3], 0);
}
END_TEST

START_TEST(float_to_decimal_73) {
  float f = 1.0 / 0.0;
  s21_decimal result = {0};
  s21_decimal check = {{{0, 0, 0, 0}}};
  int return_value = s21_from_float_to_decimal(f, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

Suite *suite_float_to_decimal(void) {
  Suite *s = suite_create("suite_float_to_decimal");
  TCase *tc = tcase_create("s21_tests");

  tcase_add_test(tc, float_to_decimal_2);
  tcase_add_test(tc, float_to_decimal_3);
  tcase_add_test(tc, float_to_decimal_4);
  tcase_add_test(tc, float_to_decimal_5);
  tcase_add_test(tc, float_to_decimal_6);
  tcase_add_test(tc, float_to_decimal_7);
  tcase_add_test(tc, float_to_decimal_8);
  tcase_add_test(tc, float_to_decimal_9);
  tcase_add_test(tc, float_to_decimal_10);
  tcase_add_test(tc, float_to_decimal_11);
  tcase_add_test(tc, float_to_decimal_12);
  tcase_add_test(tc, float_to_decimal_13);
  tcase_add_test(tc, float_to_decimal_16);
  tcase_add_test(tc, float_to_decimal_17);
  tcase_add_test(tc, float_to_decimal_18);
  tcase_add_test(tc, float_to_decimal_19);
  tcase_add_test(tc, float_to_decimal_20);
  tcase_add_test(tc, float_to_decimal_21);
  tcase_add_test(tc, float_to_decimal_31);
  tcase_add_test(tc, float_to_decimal_32);
  tcase_add_test(tc, float_to_decimal_33);
  tcase_add_test(tc, float_to_decimal_35);
  tcase_add_test(tc, float_to_decimal_39);
  tcase_add_test(tc, float_to_decimal_40);
  tcase_add_test(tc, float_to_decimal_41);
  tcase_add_test(tc, float_to_decimal_42);
  tcase_add_test(tc, float_to_decimal_49);
  tcase_add_test(tc, float_to_decimal_52);
  tcase_add_test(tc, float_to_decimal_58);
  tcase_add_test(tc, float_to_decimal_60);
  tcase_add_test(tc, float_to_decimal_61);
  tcase_add_test(tc, float_to_decimal_62);
  tcase_add_test(tc, float_to_decimal_63);
  tcase_add_test(tc, float_to_decimal_67);
  tcase_add_test(tc, float_to_decimal_69);
  tcase_add_test(tc, float_to_decimal_70);
  tcase_add_test(tc, float_to_decimal_73);

  suite_add_tcase(s, tc);
  return s;
}