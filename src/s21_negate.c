#include "s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  memset(&(result->bits), 0, sizeof(result->bits));
  int flag = 0;
  int sign = take_sign(value);
  *result = value;
  set_sign(result, !sign);
  return flag;
}