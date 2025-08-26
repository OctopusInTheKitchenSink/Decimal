#include "s21_decimal.h"

int s21_is_equal(s21_decimal value1, s21_decimal value2) {
  int flag = 1;
  int sign1 = take_sign(value1), sign2 = take_sign(value2);
  s21_big_decimal temp1 = {0}, temp2 = {0};
  CastExp(value1, value2, &temp1, &temp2);
  if (is_zero_big(temp1) && is_zero_big(temp2))
    flag = 1;
  else if (sign1 != sign2)
    flag = 0;
  else {
    for (int i = 0; i < 256; i++) {
      if (get_big_bit(temp1, i) != get_big_bit(temp2, i)) {
        flag = 0;
      }
    }
  }
  return flag;
}

int s21_is_less(s21_decimal value1, s21_decimal value2) {
  int flag = -1;
  int sign1 = take_sign(value1), sign2 = take_sign(value2);
  s21_big_decimal temp1 = {0}, temp2 = {0};
  CastExp(value1, value2, &temp1, &temp2);
  if (is_zero_big(temp1) && is_zero_big(temp2))
    flag = 0;
  else if (flag == -1 && sign1 == 1 && sign2 == 0)
    flag = 1;
  else if (flag == -1 && sign1 == 0 && sign2 == 1)
    flag = 0;
  else if (flag == -1 && sign1 == sign2) {
    for (int i = 255; i >= 0 && flag == -1; i--) {
      if (get_big_bit(temp1, i) < get_big_bit(temp2, i)) {
        flag = 1 && !sign1;
      } else if (get_big_bit(temp1, i) > get_big_bit(temp2, i)) {
        flag = 0 || sign1;
      } else if ((i == 0) & (flag == -1)) {
        flag = 0;
      }
    }
  }
  return flag;
}

int s21_is_less_or_equal(s21_decimal value1, s21_decimal value2) {
  return (s21_is_equal(value1, value2) | s21_is_less(value1, value2));
}

int s21_is_greater(s21_decimal value1, s21_decimal value2) {
  return (!s21_is_equal(value1, value2) & !s21_is_less(value1, value2));
}

int s21_is_greater_or_equal(s21_decimal value1, s21_decimal value2) {
  return (!s21_is_less(value1, value2));
}

int s21_is_not_equal(s21_decimal value1, s21_decimal value2) {
  return (!s21_is_equal(value1, value2));
}