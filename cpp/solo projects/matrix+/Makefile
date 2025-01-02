FLAGS = -Wall -Werror -Wextra -std=c11 -g

GCOV_FLAGS=-fprofile-arcs -ftest-coverage

CFLAGS=-Wall -Wextra -Werror

CC=g++

all: s21_matrix_oop.a

OS = $(shell uname)

ifeq ($(OS), Darwin)
	CHECK = -lgtest -lgmock -std=c++11
endif

ifeq ($(OS), Linux)
	CHECK = -lgtest -lgmock -lsubunit -lm -lrt -lpthread -std=c++11
endif

test: s21_matrix_oop.a
	$(CC) $(CFLAGS) test.cpp -L. s21_matrix_oop.a $(CHECK) -o testing
	# $(CC) test.cpp -o testing $(CHECK)
	make run_tests

s21_matrix_oop.a:
	$(CC) $(CFLAGS) -c *.cpp

	ar rc s21_matrix_oop.a *.o
	rm -rf *.o

gcov_report: s21_matrix_oop.a
	$(CC) $(CFLAGS) $(GCOV_FLAGS) *.cpp s21_matrix_oop.a -o testing $(CHECK)
	make run_tests
	lcov -t "testing" -o testing.info -c -d .
	genhtml -o report testing.info


format:
	clang-format -style=google -i *.cpp *.h

style:
	clang-format -style=google -n *.cpp *.h
	
clean:
	rm -rf *.o *.a s21_matrix *.info  *.gcda *.gcno testing report

run_tests:
	./testing



