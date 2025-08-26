#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int flag = 0;
  unsigned int tmp = (unsigned int)abs(src);
  memset(&(dst->bits), 0, sizeof(dst->bits));
  if (isnan((double)src) || isinf((double)src) || src > INT_MAX ||
      src < INT_MIN)
    flag = 1;
  else {
    (src < 0) ? set_sign(dst, 1) : set_sign(dst, 0);
    for (int i = 0; i < 32; ++i) {
      setting_bit(dst, tmp % 2, i);
      tmp /= 2;
    }
  }
  return flag;
}