#include "my_decimal.h"

/*
Returns the result of multiplying the specified Decimal value by negative one.
*/
int my_negate(my_decimal value, my_decimal *result) {
  int res = 1;
  if (result != NULL) {
    result->parts.flags.sign = value.parts.flags.sign ^ 1;
    res = 0;
  }
  return res;
}
