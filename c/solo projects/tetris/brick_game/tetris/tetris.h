#include <math.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

typedef struct {
  int square_fig[4][4];
} fig_info;

typedef struct {
  int i, j;
} fig_start;

int userInput(UserAction_t, bool);

bool spawn_tetris(GameInfo_t *, int, fig_info *, fig_start *);

GameInfo_t updateCurrentState(GameInfo_t);

void Start_game(GameInfo_t *);

void draw_field(GameInfo_t *);

void replace_field(GameInfo_t *);

void replace_next(GameInfo_t *, fig_info *, fig_start *, bool);

bool work_with_user(GameInfo_t *, int, fig_info *, fig_start *);

void move_tetris(GameInfo_t *, fig_info *, fig_start *);

bool move_down(GameInfo_t *, fig_info *, fig_start *);

void move_right(GameInfo_t *, fig_info *, fig_start *);

void move_left(GameInfo_t *, fig_info *, fig_start *);

void score_and_field(GameInfo_t *);

void drow_next(int);