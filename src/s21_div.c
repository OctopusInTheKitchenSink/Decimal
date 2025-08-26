#include "./s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  memset(&(result->bits), 0, sizeof(result->bits));
  int error = S21_ARITHMETIC_OK;
  if (DecCheckZero(value_2))
    error = S21_ARITHMETIC_ZERO_DIV;
  else {
    s21_big_decimal TempValue1 = {0}, TempValue2 = {0}, BigResult = {0};
    Dec_To_BigDec(value_1, &TempValue1);
    Dec_To_BigDec(value_2, &TempValue2);
    int TotalExp = take_scale(value_1) - take_scale(value_2);
    s21_big_div(TempValue1, TempValue2, &BigResult, &TotalExp);
    error = bank_round(&BigResult, result, &TotalExp);
    set_scale(result, TotalExp);
    set_sign(result, take_sign(value_1) ^ take_sign(value_2));
  }
  if ((error == S21_ARITHMETIC_BIG) & (take_sign(*result)))
    error = S21_ARITHMETIC_SMALL;
  if (error != S21_ARITHMETIC_OK)
    memset(&(result->bits), 0, sizeof(result->bits));
  return error;
}

int s21_big_div(s21_big_decimal value1, s21_big_decimal value2,
                s21_big_decimal *result, int *Exp) {
  int flag = 0;
  s21_big_decimal TempValue = {0};
  BigToBig(value1, &TempValue);
  int error = S21_ARITHMETIC_OK;
  while (flag == 0) {
    int flag_greater = 1;
    int shift_counter = 0;
    s21_big_decimal ShiftValue = {0};
    BigToBig(value2, &ShiftValue);
    while (s21_is_greater_or_equal_big(TempValue, ShiftValue)) {
      big_shift_right(&ShiftValue);
      shift_counter += 1;
    }
    if (!s21_is_greater_or_equal_big(TempValue, ShiftValue) &
        (shift_counter > 0)) {
      big_shift_left(&ShiftValue);
      shift_counter -= 1;
    }
    s21_big_decimal For_sub = {0};
    set_big_bit(&For_sub, shift_counter, 1);
    if (s21_is_greater_or_equal_big(TempValue, ShiftValue)) {
      s21_sub_big_decimal(TempValue, ShiftValue, &TempValue);
    } else
      flag_greater = 0;
    if (CheckZero(TempValue))
      flag = 1;
    else if (!s21_is_greater_or_equal_big(TempValue, value2)) {
      *Exp += 1;
      ten_pow(TempValue, &TempValue, 1);
      ten_pow(For_sub, &For_sub, 1);
      ten_pow(*result, result, 1);
    }
    if (flag_greater) big_sum(For_sub, *result, result);
    if (*Exp >= 28) flag = 1;
  }
  if (*Exp < 0) {
    ten_pow(*result, result, *Exp * (-1));
    *Exp = 0;
  }
  return error;
}

int s21_is_greater_or_equal_big(s21_big_decimal value1,
                                s21_big_decimal value2) {
  int flag = -1;
  for (int i = 255; (i >= 0) & (flag == -1); i--) {
    if (get_big_bit(value1, i) < get_big_bit(value2, i)) flag = 0;
    if (get_big_bit(value1, i) > get_big_bit(value2, i)) flag = 1;
  }
  return flag;
}

int CheckZero(s21_big_decimal value) {
  int flag = 1;
  for (int i = 0; i < 256; i++) {
    if (get_big_bit(value, i) == 1) flag = 0;
  }
  return flag;
}

int DecCheckZero(s21_decimal value) {
  int flag = 1;
  for (int i = 0; i < 96; i++) {
    if (get_bit(value, i) == 1) flag = 0;
  }
  return flag;
}

unsigned int decimal_divide_by_10(s21_decimal *dec) {
  unsigned int remainder = 0;
  unsigned int quotient;
  for (int i = 2; i >= 0; --i) {
    unsigned long long dividend =
        ((unsigned long long)remainder << 32) | (unsigned int)dec->bits[i];
    quotient = (unsigned int)(dividend / 10);
    remainder = (unsigned int)(dividend % 10);
    dec->bits[i] = quotient;
  }
  return remainder;
}

unsigned int big_decimal_divide_by_10(s21_big_decimal *big_dec) {
  unsigned int remainder = 0;
  unsigned int quotient;

  for (int i = 7; i >= 0; --i) {
    unsigned long long dividend =
        ((unsigned long long)remainder << 32) | (unsigned int)big_dec->bits[i];
    quotient = (unsigned int)(dividend / 10);
    remainder = (unsigned int)(dividend % 10);
    big_dec->bits[i] = quotient;
  }
  return remainder;
}