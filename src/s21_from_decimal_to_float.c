#include "s21_decimal.h"
int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  long double res = 0;
  int flag = 0;
  for (int i = 0; i < 96; ++i) {
    int bit = getting_bit(src, i);
    res += bit * pow(2, i);
  }
  int scale = take_scale(src);
  long double ten_scale = 1;
  for (int i = 0; i < scale; ++i) ten_scale *= 10.0;
  res /= ten_scale;
  int sign = take_sign(src);
  if (res > LARGEST_DIGIT || res < SMALLEST_DIGIT) flag = 1;
  if (!flag) {
    if (sign) res *= -1;
    *dst = res;
  }
  return flag;
}