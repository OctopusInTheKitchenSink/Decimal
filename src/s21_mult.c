#include "s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  memset(&(result->bits), 0, sizeof(result->bits));
  int error = S21_ARITHMETIC_OK;
  s21_big_decimal temp1 = {0}, temp2 = {0}, result2 = {0};
  Dec_To_BigDec(value_1, &temp1);
  Dec_To_BigDec(value_2, &temp2);
  int sign1 = take_sign(value_1), sign2 = take_sign(value_2);
  int Exp1 = take_scale(value_1), Exp2 = take_scale(value_2);
  error = big_mult(temp1, temp2, &result2);
  int TotalExp = Exp1 + Exp2;
  error = bank_round(&result2, result, &TotalExp);
  set_sign(result, sign1 ^ sign2);
  set_scale(result, TotalExp);
  if ((error == S21_ARITHMETIC_BIG) & (take_sign(*result)))
    error = S21_ARITHMETIC_SMALL;
  if (error != S21_ARITHMETIC_OK)
    memset(&(result->bits), 0, sizeof(result->bits));
  return error;
}

int big_mult(s21_big_decimal value1, s21_big_decimal value2,
             s21_big_decimal *result) {
  char flag = S21_ARITHMETIC_OK;
  s21_big_decimal temp1 = {0}, temp_result = {0};
  BigToBig(value1, &temp1);
  for (int i = 0; i < 256; i++) {
    if (get_big_bit(value2, i) == 1) {
      if (get_big_bit(*result, 255) == 1) flag = S21_ARITHMETIC_BIG;
      s21_big_decimal shifted_temp = {0};
      BigToBig(temp1, &shifted_temp);
      for (int j = 0; j < i; j++) {
        big_shift_right(&shifted_temp);
      }
      flag = big_sum(shifted_temp, temp_result, &temp_result);
    }
  }
  BigToBig(temp_result, result);
  return flag;
}