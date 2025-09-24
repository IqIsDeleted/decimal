#ifndef S21_TEST
#define S21_TEST

#include <check.h>

#include "../s21_decimal.h"

#define SUCCESS 0
#define FAILURE 1
#define TOO_SMALL 2
#define DIVISION_BY_ZERO 3

Suite *test_add();
Suite *test_comp();
Suite *test_mul();
Suite *test_div();

Suite *other_fun_test();

Suite *suite_from_int_to_decimal(void);
Suite *suite_from_decimal_to_float(void);
Suite *suite_from_decimal_to_int(void);
Suite *suite_float_to_decimal(void);

void run_test(void);
void run_testcase(Suite *testcase);

#endif