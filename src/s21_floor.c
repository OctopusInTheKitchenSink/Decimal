#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  int sign = take_sign(value);
  int scale = take_scale(value);
  memset(&(result->bits), 0, sizeof(result->bits));
  s21_decimal one = {0};
  s21_from_int_to_decimal(-1, &one);
  if (scale) {
    s21_truncate(value, result);
    if (sign) s21_add(*result, one, result);
  } else
    *result = value;
  return 0;
}