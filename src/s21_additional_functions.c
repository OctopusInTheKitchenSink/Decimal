#include "./s21_decimal.h"

void set_sign(s21_decimal *dst, int sign) {
  unsigned int mask = 1;
  if (sign)
    dst->bits[3] |= mask << 31;
  else
    dst->bits[3] &= ~(mask << 31);
}

void set_scale(s21_decimal *dst, int scale) {
  scale = scale << 16;
  dst->bits[3] |= scale;
}

void setting_bit(s21_decimal *dst, int value, int index) {
  unsigned int mask = 1;
  if (index >= 0 && index < 96) {
    if (value)
      dst->bits[index / 32] |= mask << (index % 32);
    else
      dst->bits[index / 32] &= ~(mask << (index % 32));
  }
}

void set_bit(s21_decimal *dst, int index, int value) {
  unsigned int mask = 1;
  if (index >= 0 && index < 96) {
    if (value)
      dst->bits[index / 32] |= mask << (index % 32);
    else
      dst->bits[index / 32] &= ~(mask << (index % 32));
  }
}

int take_scale(s21_decimal src) {
  int ptr = src.bits[3];
  unsigned int mask = 0b11111111 << 16;
  int scale = (ptr & mask) >> 16;
  return scale;
}

int take_sign(s21_decimal src) {
  unsigned int mask = (1 << 31);
  return ((src.bits[3] & mask) != 0) ? 1 : 0;
}

int getting_bit(s21_decimal src, int i) {
  unsigned int mask = (1 << (i % 32));
  int res = src.bits[i / 32] &= mask;
  return (res >> (i % 32)) & 1;
}

int get_bit(s21_decimal src, char i) {
  unsigned int mask = (1 << (i % 32));
  int res = src.bits[i / 32] &= mask;
  return (res >> (i % 32)) & 1;
}

char bank_round(s21_big_decimal *value, s21_decimal *result, int *exponent) {
  memset(&(result->bits), 0, sizeof(result->bits));
  char flag = S21_ARITHMETIC_OK;
  s21_big_decimal temp = {{0, 0, 0, 0, 0, 0, 0, 0}};
  BigToBig(*value, &temp);
  int counter = BigLastOne(temp);
  int last_digit, counter_for_bank_round = 0;
  s21_big_decimal big_one = {{1, 0, 0, 0, 0, 0, 0, 0}};
  if (counter < 96)
    for (int i = 0; i < 96; i++) set_bit(result, i, get_big_bit(temp, i));
  else {
    while (counter >= 96 && *exponent > 0) {
      last_digit = big_decimal_divide_by_10(&temp);
      if (*exponent == 1) {
        s21_big_decimal tmp_for_bank_round = {{0, 0, 0, 0, 0, 0, 0, 0}};
        BigToBig(temp, &tmp_for_bank_round);
        int last_digit_for_bank_round =
            big_decimal_divide_by_10(&tmp_for_bank_round);
        if (last_digit_for_bank_round % 2 != 0 && last_digit == 5 &&
            !counter_for_bank_round)
          big_sum(temp, big_one, &temp);
        if (last_digit > 5 || (last_digit == 5 && counter_for_bank_round))
          big_sum(temp, big_one, &temp);
      } else if (last_digit > 4)
        big_sum(temp, big_one, &temp);
      counter = BigLastOne(temp);
      if (last_digit) counter_for_bank_round++;
      (*exponent)--;
    }
    if (counter >= 96 && *exponent == 0)
      flag = S21_ARITHMETIC_BIG;
    else {
      s21_decimal dec_exponent = {0};
      BigToDec(temp, &dec_exponent);
      *result = dec_exponent;
      set_scale(result, *exponent);
    }
  }
  return flag;
}

int BigLastOne(s21_big_decimal value) {
  char flag = -1;
  int counter = 0;
  for (int i = 255; i >= 0 && flag == -1; i--) {
    if (get_big_bit(value, i) == 1) flag = 1;
    if (flag == 1) counter = i;
  }
  return counter;
}
