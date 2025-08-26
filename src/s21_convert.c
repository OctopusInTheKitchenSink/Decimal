#include "s21_decimal.h"

void Dec_To_BigDec(s21_decimal value, s21_big_decimal *result) {
  for (int i = 0; i < 96; i++) set_big_bit(result, i, get_bit(value, i));
}

void BigToBig(s21_big_decimal value, s21_big_decimal *result) {
  for (int i = 0; i < 256; i++) set_big_bit(result, i, get_big_bit(value, i));
}

int BigToDec(s21_big_decimal value, s21_decimal *result) {
  for (int i = 95; i >= 0; i--) set_bit(result, i, get_big_bit(value, i));
  return S21_ARITHMETIC_OK;
}

int DecToDec(s21_decimal value, s21_decimal *result) {
  for (int i = 95; i >= 0; i--) set_bit(result, i, get_bit(value, i));
  set_scale(result, take_scale(value));
  set_sign(result, take_sign(value));
  return S21_ARITHMETIC_OK;
}