CC = gcc
CFLAGS = -Wall -Werror -Wextra
LDFLAGS = -lcheck
SOURCES = src/arithmetic.c src/comparison.c src/convert_and_pars.c src/other.c src/service_fun.c src/sup_arithmetic.c src/sup_convert.c src/big_sup.c 
LIBS = $(shell pkg-config --libs check)
GCOVFLAGS = -fprofile-arcs -ftest-coverage
SRC = src/test_dir/add_sub_test.c src/test_dir/comparison_test.c src/test_dir/mul_test.c src/test_dir/test.c src/test_dir/div_test.c src/test_dir/other_fun_test.c src/test_dir/from_dec_to_float.c src/test_dir/from_decimal_to_int_test.c src/test_dir/from_float_to_decimal_test.c src/test_dir/from_int_to_decimal_test.c
EXECUTABLE = s21_decimal

all: s21_decimal.a

output_dir:
	mkdir -p gcov
	mkdir -p bin

clang:
	clang-format -i $(SRC)

test: output_dir s21_decimal.a
	$(CC) $(CFLAGS) $(SRC) bin/s21_decimal.a -o bin/test $(LIBS)
	./bin/test

gcov_report: output_dir
	$(CC) $(CFLAGS) $(GCOVFLAGS) $(SRC) $(SOURCES) -o gcov/gcov.out $(LIBS) 
	./gcov/gcov.out 
	lcov -t "s21_decimal" -o s21_decimal.info -c -d . -q --rc branch_coverage=1
	lcov -r s21_decimal.info -o s21_decimal.info --rc branch_coverage=1
	genhtml -o coverage_report s21_decimal.info -q --rc branch_coverage=1

s21_decimal.a: output_dir
	gcc $(FLAGS) -c $(SOURCES)
	ar rcs bin/s21_decimal.a *.o
	@rm *.o

clean:
	rm -rf bin gcov coverage_report s21_decimal.info

v: test
	valgrind --tool=memcheck --leak-check=yes --log-file="temp" ./test
