OS = $(shell uname)

ifeq ($(OS), Darwin)
	CHECK = -lcheck  -lm  -lpthread
endif

ifeq ($(OS), Linux)
	CHECK = -lcheck -lsubunit -lm -lrt -lpthread
endif

CC=gcc


CFLAGS=-Wall -Werror -Wextra
GCOV_FLAGS=-fprofile-arcs -ftest-coverage

all:
	make test
	make clean
	make gcov_report
	make clean

test: s21_math.a
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -c s21_*.c -L.s21_math.a $(CHECK)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) test.c -L. s21_math.a $(CHECK) -o testing
	make run_tests

s21_math.a:
	$(CC) $(CFLAGS) -c s21_*.c
	ar rc s21_math.a *.o
	rm -rf *.o

gcov_report: s21_math.a
	$(CC) $(CFLAGS) $(GCOV_FLAGS) s21_*.c test.c s21_math.a -o testing $(CHECK)
	make run_tests
	lcov -t "testing" -o testing.info -c -d .
	genhtml -o report testing.info

clean:
	rm -rf *.o *.a testing s21_math.a *.info  *.gcda *.gcno

run_tests:
	./testing

