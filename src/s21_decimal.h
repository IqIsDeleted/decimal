#ifndef S21_DEC
#define S21_DEC

#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BIG_DEC_LEN 6
#define ODD_NUM 1

#define INT32_MASK 0xFFFFFFFF
#define FAIL 1

#define sub_or_add(action)               \
  big_sub_or_add(&a, &b, result, action, \
                 __builtin_comparison_fun(value_1, value_2))
#define addition() big_add(a, b, result)
#define subtraction() big_sub(a, b, result)
#define ADD 0
#define SUB 1

#define INPUT_ERROR 4

typedef struct {
  uint32_t empty2 : 16;
  uint32_t scale : 8;
  uint32_t empty1 : 7;
  uint32_t sign : 1;

  /*Use one of two structural variations*/

  // uint32_t empty2 : 16;
  // uint32_t empty1 : 7;
  // uint32_t scale : 8;
  // uint32_t sign : 1;
} flags_t;

typedef struct {
  union {
    uint32_t bits[4];
    struct {
      uint32_t bits[3];
      flags_t flags;
    } parts;
  };
} s21_decimal;

typedef struct {
  uint64_t bits[BIG_DEC_LEN];
  flags_t flags;
} big_dec_t;

typedef struct {  // ????????
  unsigned int bits[8];
} s21_big_decimal;

/*
NNN
*/
void print_bit(s21_decimal num);

/*
Service function
*/
bool is_null(s21_decimal num);
int __builtin_comparison_fun(s21_decimal a, s21_decimal b);
void null_decimal(s21_decimal *num, size_t len);
bool get_sign(s21_decimal num);
bool big_get_sign(big_dec_t num);
void set_sign(s21_decimal *num, bool sign);
void big_set_sign(big_dec_t *num, bool sign);
int get_bits(unsigned x, uint8_t p, uint8_t n);
void set_scale(s21_decimal *num, int val);
int get_scale(s21_decimal num);
int big_get_scale(big_dec_t num);
void set_bit(s21_decimal *num, uint8_t bit, bool val);
void normalization(s21_decimal *a, s21_decimal *b);
void big_normalization(big_dec_t *a,
                       big_dec_t *b);  // FF
void mul_by_10_for_big(big_dec_t *num);

void swap_decimal(s21_decimal *a, s21_decimal *b);
void big_swap_decimal(big_dec_t *a, big_dec_t *b);

int __builtin_sub_or_add(s21_decimal *a, s21_decimal *b, s21_decimal *result,
                         uint8_t operation);
int big_sub_or_add(big_dec_t *a, big_dec_t *b, s21_decimal *result,
                   uint8_t operation, int comparison);
int __builtin_add(s21_decimal a, s21_decimal b, s21_decimal *result);
int big_add(big_dec_t a, big_dec_t b, s21_decimal *result);
int __builtin_sub(s21_decimal a, s21_decimal b, s21_decimal *result);
int big_sub(big_dec_t a, big_dec_t b, s21_decimal *result);
uint32_t div_by_10(void *ptr, size_t len);
void mul_by_10(void *ptr, size_t len);
void mul_processing(s21_decimal value_1, s21_decimal value_2, big_dec_t *tmp);
big_dec_t from_dec_to_big(s21_decimal dec);
int from_big_to_dec(s21_decimal *dec, big_dec_t *src);
int valid_data_for_arithmetic(s21_decimal a, s21_decimal b, s21_decimal *res);
int big_sub_or_add(big_dec_t *a, big_dec_t *b, s21_decimal *result,
                   uint8_t operation, int comparison);
s21_decimal abs_dec(volatile s21_decimal num);
void big_plus_x(big_dec_t *num, int x);
uint64_t big_div_by_10(big_dec_t *num);
bool big_is_odd(big_dec_t num);
bool check_too_small_num(s21_decimal *num);
bool big_is_null(big_dec_t num);
void sign_calculation(s21_decimal *a, s21_decimal *b, big_dec_t *res);
int comparison_of_two_big(big_dec_t a, big_dec_t b);
void div_processing(big_dec_t a, big_dec_t b, big_dec_t *tmp_res);
void add_one(s21_decimal *result);
void copying_decimal(s21_decimal value, s21_decimal *result);
int valid_data_for_round(s21_decimal a, s21_decimal *res);

/*
Arithmetic Operators
*/
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

/*
Comparison Operators
*/
int s21_is_less(s21_decimal, s21_decimal);
int s21_is_less_or_equal(s21_decimal, s21_decimal);
int s21_is_greater(s21_decimal, s21_decimal);
int s21_is_greater_or_equal(s21_decimal, s21_decimal);
int s21_is_equal(s21_decimal, s21_decimal);
int s21_is_not_equal(s21_decimal, s21_decimal);

/*
Convertors and parsers
*/
int s21_from_int_to_decimal(int src, s21_decimal *dst);      // From int
int s21_from_float_to_decimal(float src, s21_decimal *dst);  // From float
int s21_from_decimal_to_int(s21_decimal src, int *dst);      // To int
int s21_from_decimal_to_float(s21_decimal src, float *dst);  // To float

/*
Other functions
*/
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

/*
Other:
The defined type must support numbers from
-79,228,162,514,264,337,593,543,950,335 to
+79,228,162,514,264,337,593,543,950,335.
((-2^96 to 2^96) / 10^(0 to 28)), where -(2^96-1) is equal to MinValue and
2^96-1 is equal to MaxValue.
*/

#endif