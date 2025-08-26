#include "./s21_decimal.h"

void big_shift_right(s21_big_decimal *decimal) {
  for (int i = 255; i > 0; i--) {
    set_big_bit(decimal, i, get_big_bit(*decimal, i - 1));
  }
  set_big_bit(decimal, 0, 0);
}

void big_shift_left(s21_big_decimal *decimal) {
  for (int i = 0; i < 255; i++) {
    set_big_bit(decimal, i, get_big_bit(*decimal, i + 1));
  }
  set_big_bit(decimal, 255, 0);
}