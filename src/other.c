#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  unsigned char scale = value.parts.flags.scale;
  bool fractonal_part = false;
  int error_code = valid_data_for_round(value, result);

  if (error_code == 0) {
    null_decimal(result, 4);
    copying_decimal(value, result);
    for (int i = 0; i < scale && scale != 0; i++) {
      int temp = div_by_10(result, 3);
      temp != 0 ? fractonal_part = true : 0;
    }
    if (value.parts.flags.sign && fractonal_part) {
      add_one(result);
    }
    result->parts.flags.scale = 0;
  } else {
    error_code = 1;
  }
  return error_code;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  unsigned char scale = value.parts.flags.scale;
  int fractonal_part = 0;
  int error_code = valid_data_for_round(value, result);
  int rnd = 0;

  if (error_code == 0) {
    null_decimal(result, 4);
    copying_decimal(value, result);
    for (int i = 0; i < scale && scale != 0; i++) {
      fractonal_part = div_by_10(result, 3);
      rnd += fractonal_part;
    }
    if (fractonal_part > 5) {
      add_one(result);
    } else if (fractonal_part == 5) {
      if (result->bits[0] % 2 != 0 || rnd != 5) {
        add_one(result);
      }
    }
    result->parts.flags.scale = 0;
  } else {
    error_code = 1;
  }
  return error_code;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  unsigned char scale = value.parts.flags.scale;
  int error_code = valid_data_for_round(value, result);

  if (error_code == 0) {
    null_decimal(result, 4);
    copying_decimal(value, result);
    for (int i = 0; i < scale && scale != 0; i++) {
      div_by_10(result, 3);
    }
    result->parts.flags.scale = 0;
  } else {
    error_code = 1;
  }
  return error_code;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  int res = valid_data_for_round(value, result);

  if (res == 0) {
    null_decimal(result, 4);
    *result = value;
    result->parts.flags.sign = value.parts.flags.sign ^ 1;
    res = 0;
  }

  return res;
}