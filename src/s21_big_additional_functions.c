#include "s21_decimal.h"

void set_big_bit(s21_big_decimal *decimal, int bit, int value) {
  int num_bits = bit / 32;
  int bit_offset = bit % 32;
  if (value == 1) {
    decimal->bits[num_bits] |= (1 << bit_offset);
  } else if (value == 0) {
    decimal->bits[num_bits] &= ~(1 << bit_offset);
  }
}

int get_big_bit(s21_big_decimal decimal, int bit) {
  int num_bits = bit / 32;
  int bit_offset = bit % 32;
  return (decimal.bits[num_bits] >> bit_offset) & 1;
}

int ten_pow(s21_big_decimal value, s21_big_decimal *result, int exp) {
  int flag = S21_ARITHMETIC_OK;
  s21_decimal ten = {0};
  s21_from_int_to_decimal(10, &ten);
  s21_big_decimal big_ten = {0};
  Dec_To_BigDec(ten, &big_ten);
  s21_big_decimal temp_result = {0};
  BigToBig(value, &temp_result);
  for (int i = 0; i < exp; i++) {
    s21_big_decimal temp_result_mult = {0};
    flag = big_mult(temp_result, big_ten, &temp_result_mult);
    BigToBig(temp_result_mult, &temp_result);
  }
  BigToBig(temp_result, result);
  return flag;
}

int is_zero_big(s21_big_decimal value) {
  int flag = 1;
  for (int i = 0; i < 256; i++) {
    if (get_big_bit(value, i) != 0) flag = 0;
  }
  return flag;
}