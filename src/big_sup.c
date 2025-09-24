#include "s21_decimal.h"

int big_sub_or_add(big_dec_t *a, big_dec_t *b, s21_decimal *result,
                   uint8_t operation, int comparison) {
  uint8_t buff_sign_b = big_get_sign(*b) ^ operation,
          buff_sign_a = big_get_sign(*a);
  operation = (buff_sign_a ^ buff_sign_b) & 1;
  big_set_sign(a, 0);
  big_set_sign(b, 0);
  null_decimal(result, 4);
  big_normalization(a, b);
  if (operation && comparison == -1) {
    big_swap_decimal(a, b);
    result->parts.flags.sign = buff_sign_a ^ 1;
  } else if (comparison == 1) {
    result->parts.flags.sign = buff_sign_a;
  }
  big_set_sign(a, buff_sign_a);
  big_set_sign(b, buff_sign_b);

  return operation;
}

int big_add(big_dec_t a, big_dec_t b, s21_decimal *result) {
  uint64_t tmp_low = 0ul;
  uint64_t tmp_upp = 0ul;
  uint32_t carry = 0;
  big_dec_t tmp_res = {{0ul}, {0}};
  tmp_res.flags.scale = a.flags.scale;
  tmp_res.flags.sign = big_get_sign(a) && big_get_sign(b);

  for (int i = 0; i < BIG_DEC_LEN; ++i) {
    uint64_t lower = a.bits[i] & UINT32_MAX;
    uint64_t upper = a.bits[i] >> 32;
    uint64_t lower_b = b.bits[i] & UINT32_MAX;
    uint64_t upper_b = b.bits[i] >> 32;

    tmp_low = lower + lower_b + carry;
    tmp_upp = upper + upper_b + (tmp_low >> 32);
    tmp_low &= UINT32_MAX;
    tmp_res.bits[i] = tmp_low + (tmp_upp << 32);
    carry = tmp_upp >> 32;
  }

  return ((carry || from_big_to_dec(result, &tmp_res)) << get_sign(*result));
}

int big_sub(big_dec_t a, big_dec_t b, s21_decimal *result) {
  big_dec_t tmp_res = {{0ul}, {0}};
  tmp_res.flags.scale = a.flags.scale;

  int borrow = 0;
  for (int i = 0; i < BIG_DEC_LEN; ++i) {
    tmp_res.bits[i] = a.bits[i] - b.bits[i] - borrow;
    borrow = !!(a.bits[i] < b.bits[i] + borrow);
  }
  return (from_big_to_dec(result, &tmp_res) << get_sign(*result));
}

void big_plus_x(big_dec_t *num, int x) {
  uint64_t carry = x;
  for (int i = 0; i < BIG_DEC_LEN; ++i) {
    uint64_t lower = num->bits[i] & UINT32_MAX;
    uint64_t upper = num->bits[i] >> 32;

    lower += carry;
    upper += lower >> 32;
    carry = upper >> 32;
    num->bits[i] = lower & UINT32_MAX;
    num->bits[i] |= upper << 32;
  }
}

uint64_t big_div_by_10(big_dec_t *num) {
  uint32_t remainder = 0;
  for (int i = BIG_DEC_LEN - 1; i >= 0; --i) {
    uint64_t current = num->bits[i];
    uint32_t upper = current >> 32;
    uint32_t lower = current & 0xFFFFFFFF;

    uint64_t temp = ((uint64_t)remainder << 32) | upper;
    uint32_t new_upper = temp / 10;
    remainder = temp % 10;

    temp = ((uint64_t)remainder << 32) | lower;
    uint32_t new_lower = temp / 10;
    remainder = temp % 10;

    num->bits[i] = ((uint64_t)new_upper << 32) | new_lower;
  }
  return remainder;
}

bool big_is_odd(big_dec_t num) { return !!(num.bits[0] & ODD_NUM); }