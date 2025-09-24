#include "s21_decimal.h"

big_dec_t from_dec_to_big(s21_decimal dec) {
  big_dec_t res = {{0ul}, {0}};
  res.flags = dec.parts.flags;
  res.bits[0] = dec.bits[0];
  res.bits[0] |= (uint64_t)dec.bits[1] << 32;
  res.bits[1] = dec.bits[2];
  return res;
}

int overflow_comp(big_dec_t num) {
  return (num.bits[1] >> 32) || num.bits[2] || num.bits[3] || num.bits[4] ||
         num.bits[5];
}

int from_big_to_dec(s21_decimal *dec, big_dec_t *src) {
  int ret = !big_is_null(*src);
  int rnd = 0;
  int mod = 0;

  for (; (overflow_comp(*src) && src->flags.scale > 0) || src->flags.scale > 28;
       src->flags.scale -= 1) {
    mod = big_div_by_10(src);
    rnd += mod;
  }

  if (mod > 5) {
    big_plus_x(src, 1);
  } else if (mod == 5 && rnd == 5 && big_is_odd(*src)) {
    big_plus_x(src, 1);
  } else if (mod == 5 && rnd != 5) {
    big_plus_x(src, 1);
  }

  dec->bits[0] = (uint32_t)(src->bits[0] & UINT32_MAX);
  dec->bits[1] = (uint32_t)(src->bits[0] >> 32);
  dec->bits[2] = (uint32_t)(src->bits[1] & UINT32_MAX);

  ret = ret && is_null(*dec);

  dec->parts.flags.scale |= src->flags.scale;
  dec->parts.flags.sign |= src->flags.sign;

  return (ret ? 2 : overflow_comp(*src));
}
