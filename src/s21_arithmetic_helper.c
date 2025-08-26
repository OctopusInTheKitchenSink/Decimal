#include "./s21_decimal.h"

void CastExp(s21_decimal value_1, s21_decimal value_2, s21_big_decimal *temp_1,
             s21_big_decimal *temp_2) {
  memset(&(temp_1->bits), 0, sizeof(temp_1->bits));
  memset(&(temp_2->bits), 0, sizeof(temp_2->bits));
  int Exp1 = take_scale(value_1);
  int Exp2 = take_scale(value_2);
  Dec_To_BigDec(value_1, temp_1);
  Dec_To_BigDec(value_2, temp_2);
  if (Exp1 > Exp2) {
    ten_pow(*temp_2, temp_2, Exp1 - Exp2);
  } else if (Exp1 < Exp2) {
    ten_pow(*temp_1, temp_1, Exp2 - Exp1);
  }
}

int MaxExp(s21_decimal value_1, s21_decimal value_2) {
  int Exp1 = take_scale(value_1);
  int Exp2 = take_scale(value_2);
  int MaxExp = 0;
  if (Exp1 > Exp2)
    MaxExp = Exp1;
  else
    MaxExp = Exp2;
  return MaxExp;
}