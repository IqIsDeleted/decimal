#include "test.h"

int main() {
  Suite *s = test_add();
  SRunner *sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  srunner_free(sr);

  s = test_mul();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  srunner_free(sr);

  s = test_comp();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  srunner_free(sr);

  s = other_fun_test();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  srunner_free(sr);

  s = test_div();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  srunner_free(sr);

  s = suite_from_decimal_to_float();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  srunner_free(sr);

  s = suite_from_decimal_to_int();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  srunner_free(sr);

  s = suite_float_to_decimal();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  srunner_free(sr);

  s = suite_from_int_to_decimal();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  srunner_free(sr);

  return EXIT_SUCCESS;
}
