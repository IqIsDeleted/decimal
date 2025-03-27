#include "my_decimal.h"

/*
Returned result:
If num < 0 -> 1
If num >= 0 -> 0
*/
bool get_sign(my_decimal num) { return (bool)(num.bits[3] & SIGN_MASK); }

/*
Set the sign bit on input arg value
*/
void set_sign(my_decimal *num, bool sign) {
  if (num != NULL)
    num->bits[3] =
        (num->bits[3] & ~(SIGN_MASK)) | ((uint32_t)sign << SIGN_SHIFT);
}

/*
Input:
Two normalized decimals.
Returned result:
If a = b -> 0
If a > b -> 1
If a < b -> -1
!!! -0 == 0 !!!
*/
int __builtin_comparison_fun(my_decimal a, my_decimal b) {
  normalization(&a, &b);
  int sign_diff = get_sign(b) - get_sign(a);
  int res = !is_null(a) || !is_null(b);
  int cmp = 0;

  for (int i = 2; !cmp && i >= 0; --i) {
    cmp |= (a.bits[i] > b.bits[i]);
    cmp |= (a.bits[i] < b.bits[i]) << 1;
  }

  res *= (cmp & 1) - ((cmp >> 1) & 1);
  return sign_diff ? sign_diff : get_sign(a) ? -res : res;
}

/*
Returned result:
If n = 0 -> 0
If n != 0 -> 1
*/
bool is_null(my_decimal num) {
  return !(bool)(num.bits[0] | num.bits[1] | num.bits[2]);
}

/*
Set every bit to zero
*/
void null_decimal(my_decimal *num, size_t len) {
  for (size_t i = 0; i < len; ++i) {
    num->bits[i] = 0;
  }
}

/*
Input arg:
31 >= p >= 0
31 >= n >= 0
Returned result:
n bits on p position
*/
int get_bits(unsigned x, uint8_t p, uint8_t n) {
  uint8_t i = p - n + 1;
  return (((x >> i) & ~(~0u << n)) << i);
}

/*
Sets a bit on the input value
Input arg:
Ptr to dec
95 >= bit >= 0
*/
void set_bit(my_decimal *num, uint8_t bit, bool val) {
  num->bits[bit / 32] =
      (num->bits[bit / 32] & ~(FIRST_BIT << bit % 32)) | val << (bit % 32);
}

void set_scale(my_decimal *num, int val) {
  num->bits[3] = (num->bits[3] & ~(SCALE_MASK)) | (val << SCALE_SHIFT);
}

int get_scale(my_decimal num) {
  return (num.bits[3] & SCALE_MASK) >> SCALE_SHIFT;
}

bool normalization(my_decimal *a, my_decimal *b) {
  int scale_diff = get_scale(*a) - get_scale(*b);
  my_decimal *tmp = scale_diff > 0 ? b : a;
  scale_diff < 0 ? (scale_diff = -scale_diff) : 0;
  for (int i = 0; i < scale_diff; ++i) mul_by_10(tmp, 3);
  set_scale(tmp, get_scale(*tmp) + scale_diff);
  return 0;
}

/*
Changes the value of two decimals.
*/
void swap_decimal(my_decimal *a, my_decimal *b) {
  for (int i = 0; i < 4; ++i) {
    *(a->bits + i) ^= *(b->bits + i);
    *(b->bits + i) ^= *(a->bits + i);
    *(a->bits + i) ^= *(b->bits + i);
  }
}
