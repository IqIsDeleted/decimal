#include "my_decimal.h"

/*
0 — OK;
1 — the number is too large or equal to infinity;
2 — the number is too small or equal to negative infinity.
*/
int my_add(my_decimal value_1, my_decimal value_2, my_decimal *result) {
  return sub_or_add(ADD) ? subtraction() : addition();
}

/*
0 — OK;
1 — the number is too large or equal to infinity;
2 — the number is too small or equal to negative infinity.
*/
int my_sub(my_decimal value_1, my_decimal value_2, my_decimal *result) {
  return sub_or_add(SUB) ? subtraction() : addition();
}
