CC=g++
CFLAGS=-Wall -Wextra -Werror -std=c11
DIR=build

all:
	make install
	make open_game
	make uninstall

install:
	mkdir -p $(DIR)
	qmake -o $(DIR)/Makefile snake_game.pro
	make -C $(DIR)
	# ar rc $(DIR)/lib_snake.a $(DIR)/snake_game.o
	# $(CC) $(CFLAGS) brick_game/snake/front.cpp -L. $(DIR)/lib_snake.a -o snake_game

open_game:
	cp $(DIR)/snake_game .
	./snake_game

uninstall:
	rm -rf $(DIR) snake_game

clean:
	rm -rf $(DIR) snake_game