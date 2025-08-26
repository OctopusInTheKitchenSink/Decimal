#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  memset(&(result->bits), 0, sizeof(result->bits));
  int error = S21_ARITHMETIC_OK;
  s21_big_decimal temp1 = {0}, temp2 = {0}, result2 = {0};
  CastExp(value_1, value_2, &temp1, &temp2);
  int sign1 = take_sign(value_1), sign2 = take_sign(value_2);
  if (sign1 == sign2) {
    int TotalExp = MaxExp(value_1, value_2);
    error = ((big_sum(temp1, temp2, &result2)) |
             (bank_round(&result2, result, &TotalExp)));
    set_sign(result, sign1);
    set_scale(result, TotalExp);
  } else {
    s21_decimal TempValue = {0};
    if (sign1 == 1) {
      DecToDec(value_1, &TempValue);
      set_sign(&TempValue, 0);
      error = s21_sub(value_2, TempValue, result);
    }
    if (sign1 == 0) {
      DecToDec(value_2, &TempValue);
      set_sign(&TempValue, 0);
      error = s21_sub(value_1, TempValue, result);
    }
  }
  if ((error == S21_ARITHMETIC_BIG) & (take_sign(*result)))
    error = S21_ARITHMETIC_SMALL;
  if (error != S21_ARITHMETIC_OK)
    memset(&(result->bits), 0, sizeof(result->bits));
  return error;
}

int big_sum(s21_big_decimal value1, s21_big_decimal value2,
            s21_big_decimal *result) {
  char flag = S21_ARITHMETIC_OK;
  unsigned int carry = 0;
  for (int i = 0; i < 256; i++) {
    char bit1 = get_big_bit(value1, i);
    char bit2 = get_big_bit(value2, i);
    char sum = bit1 ^ bit2 ^ carry;
    set_big_bit(result, i, sum);
    carry = (bit1 & bit2) | (carry & (bit1 ^ bit2));
    if ((i == 255) & (carry == 1)) flag = S21_ARITHMETIC_BIG;
  }
  return flag;
}