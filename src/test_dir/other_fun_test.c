#include "test.h"

///////////////////////////////////////////////////////////////////////////////
// Тесты _________s21_floor_____________
///////////////////////////////////////////////////////////////////////////////
START_TEST(s21_floor1) {  // тест с маленьким числом
  s21_decimal a = {{{87752, 0, 0, 0}}};
  set_sign(&a, 1);
  set_scale(&a, 1);
  s21_decimal res = {{{8776, 0, 0, 0}}};
  set_sign(&res, 1);

  ck_assert_int_eq(s21_floor(a, &a), SUCCESS);
  ck_assert_int_eq(s21_is_equal(a, res), true);
}
END_TEST

START_TEST(s21_floor2) {  // тест с маленьким числом
  s21_decimal a = {{{87752, 0, 0, 0}}};
  set_scale(&a, 1);
  s21_decimal res = {{{8775, 0, 0, 0}}};

  ck_assert_int_eq(s21_floor(a, &a), SUCCESS);
  ck_assert_int_eq(s21_is_equal(a, res), true);
}
END_TEST

START_TEST(s21_floor3) {  // тест когда число становится меньше 0
  s21_decimal a = {{{87752, 0, 0, 0}}};
  set_scale(&a, 5);
  set_sign(&a, 1);
  s21_decimal res = {{{1, 0, 0, 0}}};
  set_sign(&res, 1);

  ck_assert_int_eq(s21_floor(a, &a), SUCCESS);
  ck_assert_int_eq(s21_is_equal(a, res), true);
}
END_TEST

START_TEST(s21_floor4) {  // тест когда число становится меньше 0
  s21_decimal a = {{{87752, 0, 0, 0}}};
  set_scale(&a, 5);
  s21_decimal res = {{{0, 0, 0, 0}}};
  ck_assert_int_eq(s21_floor(a, &a), SUCCESS);
  ck_assert_int_eq(s21_is_equal(a, res), true);
}
END_TEST

START_TEST(s21_floor5) {  // большое число
  s21_decimal a = {{{2147483648, 1, 1, 0}}};
  set_scale(&a, 1);
  set_sign(&a, 1);
  s21_decimal res = {{{3221225472, 429496729, 0, 0}}};
  set_sign(&res, 1);

  ck_assert_int_eq(s21_floor(a, &a), SUCCESS);
  ck_assert_int_eq(s21_is_equal(a, res), true);
}
END_TEST

START_TEST(s21_floor6) {  // код ошибки
  s21_decimal a = {{{2147483648, 1, 1, 0}}};
  set_scale(&a, 29);
  set_sign(&a, 1);
  ck_assert_int_eq(s21_floor(a, &a), FAILURE);
}
END_TEST

START_TEST(s21_floor7) {  // scale 0
  s21_decimal a = {{{87752, 0, 0, 0}}};
  s21_decimal res = {{{87752, 0, 0, 0}}};

  ck_assert_int_eq(s21_floor(a, &a), SUCCESS);
  ck_assert_int_eq(s21_is_equal(a, res), true);
}
END_TEST

START_TEST(s21_floor8) {  // scale 0
  s21_decimal a = {{{87752, 0, 0, 0}}};
  set_sign(&a, 1);
  s21_decimal res = {{{87752, 0, 0, 0}}};
  set_sign(&res, 1);
  ck_assert_int_eq(s21_floor(a, &a), SUCCESS);
  ck_assert_int_eq(s21_is_equal(a, res), true);
}
END_TEST

START_TEST(s21_floor9) {  // result = NULL

  s21_decimal a = {{{2147483648, 1, 1, 0}}};

  ck_assert_int_eq(s21_floor(a, NULL), FAILURE);
}
END_TEST
///////////////////////////////////////////////////////////////////////////////
// Тесты _________s21_round_____________
///////////////////////////////////////////////////////////////////////////////
START_TEST(s21_round1) {  // округление > 5
  s21_decimal a = {{{87758, 0, 0, 0}}};
  set_sign(&a, 1);
  set_scale(&a, 1);
  s21_decimal res = {{{8776, 0, 0, 0}}};
  set_sign(&res, 1);
  ck_assert_int_eq(s21_round(a, &a), SUCCESS);
  ck_assert_int_eq(s21_is_equal(a, res), true);
}
END_TEST

START_TEST(s21_round2) {  // округление < 5
  s21_decimal a = {{{87752, 0, 0, 0}}};
  set_scale(&a, 1);
  s21_decimal res = {{{8775, 0, 0, 0}}};
  ck_assert_int_eq(s21_round(a, &a), SUCCESS);
  ck_assert_int_eq(s21_is_equal(a, res), true);
}
END_TEST

