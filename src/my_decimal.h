#ifndef MY_DEC
#define MY_DEC

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FIRST_BIT 1u
#define SIGN_SHIFT 31
#define SIGN_MASK 1u << SIGN_SHIFT  // 0x80000000
#define SCALE_MASK 0x7F800000       // (1u << 9 - 1) << SCALE_SHIFT
#define SCALE_SHIFT 23
#define NaN 0x007FFFFF

#define sub_or_add(a) __builtin_sub_or_add(&value_1, &value_2, result, a)
#define addition() __builtin_add(value_1, value_2, result)
#define subtraction() __builtin_sub(value_1, value_2, result)
#define ADD 0
#define SUB 1

// typedef struct {
//   unsigned bits[4];
// } my_decimal;

typedef struct {
  union {
    struct {
      uint32_t bits[3];
      struct {
        uint32_t _reserved : 23;
        uint32_t scale : 8;
        uint32_t sign : 1;
      } flags;
    } parts;
    uint32_t bits[4];
  };
} my_decimal;


/*
Service function
*/

bool is_null(my_decimal num);
int __builtin_comparison_fun(my_decimal a, my_decimal b);
void null_decimal(my_decimal *num, size_t len);
bool get_sign(my_decimal num);
void set_sign(my_decimal *num, bool sign);
int get_bits(unsigned x, uint8_t p, uint8_t n);
void set_scale(my_decimal *num, int val);
int get_scale(my_decimal num);
void set_bit(my_decimal *num, uint8_t bit, bool val);
bool normalization(my_decimal *a, my_decimal *b);
void swap_decimal(my_decimal *a, my_decimal *b);


/*
Auxiliary mathematical functions
*/

int __builtin_sub_or_add(my_decimal *a, my_decimal *b, my_decimal *result,
                         uint8_t operation);
int __builtin_add(my_decimal a, my_decimal b, my_decimal *result);
int __builtin_sub(my_decimal a, my_decimal b, my_decimal *result);
uint32_t div_by_10(void *ptr, size_t len);
void mul_by_10(void *ptr, size_t len);


/*
Arithmetic Operators
*/

int my_add(my_decimal value_1, my_decimal value_2, my_decimal *result);
int my_sub(my_decimal value_1, my_decimal value_2, my_decimal *result);
int my_mul(my_decimal value_1, my_decimal value_2, my_decimal *result);
int my_div(my_decimal value_1, my_decimal value_2, my_decimal *result);


/*
Other functions
*/

int my_negate(my_decimal value, my_decimal *result);

/*
Other:
The defined type must support numbers from
-79,228,162,514,264,337,593,543,950,335 to
+79,228,162,514,264,337,593,543,950,335.
((-2^96 to 2^96) / 10^(0 to 28)), where -(2^96-1) is equal to MinValue and
2^96-1 is equal to MaxValue.
*/

#endif