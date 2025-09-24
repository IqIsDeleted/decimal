#include "s21_decimal.h"

uint32_t div_by_10(void *ptr, size_t len) {
  uint32_t *num = (uint32_t *)ptr;
  uint64_t temp_res = 0;

  for (int cnt = len - 1; cnt >= 0; --cnt) {
    temp_res = (temp_res << 32) + num[cnt];
    num[cnt] = (uint32_t)(temp_res / 10);
    temp_res %= 10;
  }

  return temp_res;
}

void mul_by_10(void *ptr, size_t len) {
  uint32_t *num = (uint32_t *)ptr;
  uint64_t carry = 0;

  for (size_t cnt = 0; cnt < len; ++cnt) {
    uint64_t temp = (uint64_t)num[cnt] * 10 + carry;
    num[cnt] = (uint32_t)temp;
    carry = temp >> 32;
  }
}

void mul_by_10_for_big(big_dec_t *num) {
  uint64_t carry = 0;

  for (int i = 0; i < BIG_DEC_LEN; ++i) {
    uint64_t lower = num->bits[i] & 0xFFFFFFFF;
    uint64_t upper = num->bits[i] >> 32;

    uint64_t lower_res = lower * 10;
    uint64_t upper_res = upper * 10;

    uint64_t total = (upper_res << 32) + lower_res + carry;
    num->bits[i] = total;

    carry = (upper_res >> 32) + (total < lower_res);
  }
}
