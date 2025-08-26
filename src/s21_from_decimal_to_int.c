#include "s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int flag = 0;
  double result = 0;
  int scale = take_scale(src);
  int sign = take_sign(src);
  for (int i = 0; i < 96 && !flag; ++i) {
    int bit = getting_bit(src, i);
    result += bit * pow(2, i);
  }
  for (int i = 0; i < scale; ++i) {
    result /= 10;
  }
  if (result > INT_MAX || result < INT_MIN) flag = 1;
  if (!flag) {
    int res = (int)result;
    if (sign) res *= -1;
    *dst = res;
  }
  return flag;
}