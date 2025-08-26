#include "s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  int sign = take_sign(value);
  int scale = take_scale(value);
  memset(&(result->bits), 0, sizeof(result->bits));
  int flag = 0;
  if (scale) {
    value.bits[3] = 0;
    set_scale(&value, scale - 1);
    s21_decimal tmp_res = {0}, one = {{1, 0, 0, 0}};
    s21_truncate(value, &tmp_res);
    int last_digit = decimal_divide_by_10(&tmp_res);
    if (last_digit > 4) s21_add(tmp_res, one, &tmp_res);
    set_sign(&tmp_res, sign);
    *result = tmp_res;
  } else
    *result = value;
  return flag;
}