#include <limits.h>

#include "s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int flag = 0;
  memset(&(dst->bits), 0, sizeof(dst->bits));
  if (isinf(src) || isnan(src) || (fabs(src) < SMALLEST_DIGIT && src) ||
      fabs(src) > LARGEST_DIGIT)
    flag = 1;
  if (!flag) {
    if (src < 0) set_sign(dst, 1);
    double src1 = fabs((double)src);
    int scale_for_zero = 1;
    if ((int)src == 0) scale_for_zero = 10;
    int scale = 0, too_big_flag = 0;
    if (src1 > 10000000) {
      while (src1 > 10000000 && !flag) {
        too_big_flag = 1;
        if (scale > 28) flag = 1;
        scale++;
        src1 /= 10;
      }
    } else
      while (src1 * 10 < (10000000 * scale_for_zero) && src != 0) {
        if (scale > 28) flag = 1;
        scale++;
        src1 *= 10;
      }
    if (!flag) {
      src1 = round(src1);
      if (too_big_flag) {
        for (int i = 0; i < scale; ++i) {
          src1 *= 10;
        }
        scale = 0;
      }
      if (src != 0) {
        for (int i = 0; i < 96; ++i) {
          setting_bit(dst, (int)src1 % 2, i);
          src1 /= 2;
        }
        set_scale(dst, scale);
      }
    }
  }
  return flag;
}