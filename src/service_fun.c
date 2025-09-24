#include "s21_decimal.h"

/*
Returned result:
If num < 0 -> 1
If num >= 0 -> 0
*/
bool get_sign(s21_decimal num) {
  return (bool)(num.parts.flags.sign);
  // return (bool)(num.bits[3] & SIGN_MASK);
}

bool big_get_sign(big_dec_t num) { return (bool)(num.flags.sign); }

/*
Set the sign bit on input arg value
*/
void set_sign(s21_decimal *num, bool sign) {
  num->parts.flags.sign = sign;
  // num->bits[3] = (num->bits[3] & ~(SIGN_MASK)) | ((uint32_t)sign <<
  // SIGN_SHIFT);
}

void big_set_sign(big_dec_t *num, bool sign) { num->flags.sign = sign; }

/*
Input:
Two normalized decimals.
Returned result:
If a = b -> 0
If a > b -> 1
If a < b -> -1
!!! -0 == 0 !!!
*/
int __builtin_comparison_fun(s21_decimal a, s21_decimal b) {
  big_dec_t a_tmp = from_dec_to_big(a), b_tmp = from_dec_to_big(b);
  return comparison_of_two_big(a_tmp, b_tmp);
}

/*
Returned result:
If a = b -> 0
If a > b -> 1
If a < b -> -1
!!! -0 == 0 !!!
*/
int comparison_of_two_big(big_dec_t a, big_dec_t b) {
  big_normalization(&a, &b);
  int sign_diff = b.flags.sign - a.flags.sign;
  int res = !big_is_null(a) || !big_is_null(b);

  int cmp = 0;
  for (int i = 5; !cmp && i >= 0; --i) {
    cmp |= (a.bits[i] > b.bits[i]);
    cmp |= (a.bits[i] < b.bits[i]) << 1;
  }

  res *= (cmp & 1) - ((cmp >> 1) & 1);

  return sign_diff ? sign_diff : big_get_sign(a) ? -res : res;
}

/*
Returned result:
If n = 0 -> 1
If n != 0 -> 0
*/
bool is_null(s21_decimal num) {
  return !(num.bits[0] | num.bits[1] | num.bits[2]);
}
bool big_is_null(big_dec_t num) {
  return !(num.bits[0] | num.bits[1] | num.bits[2] | num.bits[3] | num.bits[4] |
           num.bits[5]);
}

/*
Set every bit to zero
*/
void null_decimal(s21_decimal *num, size_t len) {
  for (size_t i = 0; i < len; ++i) {
    num->bits[i] = 0;
  }
}

/*
Sets a bit on the input value
Input arg:
Ptr to dec
95 >= bit >= 0
*/
void set_bit(s21_decimal *num, uint8_t bit, bool val) {
  num->bits[bit / 32] =
      (num->bits[bit / 32] & ~(1u << bit % 32)) | val << (bit % 32);
}

void set_scale(s21_decimal *num, int val) {
  num->parts.flags.scale = val;
  // num->bits[3] = (num->bits[3] & ~(SCALE_MASK)) | (val << SCALE_SHIFT);
}

int get_scale(s21_decimal num) {
  return num.parts.flags.scale;
  // return (num.bits[3] & SCALE_MASK) >> SCALE_SHIFT;
}

void normalization(s21_decimal *a, s21_decimal *b) {
  if (is_null(*a) && is_null(*b)) {
    set_sign(a, 0);
    set_sign(b, 0);
  } else {
    int scale_diff = get_scale(*a) - get_scale(*b);
    s21_decimal *tmp = scale_diff > 0 ? b : a;
    scale_diff < 0 ? (scale_diff = -scale_diff) : 0;
    for (int i = 0; i < scale_diff; ++i) mul_by_10(tmp, 3);
    set_scale(tmp, get_scale(*tmp) + scale_diff);
  }
}

void big_normalization(big_dec_t *a, big_dec_t *b) {
  if (big_is_null(*a) && big_is_null(*b)) {
    a->flags.sign = 0;
    b->flags.sign = 0;
  } else {
    int scale_diff = a->flags.scale - b->flags.scale;
    big_dec_t *tmp = scale_diff > 0 ? b : a;
    scale_diff < 0 ? (scale_diff = -scale_diff) : 0;
    for (int i = 0; i < scale_diff; ++i) mul_by_10_for_big(tmp);

    tmp->flags.scale = tmp->flags.scale + scale_diff;
  }
}

/*
Changes the value of two big decimals.
*/
void big_swap_decimal(big_dec_t *a, big_dec_t *b) {
  for (int i = 0; i < 7; ++i) {
    *(a->bits + i) ^= *(b->bits + i);
    *(b->bits + i) ^= *(a->bits + i);
    *(a->bits + i) ^= *(b->bits + i);
  }
}

/*
Checks the decimal for validity.
*/
int valid_data_for_arithmetic(s21_decimal a, s21_decimal b, s21_decimal *res) {
  bool val_a =
      a.parts.flags.empty1 || a.parts.flags.empty2 || a.parts.flags.scale > 28;
  bool val_b =
      b.parts.flags.empty1 || b.parts.flags.empty2 || b.parts.flags.scale > 28;
  return (!val_a && !val_b && res != NULL);
}

int valid_data_for_round(s21_decimal a, s21_decimal *res) {
  return (a.parts.flags.empty1 || a.parts.flags.empty2 ||
          a.parts.flags.scale > 28 || res == NULL);
}

int get_bit(s21_decimal decimal, int index) {  // ????
  return (decimal.bits[index / 32] &= 1 << index) >> index;
}

void add_one(s21_decimal *result) {
  unsigned memory = 1;

  for (int i = 0; i < 32 * 3; i++) {
    unsigned result_bit = get_bit(*result, i) + memory;
    memory = result_bit / 2;
    result_bit %= 2;
    set_bit(result, i, result_bit);
  }
}

/*
Copies the decimal number
*/
void copying_decimal(s21_decimal value, s21_decimal *result) {
  *result = value;
}