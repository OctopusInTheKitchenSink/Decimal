CC = gcc
FLAGS = -Wall -Werror -Wextra -std=c11
CFLAGS = -lrt -lcheck -lpthread -lsubunit -lm
GCFLAGS = -lrt -lcheck -lpthread -lsubunit -lm -fprofile-arcs -ftest-coverage  

all: s21_decimal.a test gcov_report clean

clean:
	rm -rf *.gcda *.gcno Test.c Test *.html *.css *.c.* a.out test/* executable_file/* *.o *.a

s21_decimal.a: clean
	gcc -c s21_additional_functions.c -o s21_additional_functions.o
	gcc -c s21_arithmetic_helper.c -o s21_arithmetic_helper.o
	gcc -c s21_big_additional_functions.c -o s21_big_additional_functions.o
	gcc -c s21_comparison.c -o cs21_omparison.o
	gcc -c s21_convert.c -o s21_convert.o
	gcc -c s21_mult.c -o s21_mult.o
	gcc -c s21_add.c -o s21_add.o
	gcc -c s21_div.c -o s21_div.o
	gcc -c s21_float_to_decimal.c -o s21_float_to_decimal.o
	gcc -c s21_floor.c -o s21_floor.o
	gcc -c s21_from_decimal_to_float.c -o s21_from_decimal_to_float.o
	gcc -c s21_from_decimal_to_int.c -o s21_from_decimal_to_int.o
	gcc -c s21_int_to_decimal.c -o s21_int_to_decimal.o
	gcc -c s21_negate.c -o s21_negate.o
	gcc -c s21_round.c -o s21_round.o
	gcc -c s21_sub.c -o s21_sub.o
	gcc -c s21_truncate.c -o s21_truncate.o
	gcc -c s21_shifts.c -o s21_shifts.o
	ar -crs s21_decimal.a *.o

test: clean
	@mkdir -p test
	@mkdir -p executable_file
	@checkmk clean_mode=1 checks/s21_comparison.check > test/test_comparison.c
	@checkmk clean_mode=1 checks/s21_arithmetic.check > test/test_arithmetic.c
	@checkmk clean_mode=1 checks/s21_negate.check > test/test_negate.c
	@checkmk clean_mode=1 checks/s21_truncate.check > test/test_truncate.c
	@checkmk clean_mode=1 checks/s21_round.check > test/test_round.c
	@checkmk clean_mode=1 checks/s21_from_int_to_decimal.check > test/test_from_int_to_decimal.c
	@checkmk clean_mode=1 checks/s21_from_decimal_to_int.check > test/test_from_decimal_to_int.c
	@checkmk clean_mode=1 checks/s21_from_float_to_decimal.check > test/test_from_float_to_decimal.c
	@checkmk clean_mode=1 checks/s21_from_decimal_to_float.check > test/test_from_decimal_to_float.c
	@checkmk clean_mode=1 checks/s21_floor.check > test/test_floor.c
	@$(CC) $(FLAGS) -o executable_file/test_comparison test/test_comparison.c *.c $(GCFLAGS)
	@$(CC) $(FLAGS) -o executable_file/test_arithmetic test/test_arithmetic.c *.c $(GCFLAGS)
	@$(CC) $(FLAGS) -o executable_file/test_negate test/test_negate.c *.c $(GCFLAGS)
	@$(CC) $(FLAGS) -o executable_file/test_truncate test/test_truncate.c *.c $(GCFLAGS)
	@$(CC) $(FLAGS) -o executable_file/test_round test/test_round.c *.c $(GCFLAGS)
	@$(CC) $(FLAGS) -o executable_file/test_from_int_to_decimal test/test_from_int_to_decimal.c *.c $(GCFLAGS)
	@$(CC) $(FLAGS) -o executable_file/test_from_decimal_to_int test/test_from_decimal_to_int.c *.c $(GCFLAGS)
	@$(CC) $(FLAGS) -o executable_file/test_from_float_to_decimal test/test_from_float_to_decimal.c *.c $(GCFLAGS)
	@$(CC) $(FLAGS) -o executable_file/test_from_decimal_to_float test/test_from_decimal_to_float.c *.c $(GCFLAGS)
	@$(CC) $(FLAGS) -o executable_file/test_floor test/test_floor.c *.c $(GCFLAGS)
	@./executable_file/test_comparison
	@./executable_file/test_arithmetic
	@./executable_file/test_negate
	@./executable_file/test_truncate
	@./executable_file/test_round
	@./executable_file/test_from_int_to_decimal
	@./executable_file/test_from_decimal_to_int
	@./executable_file/test_from_float_to_decimal
	@./executable_file/test_from_decimal_to_float
	@./executable_file/test_floor

gcov_report: test
	gcov executable_file/*.gcno executable_file/*.gcda 
	find ./executable_file/ ! -name '*s21*' -type f -delete
	gcovr -r . --html --html-details -o coverage_report.html
	open coverage_report.html
