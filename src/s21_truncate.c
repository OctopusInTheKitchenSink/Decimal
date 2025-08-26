#include "s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int scale = take_scale(value);
  int sign = take_sign(value);
  memset(&(result->bits), 0, sizeof(result->bits));
  if (!scale)
    *result = value;
  else {
    s21_decimal tmp_value = value;
    tmp_value.bits[3] = 0;
    for (int i = 0; i < scale; ++i) decimal_divide_by_10(&tmp_value);
    *result = tmp_value;
    set_sign(result, sign);
  }

  return 0;
}