START_TEST(s21_round3) {  // округление = 5
  s21_decimal a = {{{87745, 0, 0, 0}}};
  set_scale(&a, 1);
  s21_decimal res = {{{8774, 0, 0, 0}}};
  ck_assert_int_eq(s21_round(a, &a), SUCCESS);
  ck_assert_int_eq(s21_is_equal(a, res), true);
}
END_TEST

START_TEST(s21_round4) {  // округление = 5
  s21_decimal a = {{{87755, 0, 0, 0}}};
  set_scale(&a, 1);
  s21_decimal res = {{{8776, 0, 0, 0}}};
  ck_assert_int_eq(s21_round(a, &a), SUCCESS);
  ck_assert_int_eq(s21_is_equal(a, res), true);
}
END_TEST

START_TEST(s21_round5) {  // число становится меньше 0
  s21_decimal a = {{{87755, 0, 0, 0}}};
  set_scale(&a, 5);
  s21_decimal res = {{{1, 0, 0, 0}}};
  ck_assert_int_eq(s21_round(a, &a), SUCCESS);
  ck_assert_int_eq(s21_is_equal(a, res), true);
}
END_TEST

START_TEST(s21_round6) {  // число становится меньше 0
  s21_decimal a = {{{87755, 0, 0, 0}}};
  set_scale(&a, 6);
  s21_decimal res = {{{0, 0, 0, 0}}};
  ck_assert_int_eq(s21_round(a, &a), SUCCESS);
  ck_assert_int_eq(s21_is_equal(a, res), true);
}
END_TEST

START_TEST(s21_round7) {  // большое число
  s21_decimal a = {{{2151956480, 4260097, 67375105, 0}}};
  set_scale(&a, 5);
  set_sign(&a, 1);
  s21_decimal res = {{{1124315109, 3225735230, 673, 0}}};
  set_sign(&res, 1);
  ck_assert_int_eq(s21_round(a, &a), SUCCESS);
  ck_assert_int_eq(s21_is_equal(a, res), true);
}
END_TEST

START_TEST(s21_round8) {  // код ошибки
  s21_decimal a = {{{2151956480, 4260097, 67375105, 0}}};
  set_scale(&a, 29);
  set_sign(&a, 1);
  ck_assert_int_eq(s21_round(a, &a), FAILURE);
}
END_TEST

START_TEST(s21_round9) {  // scale = 0
  s21_decimal a = {{{87755, 0, 0, 0}}};
  s21_decimal res = {{{87755, 0, 0, 0}}};
  ck_assert_int_eq(s21_round(a, &a), SUCCESS);
  ck_assert_int_eq(s21_is_equal(a, res), true);
}
END_TEST

START_TEST(s21_round10) {  // result = NULL
  s21_decimal a = {{{87755, 0, 0, 0}}};
  ck_assert_int_eq(s21_round(a, NULL), FAILURE);
}
END_TEST

///////////////////////////////////////////////////////////////////////////////
//// Тесты _________s21_truncate_____________
///////////////////////////////////////////////////////////////////////////////

START_TEST(s21_truncate1) {
  s21_decimal a = {{{87758, 0, 0, 0}}};
  set_scale(&a, 1);
  set_sign(&a, 1);
  s21_decimal res = {{{8775, 0, 0, 0}}};
  set_sign(&res, 1);
  ck_assert_int_eq(s21_truncate(a, &a), SUCCESS);
  ck_assert_int_eq(s21_is_equal(a, res), true);
}
END_TEST

START_TEST(s21_truncate2) {
  s21_decimal a = {{{87758, 0, 0, 0}}};
  set_scale(&a, 3);
  s21_decimal res = {{{87, 0, 0, 0}}};
  ck_assert_int_eq(s21_truncate(a, &a), SUCCESS);
  ck_assert_int_eq(s21_is_equal(a, res), true);
}
END_TEST

START_TEST(s21_truncate3) {  // большое число
  s21_decimal a = {{{2420392072, 273238289, 71569409, 0}}};
  set_scale(&a, 7);
  set_sign(&a, 1);
  s21_decimal res = {{{981981378, 674056060, 7, 0}}};
  set_sign(&res, 1);
  ck_assert_int_eq(s21_truncate(a, &a), SUCCESS);
  ck_assert_int_eq(s21_is_equal(a, res), true);
}
END_TEST

START_TEST(s21_truncate4) {  // число меньше 0
  s21_decimal a = {{{87758, 0, 0, 0}}};
  set_scale(&a, 5);
  s21_decimal res = {{{0, 0, 0, 0}}};
  ck_assert_int_eq(s21_truncate(a, &a), SUCCESS);
  ck_assert_int_eq(s21_is_equal(a, res), true);
}
END_TEST

