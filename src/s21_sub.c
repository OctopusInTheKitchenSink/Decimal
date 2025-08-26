#include "./s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  memset(&(result->bits), 0, sizeof(result->bits));
  int error = S21_ARITHMETIC_OK;
  s21_big_decimal temp1 = {0}, temp2 = {0}, result2 = {0};
  int sign1 = take_sign(value_1), sign2 = take_sign(value_2);
  int TotalExp = MaxExp(value_1, value_2);
  int ResultSign = 0;
  if ((sign1 == sign2) && (sign1 == 1)) {
    s21_decimal TempValue2 = {0};
    DecToDec(value_2, &TempValue2);
    set_sign(&TempValue2, 0);
    error = s21_add(value_1, TempValue2, result);
  } else if ((sign1 == sign2) && (sign1 == 0)) {
    CastExp(value_1, value_2, &temp1, &temp2);
    if (s21_is_greater(value_1, value_2)) {
      s21_sub_big_decimal(temp1, temp2, &result2);
      ResultSign = 0;
    } else {
      s21_sub_big_decimal(temp2, temp1, &result2);
      ResultSign = 1;
    }
    error = bank_round(&result2, result, &TotalExp);
    set_sign(result, ResultSign);
  } else if (sign1 < sign2) {
    s21_decimal TempValue2 = {0};
    DecToDec(value_2, &TempValue2);
    set_sign(&TempValue2, 0);
    error = s21_add(value_1, TempValue2, result);
    set_sign(result, 0);
  } else if (sign1 > sign2) {
    s21_decimal TempValue2 = {0};
    DecToDec(value_1, &TempValue2);
    set_sign(&TempValue2, 0);
    error = s21_add(value_2, TempValue2, result);
    set_sign(result, 1);
  }
  set_scale(result, TotalExp);
  if ((error == S21_ARITHMETIC_BIG) & (take_sign(*result)))
    error = S21_ARITHMETIC_SMALL;
  if (error != S21_ARITHMETIC_OK)
    memset(&(result->bits), 0, sizeof(result->bits));
  return error;
}

void s21_sub_big_decimal(s21_big_decimal value1, s21_big_decimal value2,
                         s21_big_decimal *result) {
  int tmp = 0, res = 0;
  for (int i = 0; i < 256; i++) {
    res = get_big_bit(value1, i) - get_big_bit(value2, i) - tmp;
    tmp = res < 0;
    res = abs(res);
    set_big_bit(result, i, res % 2);
  }
}