#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define S21_ARITHMETIC_OK 0
#define S21_ARITHMETIC_BIG 1
#define S21_ARITHMETIC_SMALL 2
#define S21_ARITHMETIC_ZERO_DIV 3
#define S21_ARITHMETIC_ERROR 4

#define SMALLEST_DIGIT 1e-28
#define LARGEST_DIGIT 79228162514264337593543950335.0

typedef struct {
  int bits[4];
} s21_decimal;

typedef struct {
  int bits[8];
} s21_big_decimal;

int get_bit(s21_decimal src, char i);
void set_bit(s21_decimal *decimal, int bit, int value);
int get_big_bit(s21_big_decimal decimal, int bit);
void set_big_bit(s21_big_decimal *decimal, int bit, int value);

void set_sign(s21_decimal *dst, int sign);
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);

void set_scale(s21_decimal *dst, int scale);
void setting_bit(s21_decimal *dst, int value, int index);
int take_scale(s21_decimal src);
int take_sign(s21_decimal src);
int getting_bit(s21_decimal src, int i);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

int s21_from_decimal_to_int(s21_decimal src, int *dst);
void set_bit(s21_decimal *dst, int value, int index);

void shift_left(s21_decimal *s21_decimal);
void shift_right(s21_decimal *s21_decimal);
void big_shift_left(s21_big_decimal *decimal);
void big_shift_right(s21_big_decimal *decimal);

void CastExp(s21_decimal value_1, s21_decimal value_2, s21_big_decimal *temp_1,
             s21_big_decimal *temp_2);
int BigToDec(s21_big_decimal value, s21_decimal *result);
void Dec_To_BigDec(s21_decimal value, s21_big_decimal *result);
void BigToBig(s21_big_decimal value, s21_big_decimal *result);
int big_sum(s21_big_decimal value1, s21_big_decimal value2,
            s21_big_decimal *result);
int big_mult(s21_big_decimal value1, s21_big_decimal value2,
             s21_big_decimal *result);
int ten_pow(s21_big_decimal value, s21_big_decimal *result, int exp);
int MaxExp(s21_decimal value_1, s21_decimal value_2);
int is_zero_big(s21_big_decimal value);
int s21_is_equal(s21_decimal, s21_decimal);
int s21_is_less(s21_decimal value1, s21_decimal value2);
int s21_is_less_or_equal(s21_decimal value1, s21_decimal value2);
int s21_is_greater(s21_decimal value1, s21_decimal value2);
int s21_is_greater_or_equal(s21_decimal value1, s21_decimal value2);
int s21_is_not_equal(s21_decimal value1, s21_decimal value2);
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int DecToDec(s21_decimal value, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void s21_sub_big_decimal(s21_big_decimal value1, s21_big_decimal value2,
                         s21_big_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_big_div(s21_big_decimal value1, s21_big_decimal value2,
                s21_big_decimal *result, int *Exp);
int s21_is_greater_or_equal_big(s21_big_decimal value1, s21_big_decimal value2);
int CheckZero(s21_big_decimal value);
unsigned int decimal_divide_by_10(s21_decimal *dec);
int DecCheckZero(s21_decimal value);
unsigned int big_decimal_divide_by_10(s21_big_decimal *big_dec);
char bank_round(s21_big_decimal *value, s21_decimal *result, int *exponent);
int BigLastOne(s21_big_decimal value);