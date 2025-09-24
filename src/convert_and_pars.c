#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  null_decimal(dst, 4);
  int error_code = 0;
  if (dst == NULL) {
    error_code = 1;
  } else {
    if (src < 0) {
      src *= -1;
      dst->bits[3] |= (1 << 31);
    }
    dst->bits[0] = src;
  }
  return error_code;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int error_code = 0, sign = 1;
  if (get_sign(src) == 1) {
    set_sign(&src, 0);
    sign = -1;
  }
  int scale = get_scale(src);
  if (((src.bits[1] != 0 || src.bits[2] != 0) && src.bits[3] == 0) ||
      scale > 28) {
    error_code = 1;
    *dst = 0;
  } else {
    for (int i = get_scale(src); i > 0;
         i--) {  // если что заменить на функцию Егора s21_trancate
      div_by_10(&src, 3);
    }
    if (src.bits[1] == 0 && src.bits[2] == 0) {
      *dst = src.bits[0] * sign;
    } else {
      *dst = 0;
      error_code = 1;
    }
  }
  return error_code;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  s21_decimal temp = {{{0}}};
  if (dst != NULL) {
    null_decimal(dst, 4);
    temp = *dst;
  }
  double temp_src = 0, exponent_part = 0;
  int error_code = 0, scale_counter = 1, temp_scale = 0, number_counter = 0;
  if (dst == NULL || (0 < fabs(src) && fabs(src) <= 1e-28) ||
      fabs(src) >= 7.9228162514264337593543950335E+28 || src == NAN) {
    error_code = FAIL;
  } else {
    if (src < 0 || src == -0.0) {
      src *= -1;
      dst->parts.flags.sign = 1;
    }
    temp_src = src;

    exponent_part = fmod(src, 1);
    for (; (long long int)temp_src != 0; temp_scale++) {
      temp_src = temp_src / 10;
    }
    int iteration = temp_scale, i = 0;
    int numbers[iteration];
    while (temp_scale != 0) {
      numbers[i] = (int)fmod(src, 10);
      src /= 10;
      temp_scale--;
      i++;
    }
    for (i = iteration - 1; i >= 0; i--) {
      temp.bits[0] = numbers[i];
      mul_by_10(dst, 3);
      s21_add(*dst, temp, dst);
    }
    null_decimal(&temp, 4);

    if (exponent_part > 0.000000) {
      for (int i = 0; number_counter < 6; i++) {
        temp.bits[0] = (int)exponent_part;
        mul_by_10(dst, 3);
        if (temp.bits[0] == 0) {
          s21_add(*dst, temp, dst);
        } else {
          s21_add(*dst, temp, dst);
          number_counter++;
        }
        scale_counter++;
        exponent_part -= (int)exponent_part;
        exponent_part *= 10;
      }
      set_scale(dst, scale_counter - 2);
    }
  }
  return error_code;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int error_code = 0;
  long double result = (unsigned int)(src.bits[0]) +
                       ((unsigned int)(src.bits[1]) * pow(2, 32)) +
                       ((unsigned int)(src.bits[2]) * pow(2, 64));
  result = result / (pow(10, get_scale(src)));
  if (result < 1e-28 || result > 7.9228162514264337593543950335E+28) {
    error_code = 1;
    *dst = 0;
  } else {
    *dst = result;
    if (src.parts.flags.sign == 1) *dst *= -1;
  }
  return error_code;
}
