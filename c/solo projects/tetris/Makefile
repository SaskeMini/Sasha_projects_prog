CC=gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -g
GCOV_FLAGS=-fprofile-arcs -ftest-coverage

ifeq ($(shell uname), Linux)
    LDFLAGS = -lm -lncurses -lcheck -lsubunit -lm -lrt -lpthread
endif
ifeq ($(shell uname), Darwin)
    LDFLAGS = -lm -lncurses
endif

all: install

install:
	$(CC) $(CFLAGS) brick_game/tetris/*.c gui/cli/*.c -o tetris $(LDFLAGS) -o Out/tetris

uninstall:
	rm -rf Out/tetris

gcov_report: lib_tetris.a
	$(CC) $(CFLAGS) $(GCOV_FLAGS) test/*.c brick_game/tetris/backend.c -L. lib_tetris.a -o testing $(LDFLAGS)
	make run_tests
	lcov -t "testing" -o testing.info -c -d .
	genhtml -o report testing.info

lib_tetris.a:
	$(CC) $(CFLAGS) -c brick_game/tetris/backend.c $(LDFLAGS) 
	ar rc lib_tetris.a *.o
	rm -rf *.o

test:	lib_tetris.a
	$(CC) $(CFLAGS) test/*.c -L. lib_tetris.a  $(LDFLAGS) -o testing 
	make run_tests
	
tetris: 
	$(CC) $(CFLAGS) brick_game/tetris/*.c gui/cli/*.c -o tetris $(LDFLAGS)
	./tetris

format:
	clang-format -style=google -i */*/*.c test/*.c

style:
	clang-format -style=google -n */*/*.c */*/*.h test/*.c
    
clean:
	rm -rf *.o *.info *.gcda *.gcno lib_tetris.a tetris testing report

run_tests:
	./testing

dvi:
	open opisanie.txt

dist:
	mkdir -p res
	cp -a brick_game res
	cp -a gui res
	cp -a opisanie.txt res
	tar -czf Tetris.tar.gz res
	rm -rf res	
