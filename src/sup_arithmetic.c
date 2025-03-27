#include "my_decimal.h"

int __builtin_sub_or_add(my_decimal *a, my_decimal *b, my_decimal *result,
                         uint8_t operation) {
  if (result != NULL) {
    null_decimal(result, 4);
    normalization(a, b);
    if (__builtin_comparison_fun(*a, *b) == -1) swap_decimal(a, b);
  }
  return (operation + (a->parts.flags.sign ^ b->parts.flags.sign)) & 1;
}

int __builtin_add(my_decimal value_1, my_decimal value_2, my_decimal *result) {
  uint64_t tmp = 0ul;
  result->parts.flags.scale = value_1.parts.flags.scale;

  for (int i = 0; i < 3; ++i) {
    tmp += (uint64_t)value_1.bits[i] + (uint64_t)value_2.bits[i];
    result->bits[i] += (uint32_t)tmp;
    tmp >>= FIRST_BIT;
  }

  return (bool)(tmp);
}

int __builtin_sub(my_decimal value_1, my_decimal value_2, my_decimal *result) {
  result->parts.flags.scale = value_1.parts.flags.scale;

  int borrow = 0;
  for (int i = 0; i < 3; ++i) {
    uint64_t a = value_1.bits[i];
    uint64_t b = value_2.bits[i];
    uint64_t sub = a - b - borrow;
    result->bits[i] = (uint32_t)sub;
    borrow = !!(a < b + borrow);
  }
  return 0;
}

uint32_t div_by_10(void *ptr, size_t len) {
  uint32_t *num = (uint32_t *)ptr;
  uint64_t temp_res = 0;
  for (int count = len - 1; count >= 0; count--) {
    temp_res = (temp_res << FIRST_BIT) + num[count];
    num[count] = (uint32_t)(temp_res / 10);
    temp_res %= 10;
  }
  return temp_res;
}

void mul_by_10(void *ptr, size_t len) {
  uint32_t *num = (uint32_t *)ptr;
  uint64_t carry = 0;
  for (size_t count = 0; count < len; count++) {
    uint64_t temp = (uint64_t)num[count] * 10 + carry;
    num[count] = (uint32_t)temp;
    carry = temp >> FIRST_BIT;
  }
}