START_TEST(s21_truncate5) {  // код ошибки
  s21_decimal a = {{{87758, 0, 0, 0}}};
  set_scale(&a, 29);

  ck_assert_int_eq(s21_truncate(a, &a), FAILURE);
}
END_TEST

START_TEST(s21_truncate6) {  // scale = 0
  s21_decimal a = {{{87758, 87758, 87758, 0}}};
  s21_decimal res = {{{87758, 87758, 87758, 0}}};
  ck_assert_int_eq(s21_truncate(a, &a), SUCCESS);
  ck_assert_int_eq(s21_is_equal(a, res), true);
}
END_TEST

START_TEST(s21_truncate7) {  // result = NULL
  s21_decimal a = {{{87758, 87758, 87758, 0}}};
  ck_assert_int_eq(s21_truncate(a, NULL), FAILURE);
}
END_TEST
///////////////////////////////////////////////////////////////////////////////
//// Тесты _________s21_negate_____________
///////////////////////////////////////////////////////////////////////////////

START_TEST(s21_negate1) {
  s21_decimal a = {{{87758, 0, 0, 0}}};
  set_scale(&a, 5);

  s21_decimal res = {{{87758, 0, 0, 0}}};
  set_scale(&res, 5);
  set_sign(&res, 1);

  ck_assert_int_eq(s21_negate(a, &a), SUCCESS);
  ck_assert_int_eq(s21_is_equal(a, res), true);
}
END_TEST

START_TEST(s21_negate2) {
  s21_decimal a = {{{0, 0, 0, 0}}};
  set_scale(&a, 7);
  set_sign(&a, 1);

  s21_decimal res = {{{0, 0, 0, 0}}};
  set_scale(&res, 7);

  ck_assert_int_eq(s21_negate(a, &a), SUCCESS);
  ck_assert_int_eq(s21_is_equal(a, res), true);
}
END_TEST

START_TEST(s21_negate3) {  // result = NULL
  s21_decimal a = {{{0, 0, 0, 0}}};
  set_scale(&a, 7);
  set_sign(&a, 1);

  ck_assert_int_eq(s21_negate(a, NULL), FAILURE);
}
END_TEST

// Функция создания набора тестов.
Suite *other_fun_test() {
  Suite *suite = suite_create("Other");
  // Набор разбивается на группы тестов, разделённых по каким-либо критериям.
  TCase *tcase_core = tcase_create("Other");
  //___________________START_________________
  // Тесты _______other_functions____________
  // Тесты ____________FLOOR_________________
  tcase_add_test(tcase_core, s21_floor1);
  tcase_add_test(tcase_core, s21_floor2);
  tcase_add_test(tcase_core, s21_floor3);
  tcase_add_test(tcase_core, s21_floor4);
  tcase_add_test(tcase_core, s21_floor5);
  tcase_add_test(tcase_core, s21_floor6);
  tcase_add_test(tcase_core, s21_floor7);
  tcase_add_test(tcase_core, s21_floor8);
  tcase_add_test(tcase_core, s21_floor9);
  ///________________________________________
  // Тесты ____________ROUND_________________
  tcase_add_test(tcase_core, s21_round1);
  tcase_add_test(tcase_core, s21_round2);
  tcase_add_test(tcase_core, s21_round3);
  tcase_add_test(tcase_core, s21_round4);
  tcase_add_test(tcase_core, s21_round5);
  tcase_add_test(tcase_core, s21_round6);
  tcase_add_test(tcase_core, s21_round7);
  tcase_add_test(tcase_core, s21_round8);
  tcase_add_test(tcase_core, s21_round9);
  tcase_add_test(tcase_core, s21_round10);
  ///________________________________________
  // Тесты ____________TRUNCATE______________
  tcase_add_test(tcase_core, s21_truncate1);
  tcase_add_test(tcase_core, s21_truncate2);
  tcase_add_test(tcase_core, s21_truncate3);
  tcase_add_test(tcase_core, s21_truncate4);
  tcase_add_test(tcase_core, s21_truncate5);
  tcase_add_test(tcase_core, s21_truncate6);
  tcase_add_test(tcase_core, s21_truncate7);
  ///________________________________________
  // Тесты ____________NEGATE________________
  tcase_add_test(tcase_core, s21_negate1);
  tcase_add_test(tcase_core, s21_negate2);
  tcase_add_test(tcase_core, s21_negate3);
  suite_add_tcase(suite, tcase_core);

  return suite;
}
