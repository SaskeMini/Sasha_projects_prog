#include "../../brick_game/tetris/tetris.h"

void Start_game(GameInfo_t *game) {
  initscr();
  keypad(stdscr, 1);
  noecho();
  curs_set(0);
  mvprintw(10, 25, "Use any key to START");
  srand(time(NULL));
  int fig = rand() % 7;
  getch();
  clear();
  bool work = true;
  UserAction_t t = Start;
  bool spawn = false;
  fig_info tetris;
  fig_start coords;
  int temp_speed = 0;
  while (work) {
    if (spawn == false) {
      work = spawn_tetris(game, (++fig) % 7, &tetris, &coords);
      if (!work) {
        break;
      }
      spawn = true;
    }
    drow_next(fig);
    // refresh();
    // clear();
    draw_field(game);
    bool hold = false;
    int action = userInput(t, hold);
    if (action == Terminate) {
      break;
    } else if (action == Pause) {
      temp_speed = game->speed;
      game->speed = 3000000;
    } else if (action == Start) {
      game->speed = temp_speed;
      temp_speed = 0;
    }
    halfdelay(game->speed);
    spawn = work_with_user(game, action, &tetris, &coords);
    bool xz = true;
    if (spawn == false) {
      score_and_field(game);
      xz = false;
    }
    // refresh();
    // clear();
    draw_field(game);
    spawn = move_down(game, &tetris, &coords);
    if (spawn == false && xz) {
      score_and_field(game);
    }
    refresh();
    clear();
    draw_field(game);
  }
  refresh();
  clear();
  mvprintw(10, 25, "END GAME");
  mvprintw(12, 25, "Use any key to close game");
  getch();
  endwin();
}

void draw_field(GameInfo_t *game) {
  int rows = 21, cols = 11;
  mvprintw(9, 25, "Record: %d", game->high_score);
  mvprintw(11, 25, "Level: %d", game->level);
  mvprintw(13, 25, "Score: %d", game->score);
  mvaddch(0, 0, ACS_ULCORNER);
  mvaddch(0, cols, ACS_URCORNER);
  mvaddch(rows, 0, ACS_LLCORNER);
  mvaddch(rows, cols, ACS_LRCORNER);
  for (int i = 0; i < cols - 1; i++) {
    mvaddch(0, i + 1, ACS_HLINE);
    mvaddch(rows, i + 1, ACS_HLINE);
  }
  for (int i = 0; i < rows - 1; i++) {
    mvaddch(i + 1, 0, ACS_VLINE);
    mvaddch(i + 1, cols, ACS_VLINE);
  }
  for (int i = 1; i < rows; i++) {
    for (int j = 1; j < cols; j++) {
      if (game->field[i - 1][j - 1] == 1) {
        mvprintw(i, j, "#");
      } else {
        mvprintw(i, j, " ");
      }
    }
  }
}

void drow_next(int fig) {
  mvprintw(15, 25, "NEXT:");
  if ((fig % 7) == 0) {
    mvprintw(17, 26, "#");
    mvprintw(18, 26, "#");
    mvprintw(18, 27, "#");
    mvprintw(18, 28, "#");
  } else if ((fig % 7) == 1) {
    mvprintw(18, 26, "#");
    mvprintw(18, 27, "#");
    mvprintw(18, 28, "#");
    mvprintw(17, 28, "#");
  } else if ((fig % 7) == 2) {
    mvprintw(17, 26, "#");
    mvprintw(17, 27, "#");
    mvprintw(18, 26, "#");
    mvprintw(18, 27, "#");
  } else if ((fig % 7) == 3) {
    mvprintw(17, 27, "#");
    mvprintw(17, 28, "#");
    mvprintw(18, 26, "#");
    mvprintw(18, 27, "#");
  } else if ((fig % 7) == 4) {
    mvprintw(17, 27, "#");
    mvprintw(18, 26, "#");
    mvprintw(18, 27, "#");
    mvprintw(18, 28, "#");
  } else if ((fig % 7) == 5) {
    mvprintw(17, 26, "#");
    mvprintw(17, 27, "#");
    mvprintw(18, 27, "#");
    mvprintw(18, 28, "#");
  } else if ((fig % 7) == 6) {
    mvprintw(17, 25, "#");
    mvprintw(17, 26, "#");
    mvprintw(17, 27, "#");
    mvprintw(17, 28, "#");
  }
}