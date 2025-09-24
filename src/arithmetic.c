#include "s21_decimal.h"

void sign_calculation(s21_decimal *a, s21_decimal *b, big_dec_t *res) {
  res->flags.sign = a->parts.flags.sign ^ b->parts.flags.sign;
  a->parts.flags.sign = 0;
  b->parts.flags.sign = 0;
}

void sub_for_div(big_dec_t a, big_dec_t b, big_dec_t *res) {
  int borrow = 0;
  for (int i = 0; i < BIG_DEC_LEN; ++i) {
    res->bits[i] = a.bits[i] - b.bits[i] - borrow;
    borrow = !!(a.bits[i] < b.bits[i] + borrow);
  }
}

/*
0 — OK;
1 — the number is too large or equal to infinity;
2 — the number is too small or equal to negative infinity;
3 — division by 0.
*/
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int ret = 0;
  big_dec_t a = from_dec_to_big(value_1), b = from_dec_to_big(value_2);
  big_dec_t tmp_res = {{0ul}, {0}};

  if (valid_data_for_arithmetic(value_1, value_2, result)) {
    null_decimal(result, 4);

    if (!is_null(value_2)) {
      sign_calculation(&value_1, &value_2, &tmp_res);
      a.flags.sign = 0;
      b.flags.sign = 0;
      div_processing(a, b, &tmp_res);

      ret = from_big_to_dec(result, &tmp_res);
      ret <<= tmp_res.flags.sign & ret;

    } else {
      ret = 3;
    }

  } else {
    ret = INPUT_ERROR;
  }

  return ret;
}

void div_processing(big_dec_t a, big_dec_t b, big_dec_t *tmp_res) {
  while (!big_is_null(a) && tmp_res->flags.scale <= 28) {
    if (comparison_of_two_big(a, b) > -1) {
      sub_for_div(a, b, &a);
      big_plus_x(tmp_res, 1);

    } else {
      mul_by_10_for_big(&a);
      mul_by_10_for_big(tmp_res);
      tmp_res->flags.scale += 1;
    }
  }
}

/*
0 — OK;
1 — the number is too large or equal to infinity;
2 — the number is too small or equal to negative infinity.
*/
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int ret = 0;
  big_dec_t a = from_dec_to_big(value_1), b = from_dec_to_big(value_2);
  if (valid_data_for_arithmetic(value_1, value_2, result)) {
    if (is_null(value_1) || is_null(value_2)) {
      *result = is_null(value_1) ? value_2 : value_1;
      ret = 0;
    } else {
      set_sign(&value_1, 0);
      set_sign(&value_2, 0);
      ret = sub_or_add(ADD) ? subtraction() : addition();
    }
  } else
    ret = INPUT_ERROR;

  return ret;
}

/*
0 — OK;
1 — the number is too large or equal to infinity;
2 — the number is too small or equal to negative infinity.
*/
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int ret = 0;
  if (valid_data_for_arithmetic(value_1, value_2, result)) {
    big_dec_t a = from_dec_to_big(value_1), b = from_dec_to_big(value_2);
    if (is_null(value_1) || is_null(value_2)) {
      *result = is_null(value_1) ? value_2 : value_1;

      result->parts.flags.sign =
          is_null(value_1) ? get_sign(value_2) ^ SUB : get_sign(value_1);
      ret = 0;
    } else {
      set_sign(&value_1, 0);
      set_sign(&value_2, 0);
      ret = sub_or_add(SUB) ? subtraction() : addition();
    }
  } else
    ret = INPUT_ERROR;

  return ret;
}

/*
0 — OK;
1 — the number is too large or equal to infinity;
2 — the number is too small or equal to negative infinity.
*/
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int ret = 0;
  big_dec_t tmp = {{0ul}, {0}};

  if (valid_data_for_arithmetic(value_1, value_2, result)) {
    null_decimal(result, 4);
    sign_calculation(&value_1, &value_2, &tmp);
    tmp.flags.scale = get_scale(value_1) + get_scale(value_2);

    mul_processing(value_1, value_2, &tmp);

    ret = from_big_to_dec(result, &tmp);
    ret <<= tmp.flags.sign & ret;

  } else {
    ret = INPUT_ERROR;
  }

  return ret;
}

void mul_processing(s21_decimal value_1, s21_decimal value_2, big_dec_t *tmp) {
  for (int i = 0; i < 3; ++i) {
    uint64_t a = value_1.bits[i];
    for (int j = 0; j < 3; ++j) {
      uint64_t b = value_2.bits[j];
      tmp->bits[i + j] += a * b;
    }
  }

  tmp->bits[1] += tmp->bits[0] >> 32;
  tmp->bits[0] &= UINT32_MAX;
  for (int i = 1; i < 5; ++i) {
    tmp->bits[i + 1] += tmp->bits[i] >> 32;
    tmp->bits[i] &= UINT32_MAX;
    tmp->bits[i / 2] |= tmp->bits[i] << (32 * (i & 1));
    tmp->bits[i] = 0ul;
  }
}
