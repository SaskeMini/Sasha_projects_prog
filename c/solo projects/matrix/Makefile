FLAGS = -Wall -Werror -Wextra -std=c11 -g

GCOV_FLAGS=-fprofile-arcs -ftest-coverage

all: s21_matrix.a

OS = $(shell uname)

ifeq ($(OS), Darwin)
	CHECK = -lcheck
endif

ifeq ($(OS), Linux)
	CHECK = -lcheck -lsubunit -lm -lrt -lpthread
endif

test: s21_matrix.a
	$(CC) $(CFLAGS) test/*.c -L. s21_matrix.a $(CHECK) -o testing

	make run_tests

s21_matrix.a:
	$(CC) $(CFLAGS) -c *.c

	ar rc s21_matrix.a *.o
	rm -rf *.o

gcov_report: s21_matrix.a
	$(CC) $(CFLAGS) $(GCOV_FLAGS) *.c  */*.c s21_matrix.a -o testing $(CHECK)
	make run_tests
	lcov -t "testing" -o testing.info -c -d .
	genhtml -o report testing.info


format:
	clang-format -style=google -i *.c */*.c *.h

style:
	clang-format -style=google -n *.c */*.c *.h
	
clean:
	rm -rf *.o *.a s21_matrix *.info  *.gcda *.gcno testing report

run_tests:
	./testing




